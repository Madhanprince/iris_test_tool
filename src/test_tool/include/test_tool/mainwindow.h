#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>

#include <rclcpp/rclcpp.hpp>
#include <QApplication>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <thread>
#include <chrono>
#include <QWidget>
#include "rcl_interfaces/msg/log.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_launch_button_clicked();

    void on_log_button_clicked();

private:
    Ui::MainWindow *ui;
    QListView *listview ;
    QStringListModel *model ;



};

#endif
