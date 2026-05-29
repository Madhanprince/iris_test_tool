#include "A2/a2_service.h"
#include <QStringList>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


A2_service::A2_service(Ui::MainWindow *mainUi,
                       QWidget *parent)
    : QWidget(parent),
      ui(mainUi) // Initialize the UI pointer
{
    client_brush = qtros->create_client<test_tool::srv::A2Command>("a2_control/a2_command");
    client_vaccum = qtros->create_client<test_tool::srv::A2Command>("a2_control/a2_command");

    auto publisher = qtros->create_publisher<test_tool::msg::WaterLevel>("/water_level", 10);
    auto brush_vaccum_status_subscriber = qtros->create_subscription<test_tool::msg::A2FunctionalStatus>(
        "/a2_status",
        10,std::bind(
            &A2_service::a2_status_display,
            this,
            std::placeholders::_1
        )
    );
    auto brush_vaccum_faults_subscriber = qtros->create_subscription<test_tool::msg::A2FunctionalStatus>(
        "/a2_faults",
        10,std::bind(
            &A2_service::a2_faults_display,
            this,
            std::placeholders::_1
        )
    );
   
    connect(ui->water_level_slider,&QSlider::valueChanged,this,&A2_service::on_water_level_slider_valueChanged);
    connect(ui->brush_on, &QPushButton::clicked, this, &A2_service::brush_on_control);
    connect(ui->brush_off, &QPushButton::clicked, this, &A2_service::brush_off_control);
    connect(ui->vaccum_on, &QPushButton::clicked, this, &A2_service::vaccum_on_control);
    connect(ui->vaccum_off, &QPushButton::clicked, this, &A2_service::vaccum_off_control);

    a2_status_list();
    a2_faults_list();

} 

QStringList status_messages = {
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

void A2_service::a2_status_list()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for (const QString &msg : status_messages)
    {
        if(msg == "Brush Motor Actuator" || msg == "Squeegee Actuator")
        {
            QLabel *actuatorLabel = new QLabel(msg);
            actuatorLabel->setStyleSheet("font-weight:600;font-size:12px;");
            mainLayout->addWidget(actuatorLabel);
            continue;
        }

        QHBoxLayout *rowLayout = new QHBoxLayout;

        QLabel *light_layout = new QLabel;

        light_layout->setFixedSize(14,14);

        light_layout->setStyleSheet(
            LIGHT_RED_STYLE
        );

        lights.append(light_layout);
        QLabel *text = new QLabel(msg);

        rowLayout->addWidget(light_layout);
        rowLayout->addWidget(text);

        mainLayout->addLayout(rowLayout);
    }

    setLayout(mainLayout);
}

