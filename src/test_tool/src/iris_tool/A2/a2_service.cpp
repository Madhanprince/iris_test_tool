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
   
     // Thread-safe signal/slot connections (QueuedConnection = GUI thread safe) 
    connect(this, &A2_service::statusUpdated,
            this, &A2_service::onStatusUpdated,
            Qt::QueuedConnection);// Qt::QueuedConnection-  connection type

    connect(this, &A2_service::brushStatusUpdated,
            this, &A2_service::onBrushStatusUpdated,
            Qt::QueuedConnection);

    connect(this, &A2_service::vaccumStatusUpdated,
            this, &A2_service::onVaccumStatusUpdated,
            Qt::QueuedConnection);

    connect(this, &A2_service::faultsUpdated,
            this, &A2_service::onFaultsUpdated,
            Qt::QueuedConnection);

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
    "Hold_up", 
    "Hold_Down", 
    "Squeegee Actuator", 
    "Moving_up", 
    "Moving_Down", 
    "Hold_up", 
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
    emit statusUpdated(0, msg->brush.brush_motor_command);
    emit statusUpdated(1, msg->brush.brush_motor_status);
    emit statusUpdated(2, msg->vacuum.vacuum_motor_command);
    emit statusUpdated(3, msg->vacuum.vacuum_motor_status);
    emit statusUpdated(4, msg->water_pump);
    emit statusUpdated(5, msg->detergent_pump);
    emit statusUpdated(7,  msg->brush.brush_actuator.moving_up);
    emit statusUpdated(8,  msg->brush.brush_actuator.moving_down);
    emit statusUpdated(9,  msg->brush.brush_actuator.hold_up);
    emit statusUpdated(10, msg->brush.brush_actuator.hold_down);
    emit statusUpdated(12, msg->vacuum.squeeze_actuator.moving_up);
    emit statusUpdated(13, msg->vacuum.squeeze_actuator.moving_down);
    emit statusUpdated(14, msg->vacuum.squeeze_actuator.hold_up);
    emit statusUpdated(15, msg->vacuum.squeeze_actuator.hold_down);
}

void A2_service::onStatusUpdated(int index, bool isGreen)
{
    if (index < lights.size())
    {
        lights[index]->setStyleSheet(isGreen ? LIGHT_GREEN_STYLE : LIGHT_RED_STYLE);
    }
}

void A2_service::onBrushStatusUpdated(bool isActive)
{
    ui->brush_status->setStyleSheet(
        isActive ? LIGHT_GREEN_STYLE : LIGHT_RED_STYLE);
    ui->brush_status->setText(isActive ? "Active" : "Inactive");
}

void A2_service::onVaccumStatusUpdated(bool isActive)
{
    ui->vaccum_status->setStyleSheet(
        isActive ? LIGHT_GREEN_STYLE : LIGHT_RED_STYLE);
    ui->vaccum_status->setText(isActive ? "Active" : "Inactive");
}

void A2_service::onFaultsUpdated(QStringList activeFaults, int group)
{
    // Pick target layout based on group
    QLayout *targetLayout = nullptr;
    if      (group == 0) targetLayout = faults_Group_Layout;
    else if (group == 1) targetLayout = brushMotorFaultsLayout;
    else if (group == 2) targetLayout = vaccumMotorFaultsLayout;

    if (!targetLayout) return;

    // Clear old labels to avoid duplicates on each update
    QLayoutItem *item;
    while ((item = targetLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    // Create new fault labels safely on GUI thread
    for (const QString &faultName : activeFaults)
    {
        QLabel *label = new QLabel(faultName);
        targetLayout->addWidget(label);
    }

    // Re-apply layouts to group boxes
    faults_Group->setLayout(faults_Group_Layout);
    BrushMotor_faults_Group->setLayout(brushMotorFaultsLayout);
    VaccumMotor_faults_Group->setLayout(vaccumMotorFaultsLayout);
}

void A2_service::create_faults_group_box(){

    if (!ui_created)
    {
        faults_mainLayout = new QVBoxLayout;
        faults_Group_Layout = new QVBoxLayout;
        brushMotorFaultsLayout = new QVBoxLayout;
        vaccumMotorFaultsLayout = new QVBoxLayout;

        faults_Group =
            new QGroupBox("Faults", this);

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
    QStringList fault_names = {
        "brush_vacuum_motor_driver_digital_fault",
        "A2_Fault_Status",
        "Actuator_Digital_Fault",
        "Drive_Brush_Current_Digital_Fault",
        "Overcurrent_Analog_Fault",
        "Temperature_Fault",
        "Undercurrent_Analog_Fault",
        "Squeeze_Actuator_Digital_Fault",
        "Drive_Brush_Current_Digital_Fault",
        "Overcurrent_Analog_Fault",
        "Undercurrent_Analog_Fault",
        "Water_Pump_Digital_Fault",
        "Detergent_Pump_Digital_Fault",
        "Water_and_Detergent_Pump_Flow_Fault"
    };

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

    // Collect fault names per group — no widget creation here
    QStringList generalFaults;
    QStringList brushFaults;
    QStringList vaccumFaults;

    for (size_t i = 0; i < fault_values.size(); i++)
    {
        if (fault_values[i] == 1)
        {
            if (i <= 1)
                generalFaults << fault_names[i];
            else if (i >= 2 && i <= 6)
                brushFaults << fault_names[i];
            else
                vaccumFaults << fault_names[i];
        }
    }

    // Emit to GUI thread safely
    emit faultsUpdated(generalFaults, 0);
    emit faultsUpdated(brushFaults,   1);
    emit faultsUpdated(vaccumFaults,  2);
}

void A2_service::brush_on_control()
{
    ui->brush_on->setStyleSheet("background-color:#22c55e;");
    ui->brush_off->setStyleSheet("");

    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->brush_command = 1;
    client_brush_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            emit brushStatusUpdated(response->brush_status == 1);
        });
}

void A2_service::brush_off_control()
{
    ui->brush_off->setStyleSheet("background-color:#ef4444;");
    ui->brush_on->setStyleSheet("");

    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->brush_command = 0;
    client_brush_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            emit brushStatusUpdated(response->brush_status == 1);
        });
}

void A2_service::vaccum_on_control()
{
    ui->vaccum_on->setStyleSheet("background-color:#22c55e;");
    ui->vaccum_off->setStyleSheet("");

    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->vacuum_command = 1;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            emit vaccumStatusUpdated(response->vacuum_status == 1);
        });
}

void A2_service::vaccum_off_control()
{
    ui->vaccum_off->setStyleSheet("background-color:#ef4444;");
    ui->vaccum_on->setStyleSheet("");

    auto request = std::make_shared<iris_interfaces::srv::A2Command::Request>();
    request->vacuum_command = 0;
    client_vaccum_->async_send_request(request,
        [this](rclcpp::Client<iris_interfaces::srv::A2Command>::SharedFuture future)
        {
            auto response = future.get();
            emit vaccumStatusUpdated(response->vacuum_status == 1);
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