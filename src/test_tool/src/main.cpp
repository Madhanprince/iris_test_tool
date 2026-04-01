#include "mainwindow.h"

#include <QApplication>
//#include <rclcpp/rclcpp.hpp>
#include <thread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    rclcpp::init(argc, argv);
    MainWindow w;
    w.show(); // Show the main window on the screen

    return a.exec(); // Start the event loop (keeps the application running and responsive)
                    // Without this, the window will open and close immediately
}

