#include "mainwindow.h"
#include "qt_ros.h"
#include <QApplication>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <thread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rclcpp::init(argc, argv);
    
    MainWindow w;
    w.show();

    // Use a shared pointer to ensure the node stays alive
    auto qtnode = w.getNode(); 
    
    // Check if qtnode is valid before spinning
    if (!qtnode) {
        return -1; 
    }
    // Launch ROS spinning in a background thread
    std::thread ros_thread([qtnode]() {
        rclcpp::spin(qtnode);
    });

    int result = a.exec(); // Main Qt event loop

    // Proper shutdown sequence
    rclcpp::shutdown();
    if (ros_thread.joinable()) {
        ros_thread.join(); // Wait for ROS thread to finish
    }

    return result;
}
