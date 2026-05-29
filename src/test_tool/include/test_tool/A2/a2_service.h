#ifndef A2_SERVICE_H
#define A2_SERVICE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "test_tool/srv/A2Command.hpp"
#include "test_tool/msg/A2FunctionalStatus.hpp"
#include "test_tool/msg/A2FaultStatus.hpp"


class A2_service : public QWidget
{
    Q_OBJECT
public:
    explicit A2_service(Ui::MainWindow *mainUi,
                        QWidget *parent = nullptr);
    Ui::MainWindow *ui;      
    rclcpp::Client<test_tool::srv::A2Command>::SharedPtr client_brush;    
    rclcpp::Client<test_tool::srv::A2Command>::SharedPtr client_vaccum;  
    QHBoxLayout *rowLayout ;
    QLabel *light_layout; ;   
    QVector<QLabel*> lights;     
    QVector<QLabel*> store_faults;     
    
    const QString ACTIVE_BUTTON_STYLE =
    "background-color:#22c55e;";

    const QString INACTIVE_BUTTON_STYLE =
    "background-color:#ef4444;"

private slots:
    void on_water_level_slider_valueChanged(int value);
    void brush_on_control();
    void brush_off_control();
    void vaccum_on_control();
    void vaccum_off_control();
    void a2_status_list();
};

#endif // A2_SERVICE_H