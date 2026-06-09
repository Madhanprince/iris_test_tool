#include "A5/a5_service.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QSizePolicy>
#include <QString>
#include <QThread>
#include <QDebug>

A5_service::A5_service(std::shared_ptr<Qtros> qtros_node ,QWidget *parent)
    : QWidget(parent), qtros(qtros_node)
{
    setupMainLayout();
    wheel_encoder_sub = qtros->create_subscription<iris_interfaces::msg::WheelEncoders>(
        "wheel_encoders", 10,
        [this](const iris_interfaces::msg::WheelEncoders::SharedPtr msg) {
            setEncoderValues(msg->left_wheel_ticks, msg->right_wheel_ticks);
        });
    
    ultrasonic_sub = qtros->create_subscription<iris_interfaces::msg::UltrasonicRanges>(
        "ultrasonic_ranges", 10,
        [this](const iris_interfaces::msg::UltrasonicRanges::SharedPtr msg) {
            setUltrasonicValues(msg->ultrasonic_1.range, msg->ultrasonic_2.range, 
                msg->ultrasonic_3.range, msg->ultrasonic_4.range);
        });
    water_level_sub = qtros->create_subscription<iris_interfaces::msg::WaterTankLevels>(
        "water_tank_levels", 10,
        [this](const iris_interfaces::msg::WaterTankLevels::SharedPtr msg) {
            setFreshWaterLevel(msg->fresh_water_tank_level);
            setDirtyWaterLevel(msg->dirty_water_tank_level);
        });
    // a5_status_sub = qtros->create_subscription<iris_interfaces::msg::A5Status>(
    //     "a5_control_status", 10,
    //     [this](const iris_interfaces::msg::A5Status::SharedPtr msg) {
    //             msg->mode_and_status ;
    //     });
    led_command_publisher = qtros->create_publisher<iris_interfaces::msg::LedControl>
                                                ("a5_control/led_control", 10);
    
    connect(this, &A5_service::ultrasonicValuesUpdated,
            this, &A5_service::on_ultrasonicValuesUpdated,
            Qt::QueuedConnection);
    connect(this, &A5_service::encoderValuesUpdated,
            this, &A5_service::on_encoderValuesUpdated,
            Qt::QueuedConnection);
    connect(this, &A5_service::freshWaterLevelUpdated,
            this, &A5_service::on_freshWaterLevelUpdated,
            Qt::QueuedConnection);  
    connect(this, &A5_service::dirtyWaterLevelUpdated,
            this, &A5_service::on_dirtyWaterLevelUpdated,
            Qt::QueuedConnection);
    // connect(this, &A5_service::a5_status_display,
    //         this, &A5_service::on_a5_status_display,
    //         Qt::QueuedConnection);
}

void A5_service::setupMainLayout()
{
    // =========================================================
    // Main Layout
    // =========================================================
    mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(4,4,4,4);
    mainLayout->setSpacing(6);
    // Keep everything at top
    mainLayout->setAlignment(Qt::AlignTop);

    // =========================================================
    // Group Boxes
    // =========================================================

    ultraBox = new QGroupBox("Ultrasonic Sensors");
    encBox = new QGroupBox("Wheel Encoders");
    ledBox = new QGroupBox("LED Commands");
    freshwaterBox = new QGroupBox("Fresh Water Level");
    dirtywaterBox = new QGroupBox("Dirty Water Level");


    // =========================================================
    // Prevent Vertical Stretching
    // =========================================================

    ultraBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    encBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    ledBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    freshwaterBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    dirtywaterBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);

    // =========================================================
    // Layouts Inside Group Boxes
    // =========================================================

    ultraLayout = new QVBoxLayout;
    encLayout = new QHBoxLayout;
    ledLayout = new QHBoxLayout;
    freshwaterLayout = new QVBoxLayout;
    dirtywaterLayout = new QVBoxLayout;

    ultraLayout->setSpacing(4);
    encLayout->setSpacing(10);
    ledLayout->setSpacing(8);
    freshwaterLayout->setSpacing(4);
    dirtywaterLayout->setSpacing(4);

    ultraBox->setLayout(ultraLayout);
    encBox->setLayout(encLayout);
    ledBox->setLayout(ledLayout);
    freshwaterBox->setLayout(freshwaterLayout);
    dirtywaterBox->setLayout(dirtywaterLayout);

    // =========================================================
    // Setup Each Section
    // =========================================================

    setupUltrasonicSection(ultraLayout);
    setupEncoderSection(encLayout);
    setupLedSection(ledLayout);
    setupFreshWaterSection(freshwaterLayout);
    setupDirtyWaterSection(dirtywaterLayout);

    // =========================================================
    // Add Group Boxes to Main Layout
    // =========================================================

    mainLayout->addWidget(ultraBox);
    mainLayout->addWidget(encBox);
    mainLayout->addWidget(ledBox);
    mainLayout->addWidget(freshwaterBox);
    mainLayout->addWidget(dirtywaterBox);

    // =========================================================
    // StyleSheet
    // =========================================================
    this->setStyleSheet(R"(
QGroupBox {
    background-color: #ffffff;
    border: 1px solid #e0e4eb;
    border-radius: 10px;
    margin-top: 14px;
    padding: 2px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    left: 12px;
    padding: 2px 10px;
    color: #1a6bdb;
    font-weight: 600;
    background-color: #ffffff;
    border-radius: 6px;
}

QPushButton {
    background-color: #ffffff;
    border: 1px solid #d1d5db;
    border-radius: 7px;
    padding: 5px 16px;
    font-size: 12px;
    min-height: 28px;
}

QPushButton:hover {
    background-color: #f3f6ff;
    border-color: #1a6bdb;
    color: #1a6bdb;
}

QWidget {
    background-color: #f0f2f5;
    font-family: "Segoe UI";
    font-size: 13px;
}

)");
    setLayout(mainLayout);
}

