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
#include <rviz_common/render_panel.hpp>
#include <rviz_common/visualization_manager.hpp>
#include <rviz_common/display.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction.hpp>
#include <rviz_common/tool_manager.hpp>        // ← add
#include <rviz_common/view_manager.hpp>        // ← add
#include <rviz_rendering/render_window.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } //Qt puts all generated UI classes inside a namespace called Ui
QT_END_NAMESPACE

// Forward declarations (clean way)
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
private:
    Ui::MainWindow *ui;
    QListWidgetItem *item;
    QTimer *Timer;
    QStringList nodes;

    bool rviz_initialized = false;
    std::shared_ptr<Qtros> qtros;
    std::set<std::string> clicked_node;
    rviz_common::RenderPanel *render_panel = nullptr;
    rviz_common::VisualizationManager *visualizationManager_ = nullptr;

    void refreshNodeList();
    void pages(int row);
    void onItemChanged(QListWidgetItem *item);
    void onLogReceived(const QString &msg,const QString &node,int level);
    void initRViz();
    void setupDisplays();
};
#endif // MAINWINDOW_H
