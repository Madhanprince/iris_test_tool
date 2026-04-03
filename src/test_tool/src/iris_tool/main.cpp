#include "mainwindow.h"

#include <QApplication>
#include <thread>
#include <rclcpp/rclcpp.hpp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rclcpp::init(argc, argv);
    rclcpp::Node::SharedPtr node = std::make_shared<MainWindow>();
    MainWindow w;
    w.show(); // Show the main window on the screen

    return a.exec(); // Start the event loop (keeps the application running and responsive)
                    // Without this, the window will open and close immediately
}

