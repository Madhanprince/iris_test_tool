#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTimer>
#include <QProcess>
#include <rclcpp/rclcpp.hpp>
#include <rcl_interfaces/msg/log.hpp>
#include "qt_ros.h"
#include <memory>
#include <map>
#include <set>
#include <QToolBar>
#include <rviz_common/render_panel.hpp>
#include <rviz_common/visualization_manager.hpp>
#include <rviz_common/tool_manager.hpp>
#include <rviz_common/display.hpp>
#include <rviz_common/display_context.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction.hpp>
#include <rviz_common/view_manager.hpp>
#include <rviz_rendering/render_window.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace rviz_common {
    class RenderPanel;
    class VisualizationManager;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<Qtros> getNode();

private slots:
    void onLogReceived(const QString &msg, const QString &node, int level);
    void onItemChanged(QListWidgetItem *item);
    void refreshNodeList();

private:
    Ui::MainWindow *ui;

    // ── General UI ────────────────────────────────────────────────────────────
    QListWidgetItem *item  = nullptr;
    QTimer          *Timer = nullptr;
    QStringList      nodes;

    // ── ROS node ──────────────────────────────────────────────────────────────
    std::shared_ptr<Qtros> qtros;
    std::set<std::string>  clicked_node;

    // ── Shared RViz resources ─────────────────────────────────────────────────
    // IMPORTANT: Ogre registers materials (RVIZ/Red, RVIZ/Blue …) as GLOBAL
    // singletons. Creating a second VisualizationManager crashes with:
    //   "Material with the name RVIZ/Red already exists"
    // Solution: ONE ros node, ONE clock, ONE VisualizationManager, shared by
    // all three pages. Each page gets its own RenderPanel only.

    std::shared_ptr<rviz_common::ros_integration::RosNodeAbstraction> ros_node_shared_;
    rclcpp::Clock::SharedPtr rviz_clock_;

    // The ONE shared VisualizationManager
    rviz_common::VisualizationManager *visualizationManager_ = nullptr;

    // One RenderPanel per page (all attached to the same manager above)
    rviz_common::RenderPanel *render_panel_loc = nullptr;  // localization (ui->widget)
    rviz_common::RenderPanel *render_panel_map = nullptr;  // mapping      (ui->widget_4)
    rviz_common::RenderPanel *render_panel_nav = nullptr;  // navigation   (ui->widget_3)

    // Per-page tool pointers
    // localization page
    rviz_common::Tool *loc_cleaning = nullptr;
    rviz_common::Tool *loc_goal     = nullptr;
    rviz_common::Tool *loc_pose     = nullptr;
    // mapping page
    rviz_common::Tool *map_cleaning = nullptr;
    rviz_common::Tool *map_goal     = nullptr;
    rviz_common::Tool *map_pose     = nullptr;
    // navigation page
    rviz_common::Tool *nav_cleaning = nullptr;
    rviz_common::Tool *nav_goal     = nullptr;
    rviz_common::Tool *nav_pose     = nullptr;

    // ── Init flags ────────────────────────────────────────────────────────────
    bool rviz_initialized_localization = false;
    bool rviz_initialized_mapping      = false;
    bool rviz_initialized_navigation   = false;

    // ── Private helpers ───────────────────────────────────────────────────────
    void pages(int row);

    // Called once. Creates the VisualizationManager. Subsequent calls are no-op.
    void initVisualizationManager(rviz_common::RenderPanel *first_panel);

    // Allocates a RenderPanel, appends it to layout, and initialises Ogre window
    rviz_common::RenderPanel *buildRenderPanel(QVBoxLayout *layout);

    void initRViz_localization();
    void initRViz_mapping();
    void initRViz_navigation();

    void setupDisplays_loc();
    void setupDisplays_map();
    void setupDisplays_nav();
};

#endif // MAINWINDOW_H
