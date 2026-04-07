#include "mainwindow.h"

#include <QApplication>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <thread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MainWindow>();
    MainWindow w(node);
    w.show(); // Show the main window on the screen
    std::thread ros_thread([node]() {
        rclcpp::spin(node);
    });
    int result = a.exec(); // Start the Qt event loop it is the blocking call 
    // After the Qt event loop exits, we can safely shutdown ROS and join the thread
    rclcpp::shutdown(); 

    ros_thread.join(); // Wait for the ROS thread to finish before exiting
    return result; // Start the event loop (keeps the application running and responsive)
                    // Without this, the window will open and close immediately
}

