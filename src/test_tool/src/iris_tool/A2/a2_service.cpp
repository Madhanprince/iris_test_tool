#include "A2/a2_service.h"
#include <QStringList>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"



A2_service::A2_service(Ui::MainWindow *mainUi,
                       std::shared_ptr<Qtros> qtros_node,
                       QWidget *parent)
    : QWidget(parent),
      ui(mainUi),
      qtros(qtros_node)
{
    client_brush_ = qtros->create_client<iris_interfaces::srv::A2Command>("a2_control/a2_command");
    client_vaccum_ = qtros->create_client<iris_interfaces::srv::A2Command>("a2_control/a2_command");

    publisher_ = qtros->create_publisher<iris_interfaces::msg::A2Command>("water_level", 10);
    brush_vaccum_status_subscriber = qtros->create_subscription<iris_interfaces::msg::A2FunctionalStatus>(
        "/a2_status",
        10,std::bind(
            &A2_service::a2_status_display,
            this,
            std::placeholders::_1
        )
    );
    brush_vaccum_faults_subscriber = qtros->create_subscription<iris_interfaces::msg::A2FaultStatus>(
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
    create_faults_group_box();
}

QStringList status_messages = {
    "Brush_Command_received", 
    "Brush_Motor_ON",
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
    const iris_interfaces::msg::A2FunctionalStatus::SharedPtr msg)
{
    std::cout << "Received A2 Status Update" << std::endl;

    lights[0]->setStyleSheet(
        msg->brush.brush_motor_command?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[1]->setStyleSheet(
        msg->brush.brush_motor_status ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[2]->setStyleSheet(
        msg->vacuum.vacuum_motor_command ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[3]->setStyleSheet(
        msg->vacuum.vacuum_motor_status ?
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
        msg->vacuum.squeeze_actuator.moving_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[11]->setStyleSheet(
        msg->vacuum.squeeze_actuator.moving_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[12]->setStyleSheet(
        msg->vacuum.squeeze_actuator.hold_up ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

    lights[13]->setStyleSheet(
        msg->vacuum.squeeze_actuator.hold_down ?
        LIGHT_RED_STYLE : LIGHT_GREEN_STYLE
    );

}

void A2_service::create_faults_group_box(){

    if (!ui_created)
    {
        faults_mainLayout = new QVBoxLayout;
        faults_Group_Layout = new QVBoxLayout;
        brushMotorFaultsLayout = new QHBoxLayout;
        vaccumMotorFaultsLayout = new QHBoxLayout;

        faults_Label = new QLabel;

        faults_Group =
            new QGroupBox("faults", this);

        BrushMotor_faults_Group =
            new QGroupBox("Brush_Motor", this);

        VaccumMotor_faults_Group =
            new QGroupBox("Vaccum_Motor", this);

        // Add layouts/widgets here
        ui_created = true;
        faults_mainLayout->addWidget(faults_Group);
        faults_mainLayout->addWidget(BrushMotor_faults_Group);
        faults_mainLayout->addWidget(VaccumMotor_faults_Group);
        std::cout << "Fault UI Created Once" << std::endl;
    }

    ui->fault_box->setLayout(faults_mainLayout);
}

void A2_service::a2_faults_display(
    const iris_interfaces::msg::A2FaultStatus::SharedPtr msg)
{
    
    std::vector<uint8_t> fault_values = {

    msg->brush_vacuum_motor_driver_digital_fault,
    msg->a2_fault_status,
    
    msg->brush.actuator_digital_fault,
    msg->brush.drive_brush_current_digital_fault,
    msg->brush.overcurrent_analog_fault,
    msg->brush.temperature_fault,
    msg->brush.undercurrent_analog_fault,

    msg->vacuum.squeeze_actuator_digital_fault,
    msg->vacuum.drive_brush_current_digital_fault,
    msg->vacuum.overcurrent_analog_fault,
    msg->vacuum.undercurrent_analog_fault,
    msg->water_pump_digital_fault,
    msg->detergent_pump_digital_fault,
    msg->water_and_detergent_pump_flow_fault
   
    };
    if(msg){
        if(msg->brush_vacuum_motor_driver_digital_fault){
            faults_Label->setText("brush_vacuum_motor_driver_digital_fault");
            faults_Group_Layout->addWidget(faults_Label);
        }
    }else if(msg->a2_fault_status){
        faults_Label->setText("A2_Fault_Status");
        faults_Group_Layout->addWidget(faults_Label);

    }else if(msg->brush.drive_brush_current_digital_fault){
        faults_Label->setText("Drive_Brush_Current_Digital_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);
       
    }else if(msg->brush.overcurrent_analog_fault){
        faults_Label->setText("Overcurrent_Analog_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->brush.temperature_fault){
        faults_Label->setText("Temperature_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->brush.undercurrent_analog_fault){
        faults_Label->setText("Undercurrent_Analog_Fault");
        brushMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->vacuum.squeeze_actuator_digital_fault){
        faults_Label->setText("squeeze_actuator_digital_fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->vacuum.drive_brush_current_digital_fault){
        faults_Label->setText("Drive_Brush_Current_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->vacuum.overcurrent_analog_fault){
        faults_Label->setText("Overcurrent_Analog_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->vacuum.undercurrent_analog_fault){
        faults_Label->setText("Undercurrent_Analog_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->water_pump_digital_fault){
        faults_Label->setText("Water_Pump_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->detergent_pump_digital_fault){
        faults_Label->setText("Detergent_Pump_Digital_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);

    }else if(msg->water_and_detergent_pump_flow_fault){
        faults_Label->setText("Water_and_Detergent_Pump_Flow_Fault");
        vaccumMotorFaultsLayout->addWidget(faults_Label);
    }

}

void A2_service::brush_on_control()
{
    ui->brush_on->setStyleSheet(
        "background-color:#22c55e;");
    ui->brush_off->setStyleSheet(
        "");
    
    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->brush_command = 1;
    client_brush_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
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
    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->brush_command = 0;
    client_brush_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->brush_status){
    
                ui->brush_status->setStyleSheet(
                    "background-color:#fecaca"
                );
                ui->brush_status->setText("Inactive");
            }
            else{
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
   
    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->vacuum_command = 1;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
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
    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->vacuum_command = 0;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            if(response->vacuum_status){
                ui->vaccum_status->setStyleSheet(
                    "background-color:#fecaca;"
                );
                ui->vaccum_status->setText("Inactive");
            }
            else{
                ui->vaccum_status->setStyleSheet(
                    "background-color:#bbf7d0;"
                );
                ui->vaccum_status->setText("Active");
            }
        });
}

void A2_service::on_water_level_slider_valueChanged(int value)
{
    ui->percentage->setText(QString::number(value) + "%");

    auto message = std::make_shared<iris_interfaces::msg::A2Command>();
    message->pump_flow_rate = value;
    publisher_->publish(*message);
    RCLCPP_INFO(rclcpp::get_logger("A2_service"), "Publishing water level: %d%%", value);
}
