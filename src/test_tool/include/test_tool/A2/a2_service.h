#ifndef A2_SERVICE_H
#define A2_SERVICE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include "mainwindow.h"


class A2_service : public QWidget
{
    Q_OBJECT
public:
    explicit A2_service(Ui::MainWindow *mainUi,
                        QWidget *parent = nullptr);
    Ui::MainWindow *ui;      
    rclcpp::Client<srv::BrushControl>::SharedPtr client_brush;    
    rclcpp::Client<srv::VaccumControl>::SharedPtr client_vaccum_;  
    QHBoxLayout *rowLayout ;
    QLabel *light_layout; ;   
    QVector<QLabel*> lights;     
    
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