void A2_service::a2_status_display(
    const test_tool::msg::A2FunctionalStatus::SharedPtr msg)
{
    lights[0]->setStyleSheet(
        msg->brush.brush_motor_command ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[1]->setStyleSheet(
        msg->brush.brush_motor_status ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[2]->setStyleSheet(
        msg->vaccum.vaccum_motor_command ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[3]->setStyleSheet(
        msg->vaccum.vaccum_motor_status ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[4]->setStyleSheet(
        msg->water_pump ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[5]->setStyleSheet(
        msg->detergent_pump ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[6]->setStyleSheet(
        msg->brush.brush_actuator.moving_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[7]->setStyleSheet(
        msg->brush.brush_actuator.moving_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[8]->setStyleSheet(
        msg->brush.brush_actuator.hold_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[9]->setStyleSheet(
        msg->brush.brush_actuator.hold_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[10]->setStyleSheet(
        msg->vaccum.squeeze_actuator.moving_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[11]->setStyleSheet(
        msg->vaccum.squeeze_actuator.moving_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[12]->setStyleSheet(
        msg->vaccum.squeeze_actuator.hold_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[13]->setStyleSheet(
        msg->vaccum.squeeze_actuator.hold_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );
}

void A2_service::a2_faults_display(
    const test_tool::msg::A2FaultStatus::SharedPtr msg)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QHBoxLayout *brushMotorFaultsLayout = new QHBoxLayout;
    QHBoxLayout *vaccumMotorFaultsLayout = new QHBoxLayout;
    QLabel *faults_Label = new QLabel(this);
    QGroupBox *faults_Group = new QGroupBox("faults", this);

    QGroupBox *BrushMotor_faults_Group = new QGroupBox("Brush_Motor", this);
    QGroupBox *VaccumMotor_faults_Group = new QGroupBox("Vaccum_Motor", this);

    mainLayout->addWidget(faults_Group);
    mainLayout->addWidget(BrushMotor_faults_Group);
    mainLayout->addWidget(VaccumMotor_faults_Group);


    std::vector<uint8_t> fault_values = {

    msg->brush_vaccum_motor_driver_digital_fault,
    msg->brush_motor_actuator_fault,
    
    msg->drive_brush_current_digital_fault,
    msg->overcurrent_analog_fault,
    msg->temperature_fault,
    msg->undercurrent_analog_fault,

    msg->squeegee_actuator_digital_fault,
    msg->drive_brush_current_digital_fault,
    msg->overcurrent_analog_fault,
    msg->undercurrent_analog_fault,
    msg->water_pump_digital_fault,
    msg->deergent_pump_digital_fault,
    msg->water_and_detergent_pump_flow_fault
    };

    if(msg != nullptr)
    {
        if(msg->brush_vaccum_motor_driver_digital_fault){
            faults_Label->setText("Brush_Vaccum_Motor_Driver_Digital_Fault");
            faults_Group->setLayout(new QVBoxLayout);
            faults_Group->layout()->addWidget(faults_Label);
        }
    }else if(msg->brush_motor_actuator_fault){
        faults_Label->setText("Brush_Motor_Actuator_Fault");
        faults_Group->setLayout(new QVBoxLayout);
        faults_Group->layout()->addWidget(faults_Label);
     
    }else if(msg->drive_brush_current_digital_fault){
        faults_Label->setText("Drive_Brush_Current_Digital_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);
       
    }else if(msg->overcurrent_analog_fault){
        faults_Label->setText("Overcurrent_Analog_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->temperature_fault){
        faults_Label->setText("Temperature_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->undercurrent_analog_fault){
        faults_Label->setText("Undercurrent_Analog_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->squeegee_actuator_digital_fault){
        faults_Label->setText("Squeegee_Actuator_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->drive_brush_current_digital_fault){
        faults_Label->setText("Drive_Brush_Current_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->overcurrent_analog_fault){
        faults_Label->setText("Overcurrent_Analog_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->undercurrent_analog_fault){
        faults_Label->setText("Undercurrent_Analog_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->water_pump_digital_fault){
        faults_Label->setText("Water_Pump_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->deergent_pump_digital_fault){
        faults_Label->setText("Deergent_Pump_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->water_and_detergent_pump_flow_fault){
        faults_Label->setText("Water_and_Detergent_Pump_Flow_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);
    }

    setLayout(brushMotorFaultsLayout);
    setLayout(vaccumMotorFaultsLayout);
    setLayout(mainLayout);
}


void A2_service::brush_on_control()
{
    ui->brush_on->setStyleSheet(
        "background-color:#22c55e;");
    ui->brush_off->setStyleSheet(
        "");
    
    auto request = std::make_shared<test_tool::srv::A2Command::Request>();
    request->brush_command = 0 ;
    client_brush->async_send_request(request,
        [this](rclcpp::Client<test_tool::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->brush_status){
                ui->brush_status->setStyleSheet(
                        "background-color:#bbf7d0;");
                ui->brush_status->setText("Active");
            }
            else{
                ui->brush_status->setStyleSheet(
                    "background-color:#fecaca;");
                ui->brush_status->setText("Inactive");
            }
        });
}

void A2_service::brush_off_control()
{
    ui->brush_off->setStyleSheet(
        "background-color:#ef4444;"
    );
    ui->brush_on->setStyleSheet(
        ""
    );
    auto request = std::make_shared<test_tool::srv::A2Command::Request>();
    request->brush_command = 1;
    client_brush->async_send_request(request,
        [this](rclcpp::Client<test_tool::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->brush_status){
                lights[1]->setStyleSheet(LIGHT_GREEN_STYLE);
                ui->brush_status->setStyleSheet(
                    "background-color:#fecaca"
                );
                ui->brush_status->setText("Inactive");
            }
            else{
                lights[1]->setStyleSheet(LIGHT_RED_STYLE);
                ui->brush_status->setStyleSheet(
                    "background-color:#bbf7d0;"
                );
                ui->brush_status->setText("Active");
            }
        });
}

void A2_service::vaccum_on_control()
{
    ui->vaccum_on->setStyleSheet(
        "background-color:#22c55e;"
    );
    ui->vaccum_off->setStyleSheet(
        ""
    );
    ui->vaccum_status->setStyleSheet(
        "background-color:#bbf7d0;"
    );
    ui->vaccum_status->setText("Active");

    auto request = std::make_shared<test_tool::srv::A2Command::Request>();
    request->vacuum_command = 1;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<test_tool::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->vacuum_status){
                ui->vaccum_status->setStyleSheet(
                    "background-color:#bbf7d0;");
                ui->vaccum_status->setText("Active");
            }
            else{
                ui->vaccum_status->setStyleSheet(
                    "background-color:#fecaca;");
                ui->vaccum_status->setText("Inactive");
            }
        });
}

void A2_service::vaccum_off_control()
{
    ui->vaccum_off->setStyleSheet(
        "background-color:#ef4444;"
    );
    ui->vaccum_on->setStyleSheet(
        ""
    );
    ui->vaccum_status->setStyleSheet(
        "background-color:#fecaca;"
    );
    ui->vaccum_status->setText("Inactive");
    auto request = std::make_shared<test_tool::srv::A2Command::Request>();
    request->vacuum_command = 0;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<test_tool::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->vacuum_status){
                ui->vaccum_status->setStyleSheet(
                    "background-color:#bbf7d0;"
                );
                ui->vaccum_status->setText("Active");
            }
            else{
                ui->vaccum_status->setStyleSheet(
                    "background-color:#fecaca;"
                );
                ui->vaccum_status->setText("Inactive");
            }
        });
}

void A2_service::on_water_level_slider_valueChanged(int value)
{
    ui->percentage->setText(QString::number(value) + "%");

    auto message = std::make_shared<test_tool::msg::WaterLevel>();
    message->percentage = value;
    publisher->publish(*message);
}
