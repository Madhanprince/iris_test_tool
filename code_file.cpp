#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QProcess>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QString>
#include <rviz_common/visualization_manager.hpp>

using namespace std::chrono_literals;

// ═════════════════════════════════════════════════════════════════════════════
//  CONSTRUCTOR
// ═════════════════════════════════════════════════════════════════════════════

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ── Sidebar → page switching ──────────────────────────────────────────────
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            this, [=](int row){ pages(row); });

    ui->listWidget->setCurrentRow(0);  // default page

    // ── ROS logging node ──────────────────────────────────────────────────────
    qtros = std::make_shared<Qtros>();
    connect(qtros.get(), &Qtros::logReceived,
            this, &MainWindow::onLogReceived);

    // ── Shared RViz ROS resources (ONE node, ONE clock for ALL pages) ─────────
    // We create these here so they are ready before any page triggers RViz init.
    ros_node_shared_ =
        std::make_shared<rviz_common::ros_integration::RosNodeAbstraction>(
            "rviz_shared_node");

    rviz_clock_ = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    // ── Node list widget ──────────────────────────────────────────────────────
    connect(ui->node_list, &QListWidget::itemChanged,
            this, &MainWindow::onItemChanged);

    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::refreshNodeList);
    Timer->start(500ms);
}

// ═════════════════════════════════════════════════════════════════════════════
//  DESTRUCTOR
// ═════════════════════════════════════════════════════════════════════════════

MainWindow::~MainWindow()
{
    // Stop RViz updates BEFORE the render panels are destroyed.
    // Skipping this causes a crash inside Ogre on close.
    if (visualizationManager_) {
        visualizationManager_->stopUpdate();
        delete visualizationManager_;
        visualizationManager_ = nullptr;
    }

    delete ui;
}

// ═════════════════════════════════════════════════════════════════════════════
//  getNode
// ═════════════════════════════════════════════════════════════════════════════

std::shared_ptr<Qtros> MainWindow::getNode()
{
    std::cout << "started" << std::endl;
    return qtros;
}

