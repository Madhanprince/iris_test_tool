#include "A2/a2_service.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>
#include <iostream>

A2_service::A2_service(QWidget *parent)
    : QWidget(parent)
{
    QStringList messages = {
        "Brush_Command_received", 
        "Brush_Motor_ON" 
        "Vaccum_Command_received", 
        "Vaccum_Motor_ON", 
        "Water_Pump", 
        "Detergent", 
        "Brush Motor Actuator", 
        "Moving_up", 
        "Moving_Down", 
        "Hold_Up", 
        "Hold_Down", 
        "Squeegee Actuator", 
        "Moving_up", 
        "Moving_Down", 
        "Hold_Up", 
        "Hold_Down",
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for (const QString &msg : messages)
    {
        QHBoxLayout *rowLayout = new QHBoxLayout;

        QLabel *light = new QLabel;

        light->setFixedSize(14,14);

        light->setStyleSheet(
            "background-color:#22c55e;"
            "border-radius:7px;"
        );

        QLabel *text = new QLabel(msg);

        rowLayout->addWidget(light);
        rowLayout->addWidget(text);

        mainLayout->addLayout(rowLayout); //“Add the entire horizontal layout rowLayout
        //as one item inside the vertical layout mainLayout.”
    }
    setLayout(mainLayout);
}