#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>

// #include <rclcpp/rclcpp.h>
#include <QApplication>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <thread>
#include <chrono>
#include <QWidget>
#include "rcl_interfaces/msg/log.hpp"
#include <QComboBox>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_launch_button_clicked();

    // void on_log_button_clicked();

    // void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QListView *listview ;
    QStringListModel *model ;
    QComboBox *logLevelComboBox;
    QTextEdit *textEdit;
    QWidget *logWidget=nullptr;

    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr log_subscription_; 



};

#endif