// ═════════════════════════════════════════════════════════════════════════════
//  PAGE SWITCHING  (called by sidebar listWidget)
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::pages(int row)
{
    ui->stackedWidget->setCurrentIndex(row);

    switch (row) {
        case 0:
            // Home / dashboard page — no RViz needed
            break;

        case 1:
            // Node list page
            refreshNodeList();
            break;

        case 2:
            // Mapping page
            if (!rviz_initialized_mapping) {
                initRViz_mapping();
                rviz_initialized_mapping = true;
            }
            break;

        case 3:
            // Navigation page
            if (!rviz_initialized_navigation) {
                initRViz_navigation();
                rviz_initialized_navigation = true;
            }
            break;

        case 4:
            // Localization page
            if (!rviz_initialized_localization) {
                initRViz_localization();
                rviz_initialized_localization = true;
            }
            break;

        default:
            break;
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  NODE LIST HELPERS
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::refreshNodeList()
{
    auto get_nodes = qtros->get_node_names();
    for (auto &node : get_nodes) {
        QString qnode = QString::fromStdString(node);
        qnode = qnode.trimmed().remove("/");
        node = qnode.toStdString();
    }

    ui->node_list->blockSignals(true);

    QSet<QString> activeNodes;
    for (const auto &node : get_nodes)
        activeNodes.insert(QString::fromStdString(node));

    // Add new nodes not already in the list
    for (const auto &node : get_nodes) {
        QString qnode = QString::fromStdString(node);
        bool exists = false;
        for (int i = 0; i < ui->node_list->count(); i++) {
            if (ui->node_list->item(i)->text() == qnode) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            QListWidgetItem *it = new QListWidgetItem(qnode, ui->node_list);
            it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
            it->setCheckState(Qt::Unchecked);
        }
    }

    // Remove nodes that are no longer running
    for (int i = ui->node_list->count() - 1; i >= 0; i--) {
        QListWidgetItem *it = ui->node_list->item(i);
        if (!activeNodes.contains(it->text())) {
            std::string nodeName = it->text().toStdString();
            if (clicked_node.find(nodeName) != clicked_node.end())
                clicked_node.erase(nodeName);
            delete ui->node_list->takeItem(i);
        }
    }

    ui->node_list->blockSignals(false);
}

void MainWindow::onItemChanged(QListWidgetItem *item)
{
    QString nodeName = item->text();
    qDebug() << nodeName;
    std::string node = nodeName.toStdString();

    if (item->checkState() == Qt::Checked) {
        if (clicked_node.find(node) == clicked_node.end())
            clicked_node.insert({node});
        std::cout << "Checked: " << node << "\n";
    } else {
        if (clicked_node.find(node) != clicked_node.end())
            clicked_node.erase(node);
        std::cout << "Unchecked: " << node << "\n";
    }
}

void MainWindow::onLogReceived(const QString &msg, const QString &name, int level)
{
    if (clicked_node.find(name.toStdString()) != clicked_node.end()) {
        QString logMessage = QString("[%1] %2: %3").arg(msg).arg(name).arg(level);
        if (level >= 40)
            ui->plainTextEdit_3->appendPlainText(logMessage);   // ERROR
        else if (level >= 30)
            ui->plainTextEdit_2->appendPlainText(logMessage);   // WARN
        else
            ui->plainTextEdit->appendPlainText(logMessage);     // INFO
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  RVIZ CORE HELPERS
// ═════════════════════════════════════════════════════════════════════════════

// Called from whichever initRViz_* runs FIRST.
// On every subsequent call it does nothing (guard at top).
// This is the only place VisualizationManager is ever constructed,
// which prevents the "RVIZ/Red already exists" Ogre crash.
void MainWindow::initVisualizationManager(rviz_common::RenderPanel *first_panel)
{
    if (visualizationManager_) return;  // already created — skip

    std::weak_ptr<rviz_common::ros_integration::RosNodeAbstractionIface>
        weak = ros_node_shared_;  // implicit upcast to interface type

    visualizationManager_ = new rviz_common::VisualizationManager(
        first_panel,
        weak,
        nullptr,        // window manager (not needed)
        rviz_clock_
    );

    visualizationManager_->initialize();

    // Default view and tool — set once here, shared by all pages
    visualizationManager_->getViewManager()
        ->setCurrentViewControllerType("rviz_default_plugins/Orbit");

    auto *tm = visualizationManager_->getToolManager();
    tm->addTool("rviz_default_plugins/MoveCamera");
    tm->setCurrentTool(tm->getTool(tm->numTools() - 1));

    visualizationManager_->startUpdate();
}


// Allocates a RenderPanel, adds it to the layout, and initialises the
// underlying Ogre render window.  The caller must then call
//   render_panel->initialize(visualizationManager_)
// after initVisualizationManager() has run.
rviz_common::RenderPanel *MainWindow::buildRenderPanel(QVBoxLayout *layout)
{
    auto *panel = new rviz_common::RenderPanel();
    layout->addWidget(panel);

    panel->winId();                         // forces native window handle
    QApplication::processEvents();


    panel->getRenderWindow()->initialize(); // initialises Ogre for this panel
    QApplication::processEvents();

    return panel;
}

// ═════════════════════════════════════════════════════════════════════════════
//  PAGE 4 — LOCALIZATION  (ui->widget)
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::initRViz_localization()
{
    // Guard: rviz_initialized_localization is checked in pages() before calling,
    // but we double-check here for safety.
    if (rviz_initialized_localization) return;

    // ── Layout ───────────────────────────────────────────────────────────────
    auto *layout = new QVBoxLayout(ui->widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    ui->widget->setLayout(layout);

    // ── Toolbar ──────────────────────────────────────────────────────────────
    auto *toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    layout->addWidget(toolbar);

    auto *aStartMap = new QAction("Start Mapping",    this);
    auto *aStopMap  = new QAction("Stop Mapping",     this);
    auto *aCleaning = new QAction("Cleaning Points",  this);
    auto *aGoal     = new QAction("2D Goal Pose",     this);
    auto *aPose     = new QAction("2D Pose Estimate", this);
    auto *aSafety   = new QAction("Safety Points",    this);

    toolbar->addAction(aStartMap);
    toolbar->addAction(aStopMap);
    toolbar->addSeparator();
    toolbar->addAction(aCleaning);
    toolbar->addAction(aGoal);
    toolbar->addAction(aPose);
    toolbar->addAction(aSafety);

    // Wire Start/Stop Mapping to your own slots when ready:
    // connect(aStartMap, &QAction::triggered, this, &MainWindow::onStartMapping);
    // connect(aStopMap,  &QAction::triggered, this, &MainWindow::onStopMapping);

    // ── RenderPanel ───────────────────────────────────────────────────────────
    render_panel_loc = buildRenderPanel(layout);

    // ── VisualizationManager (created here if localization page loads first) ──
    initVisualizationManager(render_panel_loc);

    // Attach this panel to the shared manager
    render_panel_loc->initialize(visualizationManager_);

    // ── Tools ────────────────────────────────────────────────────────────────
    auto *tm = visualizationManager_->getToolManager();

    loc_cleaning = tm->addTool("rviz_default_plugins/PublishPoint");
    loc_goal     = tm->addTool("rviz_default_plugins/SetGoal");
    loc_pose     = tm->addTool("rviz_default_plugins/SetInitialPose");

    connect(aCleaning, &QAction::triggered, this, [=]() {
        if (loc_cleaning) tm->setCurrentTool(loc_cleaning);
    });
    connect(aGoal, &QAction::triggered, this, [=]() {
        if (loc_goal) tm->setCurrentTool(loc_goal);
    });
    connect(aPose, &QAction::triggered, this, [=]() {
        if (loc_pose) tm->setCurrentTool(loc_pose);
    });

    // ── Displays ─────────────────────────────────────────────────────────────
    setupDisplays_loc();
}

void MainWindow::setupDisplays_loc()
{
    visualizationManager_->setFixedFrame("map");

    auto *grid = visualizationManager_->createDisplay(
        "rviz_default_plugins/Grid", "Grid_loc", true);
    Q_UNUSED(grid);

    auto *laser = visualizationManager_->createDisplay(
        "rviz_default_plugins/LaserScan", "LaserScan_loc", true);
    if (laser) laser->subProp("Topic")->setValue("/scan");

    auto *map = visualizationManager_->createDisplay(
        "rviz_default_plugins/Map", "Map_loc", true);
    if (map) map->subProp("Topic")->setValue("/map");

    auto *robot = visualizationManager_->createDisplay(
        "rviz_default_plugins/RobotModel", "RobotModel_loc", true);
    if (robot) robot->subProp("Description Topic")->setValue("/robot_description");
}

// ═════════════════════════════════════════════════════════════════════════════
//  PAGE 2 — MAPPING  (ui->widget_4)
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::initRViz_mapping()
{
    if (rviz_initialized_mapping) return;

    // ── Layout ───────────────────────────────────────────────────────────────
    auto *layout = new QVBoxLayout(ui->widget_4);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    ui->widget_4->setLayout(layout);

    // ── Toolbar ──────────────────────────────────────────────────────────────
    auto *toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    layout->addWidget(toolbar);

    auto *aCleaning = new QAction("Cleaning Points",  this);
    auto *aGoal     = new QAction("2D Goal Pose",     this);
    auto *aPose     = new QAction("2D Pose Estimate", this);
    auto *aSafety   = new QAction("Safety Points",    this);

    toolbar->addAction(aCleaning);
    toolbar->addAction(aGoal);
    toolbar->addAction(aPose);
    toolbar->addAction(aSafety);


    // ── RenderPanel ───────────────────────────────────────────────────────────
    render_panel_map = buildRenderPanel(layout);

    // ── VisualizationManager (created here if mapping page loads first) ───────
    initVisualizationManager(render_panel_map);

    // Attach this panel to the shared manager
    render_panel_map->initialize(visualizationManager_);

    // ── Tools ────────────────────────────────────────────────────────────────
    auto *tm = visualizationManager_->getToolManager();

    map_cleaning = tm->addTool("rviz_default_plugins/PublishPoint");
    map_goal     = tm->addTool("rviz_default_plugins/SetGoal");
    map_pose     = tm->addTool("rviz_default_plugins/SetInitialPose");

    connect(aCleaning, &QAction::triggered, this, [=]() {
        if (map_cleaning) tm->setCurrentTool(map_cleaning);
    });
    connect(aGoal, &QAction::triggered, this, [=]() {
        if (map_goal) tm->setCurrentTool(map_goal);
    });
    connect(aPose, &QAction::triggered, this, [=]() {
        if (map_pose) tm->setCurrentTool(map_pose);
    });

    // ── Displays ─────────────────────────────────────────────────────────────
    setupDisplays_map();
}

void MainWindow::setupDisplays_map()
{
    visualizationManager_->setFixedFrame("map");

    auto *grid = visualizationManager_->createDisplay(
        "rviz_default_plugins/Grid", "Grid_map", true);
    Q_UNUSED(grid);

    auto *laser = visualizationManager_->createDisplay(
        "rviz_default_plugins/LaserScan", "LaserScan_map", true);
    if (laser) laser->subProp("Topic")->setValue("/scan");

    auto *map = visualizationManager_->createDisplay(
        "rviz_default_plugins/Map", "Map_map", true);
    if (map) map->subProp("Topic")->setValue("/map");
}

// ═════════════════════════════════════════════════════════════════════════════
//  PAGE 3 — NAVIGATION  (ui->widget_3)
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::initRViz_navigation()
{
    if (rviz_initialized_navigation) return;

    // ── Layout ───────────────────────────────────────────────────────────────
    auto *layout = new QVBoxLayout(ui->widget_3);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    ui->widget_3->setLayout(layout);

    // ── Toolbar ──────────────────────────────────────────────────────────────
    auto *toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    layout->addWidget(toolbar);

    auto *aCleaning = new QAction("Cleaning Points",  this);
    auto *aGoal     = new QAction("2D Goal Pose",     this);
    auto *aPose     = new QAction("2D Pose Estimate", this);
    auto *aSafety   = new QAction("Safety Points",    this);

    toolbar->addAction(aCleaning);
    toolbar->addAction(aGoal);
    toolbar->addAction(aPose);
    toolbar->addAction(aSafety);

    // ── RenderPanel ───────────────────────────────────────────────────────────
    render_panel_nav = buildRenderPanel(layout);

    // ── VisualizationManager (created here if navigation page loads first) ────
    initVisualizationManager(render_panel_nav);

    // Attach this panel to the shared manager
    render_panel_nav->initialize(visualizationManager_);

    // ── Tools ────────────────────────────────────────────────────────────────
    auto *tm = visualizationManager_->getToolManager();

    nav_cleaning = tm->addTool("rviz_default_plugins/PublishPoint");
    nav_goal     = tm->addTool("rviz_default_plugins/SetGoal");
    nav_pose     = tm->addTool("rviz_default_plugins/SetInitialPose");

    connect(aCleaning, &QAction::triggered, this, [=]() {
        if (nav_cleaning) tm->setCurrentTool(nav_cleaning);
    });
    connect(aGoal, &QAction::triggered, this, [=]() {
        if (nav_goal) tm->setCurrentTool(nav_goal);
    });
    connect(aPose, &QAction::triggered, this, [=]() {
        if (nav_pose) tm->setCurrentTool(nav_pose);
    });

    // ── Displays ─────────────────────────────────────────────────────────────
    setupDisplays_nav();
}

void MainWindow::setupDisplays_nav()
{
    visualizationManager_->setFixedFrame("map");

    auto *grid = visualizationManager_->createDisplay(
        "rviz_default_plugins/Grid", "Grid_nav", true);
    Q_UNUSED(grid);

    auto *laser = visualizationManager_->createDisplay(
        "rviz_default_plugins/LaserScan", "LaserScan_nav", true);
    if (laser) laser->subProp("Topic")->setValue("/scan");

    auto *map = visualizationManager_->createDisplay(
        "rviz_default_plugins/Map", "Map_nav", true);
    if (map) map->subProp("Topic")->setValue("/map");

    // Navigation-specific: costmaps
    auto *global_cm = visualizationManager_->createDisplay(
        "rviz_default_plugins/Map", "GlobalCostmap_nav", true);
    if (global_cm)
        global_cm->subProp("Topic")->setValue("/global_costmap/costmap");

    auto *local_cm = visualizationManager_->createDisplay(
        "rviz_default_plugins/Map", "LocalCostmap_nav", true);
    if (local_cm)
        local_cm->subProp("Topic")->setValue("/local_costmap/costmap");
}
