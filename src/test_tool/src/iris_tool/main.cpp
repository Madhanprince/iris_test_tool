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
    w.show(); // Show the main window on the screen
    auto qtnode = w.getNode();
    std::thread ros_thread([qtnode]() {
        rclcpp::spin(qtnode);
    });
    int result = a.exec(); // Start the Qt event loop it is the blocking call 
    // After the Qt event loop exits, we can safely shutdown ROS and join the thread
    rclcpp::shutdown(); 
    ros_thread.join(); // Wait for the ROS thread to finish before exiting
    return result; // Start the event loop (keeps the application running and responsive)
                    // Without this, the window will open and close immediately
}