// =============================================================
// Setup Ultrasonic Section
// =============================================================

void A5_service::setupUltrasonicSection(QBoxLayout *layout)
{
    
    QStringList sensorNames = {
        "Ultrasonic 1 :",
        "Ultrasonic 2 :",
        "Ultrasonic 3 :",
        "Ultrasonic 4 :",
    };
    for (int i = 0; i < 4; ++i)
    {
        QVBoxLayout *row = new QVBoxLayout;
        QLabel *ultrasonic_label = new QLabel;
        QLabel *ultrasonic_value_label = new QLabel("0 cm");
        
        ultrasonic_value_label->setStyleSheet(
            "font-weight:600;"
            "font-size:14px;"
        );

        ultrasonic_label->setText(sensorNames[i]);
        ultrasonicLabels.append(ultrasonic_value_label);

        row->addWidget(ultrasonic_label);
        row->addWidget(ultrasonic_value_label);

        layout->addLayout(row);
    }

}

// =============================================================
// Setup Encoder Section
// =============================================================

void A5_service::setupEncoderSection(QBoxLayout *layout)
{
    QVBoxLayout *leftCol = new QVBoxLayout;
    QLabel *leftTitle = new QLabel("Left Wheel");
    encoderLeftLabel = new QLabel("0");

    encoderLeftLabel->setStyleSheet(
        "font-weight:600;"
        "font-size:14px;"
    );
    leftCol->addWidget(leftTitle);
    leftCol->addWidget(encoderLeftLabel);
    // --------------------------
    QVBoxLayout *rightCol = new QVBoxLayout;

    QLabel *rightTitle = new QLabel("Right Wheel");

    encoderRightLabel = new QLabel("0");

    encoderRightLabel->setStyleSheet(
        "font-weight:600;"
        "font-size:14px;"
    );

    rightCol->addWidget(rightTitle);
    rightCol->addWidget(encoderRightLabel);
    // --------------------------
    layout->addLayout(leftCol);
    layout->addSpacing(30);
    layout->addLayout(rightCol);
    layout->addStretch();
}

// =============================================================
// Setup LED Section
// =============================================================

void A5_service::setupLedSection(QBoxLayout *layout)
{
    const QString cmds[5] = {
        "OFF",
        "BOOTUP_WAIT",
        "STANDBY",
        "RUNNING",
        "ERROR"
    };

    for (int i = 0; i < 5; ++i)
    {
        QPushButton *button =
            new QPushButton(cmds[i]);

        button->setMinimumWidth(90);
        ledButtons.append(button);
        layout->addWidget(button);
        
    }
    layout->addStretch();
    connect(ledButtons[0], &QPushButton::clicked, [this]() { ledCommandRequested("OFF"); });
    connect(ledButtons[1], &QPushButton::clicked, [this]() { ledCommandRequested("BOOTUP_WAIT"); });
    connect(ledButtons[2], &QPushButton::clicked, [this]() { ledCommandRequested("STANDBY"); });
    connect(ledButtons[3], &QPushButton::clicked, [this]() { ledCommandRequested("RUNNING"); });
    connect(ledButtons[4], &QPushButton::clicked, [this]() { ledCommandRequested("ERROR"); });

}

// =============================================================
// Fresh Water Section
// =============================================================

void A5_service::setupFreshWaterSection(QBoxLayout *layout)
{
    freshWaterBar =
        new QProgressBar;

    freshWaterBar->setRange(0,100);

    freshWaterBar->setValue(0);

    layout->addWidget(freshWaterBar);
}

// =============================================================
// Dirty Water Section
// =============================================================
void A5_service::setupDirtyWaterSection(QBoxLayout *layout)
{
    dirtyWaterBar =
        new QProgressBar;

    dirtyWaterBar->setRange(0,100);

    dirtyWaterBar->setValue(0);

    layout->addWidget(dirtyWaterBar);

}

