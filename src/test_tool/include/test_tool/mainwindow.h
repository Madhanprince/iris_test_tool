#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTimer>
#include <QProcess>
#include <rclcpp/rclcpp.hpp>
#include <rcl_interfaces/msg/log.hpp>
#include "qt_ros.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public rclcpp::Node
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    rclcpp::Node::SharedPtr node ;
    rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr subscription;

private:
    Ui::MainWindow *ui;
    QListWidgetItem *item;
    QTimer *Timer;
    QStringList nodes;
    QString *outputs ;
    QProcess process;
    
    Qtros *qtros;

    void refreshNodeList();
    void pages(int row);
    void onItemChanged(QListWidgetItem *item, const rcl_interfaces::msg::Log::SharedPtr msg);
    void onLogReceived(const rcl_interfaces::msg::Log::SharedPtr msg);
};
#endif // MAINWINDOW_H
