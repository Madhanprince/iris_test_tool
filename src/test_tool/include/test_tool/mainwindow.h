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
#include <QToolBar>
#include <QAction>
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
    QToolBar *toolbar =nullptr;
    QVBoxLayout *layout ;
        

    bool rviz_initialized_mapping = false;
    bool rviz_initialized_localization =false;
    bool rviz_initialized_navigation =false;
    std::shared_ptr<Qtros> qtros;
    std::set<std::string> clicked_node;
    rviz_common::RenderPanel *render_panel_1 = nullptr;
    rviz_common::RenderPanel *render_panel_2 = nullptr;
    rviz_common::RenderPanel *render_panel_3 = nullptr;
    rviz_common::VisualizationManager *visualizationManager_ = nullptr;
    rviz_common::ToolManager *tool_manager = nullptr;
    rviz_common::ToolManager *tool_manager_2 = nullptr;
    rviz_common::ToolManager *tool_manager_3 = nullptr;
    rviz_common::Tool *cleaning_points_plugins = nullptr;
    rviz_common::Tool *goal_pose_plugins = nullptr;
    rviz_common::Tool *pose_estimate_plugins = nullptr; 
    std::weak_ptr<rviz_common::ros_integration::RosNodeAbstraction> ros_weak;
    std::shared_ptr<rviz_common::ros_integration::RosNodeAbstraction> ros_node_mapping;
    rclcpp::Clock::SharedPtr rivz_clock;
    QAction *Cleaning_Points ;
    QAction *Goal_Pose ;
    QAction *Pose_Estimate; 
    QAction *Safty_Points ;


    void refreshNodeList();
    void pages(int row);
    void onItemChanged(QListWidgetItem *item);
    void onLogReceived(const QString &msg,const QString &node,int level);
    void initRViz_mapping();
    void initRViz_navigation();
    void initRViz_localization();
    void setupDisplays();
    void setupDisplays_2();
    void setupDisplays_3();

    void visual_manager(
        rviz_common::RenderPanel * visual_panel, 
        std::weak_ptr<rviz_common::ros_integration::RosNodeAbstractionIface> ros_weak_ptr, // Added "Iface"
        rclcpp::Clock::SharedPtr sys_clock); // Simplified Clock type

};
#endif // MAINWINDOW_H