// =============================================================
// Subscriber callback functions to update UI " Signals "
// =============================================================

void A5_service::setUltrasonicValues(float ultrasonic1, float ultrasonic2, float ultrasonic3, float ultrasonic4) 
{
    emit ultrasonicValuesUpdated(ultrasonic1, ultrasonic2, ultrasonic3, ultrasonic4);
}

void A5_service::setEncoderValues(int left, int right)
{
    emit encoderValuesUpdated(left, right);
}

void A5_service::setFreshWaterLevel(int fresh_level)
{
    emit freshWaterLevelUpdated(fresh_level);
}
void A5_service::setDirtyWaterLevel(int dirty_level)
{
    emit dirtyWaterLevelUpdated(dirty_level);
}
// void A5_service::setA5Status(const iris_interfaces::msg::A5Status::SharedPtr msg)
// {
//     emit a5_status_display(msg);
// }
// =============================================================
// Subscriber callback functions to update UI " Slots "
// =============================================================

void A5_service::on_ultrasonicValuesUpdated(float ultrasonic1, float ultrasonic2, float ultrasonic3, float ultrasonic4)
{
    ultrasonicLabels[0]->setText(QString::number(ultrasonic1, 'f', 2) + " cm");
    ultrasonicLabels[1]->setText(QString::number(ultrasonic2, 'f', 2) + " cm");
    ultrasonicLabels[2]->setText(QString::number(ultrasonic3, 'f', 2) + " cm");
    ultrasonicLabels[3]->setText(QString::number(ultrasonic4, 'f', 2) + " cm");
}

void A5_service::ledCommandRequested(const QString &command)
{
    auto msg =
        std::make_shared<iris_interfaces::msg::LedControl>();

    if (command == "OFF")
    {
        msg->led_command =
            iris_interfaces::msg::LedControl::OFF;

        msg->left_indicator = 0;
        msg->right_indicator = 0;

        led_command_publisher->publish(*msg);
        RCLCPP_INFO(qtros->get_logger(), "Published LED Command : OFF");
    }
    else if (command == "BOOTUP_WAIT")
    {
        msg->led_command =
            iris_interfaces::msg::LedControl::BOOTUP_WAIT;

        msg->left_indicator = 1;
        msg->right_indicator = 1;

        led_command_publisher->publish(*msg);
        RCLCPP_INFO(qtros->get_logger(), "Published LED Command : BOOTUP_WAIT");
    }
    else if (command == "STANDBY")
    {
        msg->led_command =
            iris_interfaces::msg::LedControl::STANDBY;

        msg->left_indicator = 1;
        msg->right_indicator = 1;

        led_command_publisher->publish(*msg);
        RCLCPP_INFO(qtros->get_logger(), "Published LED Command : STANDBY");
    }
    else if (command == "RUNNING")
    {
        msg->led_command =
            iris_interfaces::msg::LedControl::RUNNING;

        // First state
        msg->left_indicator = 1;
        msg->right_indicator = 0;

        led_command_publisher->publish(*msg);

        QThread::msleep(300);

        // Second state
        msg->left_indicator = 0;
        msg->right_indicator = 1;

        led_command_publisher->publish(*msg);
        RCLCPP_INFO(qtros->get_logger(), "Published LED Command : RUNNING");
    }
    else if (command == "ERROR")
    {
        msg->led_command =
            iris_interfaces::msg::LedControl::ERROR;

        msg->left_indicator = 1;
        msg->right_indicator = 1;

        led_command_publisher->publish(*msg);
        RCLCPP_INFO(qtros->get_logger(), "Published LED Command : ERROR");
    }
    else
    {
        qDebug() << "Unknown LED Command :" << command;
        return;
    }

    qDebug() << "Published LED Command :" << command;
}


void A5_service::on_encoderValuesUpdated(int left, int right)
{
    if (encoderLeftLabel)
    {
        encoderLeftLabel->setText(QString::number(left));
    }
    if (encoderRightLabel)
    {
        encoderRightLabel->setText(QString::number(right));
    }
}

void A5_service::on_freshWaterLevelUpdated(int fresh_level){
    if (freshWaterBar)
    {
        freshWaterBar->setValue(qBound(0, fresh_level, 100));
    }
}

void A5_service::on_dirtyWaterLevelUpdated(int dirty_level){
    if (dirtyWaterBar)
    {
        dirtyWaterBar->setValue(qBound(0, dirty_level, 100));
    }
}

// void A5_service::on_a5_status_display(const iris_interfaces::msg::A5Status::SharedPtr msg)
// {
//     // Example: Update LED buttons based on mode
//     QString mode = QString::fromStdString(msg->mode_and_status);
//     for (QPushButton *button : ledButtons)
//     {
//         if (button->text() == mode)
//         {
//             button->setStyleSheet("background-color:#22c55e;"); // Active
//         }
//         else
//         {
//             button->setStyleSheet(""); // Default
//         }
//     }
// }

