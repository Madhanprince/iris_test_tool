#include "mainwindow.h"

#include <QApplication>

#include <thread>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication a(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("qt_ui_node");

    // ROS spinning in separate thread
    std::thread ros_thread([&]() {
        rclcpp::spin(node);
    });
    MainWindow w(node);
    // w.show();
    w.showMaximized();

    int result = a.exec();

    rclcpp::shutdown();
    ros_thread.join();
    

    return result;
}
