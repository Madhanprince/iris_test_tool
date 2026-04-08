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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } //Qt puts all generated UI classes inside a namespace called Ui
QT_END_NAMESPACE

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
    QString *outputs ;
    QProcess process;

    std::shared_ptr<Qtros> qtros;

    void refreshNodeList();
    void pages(int row);
    void onItemChanged(QListWidgetItem *item, const rcl_interfaces::msg::Log::SharedPtr msg);
    void onLogReceived(const QString &msg,const QString &node,int level);
};
#endif // MAINWINDOW_H
