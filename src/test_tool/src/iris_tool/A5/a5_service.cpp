#include "A5/a5_service.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QSizePolicy>
#include <QString>
#include "A5/a5_service.h"

A5_service::A5_service(QWidget *parent)
    : QWidget(parent)
{

    wheel_encoder_sub = qtros->create_subscription<iris_interfaces::msg::WheelEncoders>(
        "wheel_encoders", 10,
        [this](const iris_interfaces::msg::WheelEncoders::SharedPtr msg) {
            setEncoderValues(msg->left_wheel_ticks, msg->right_wheel_ticks);
        });
    
    ultrasonic_sub = qtros->create_subscription<iris_interfaces::msg::UltrasonicRanges>(
        "ultrasonic_ranges", 10,
        [this](const iris_interfaces::msg::UltrasonicRanges::SharedPtr msg) {
            setUltrasonicValues(msg->ultrasonic_1_active, msg->ultrasonic_2_active, 
                msg->ultrasonic_3_active);
        });
    water_level_sub = qtros->create_subscription<iris_interfaces::msg::WaterTankLevels>(
        "water_tank_levels", 10,
        [this](const iris_interfaces::msg::WaterTankLevels::SharedPtr msg) {
            setFreshWaterLevel(msg->fresh_water_tank_level , 
                msg->dirty_water_tank_level );
        });
    a5_status_sub = qtros->create_subscription<iris_interfaces::msg::A5Status>(
        "a5_control_status", 10,
        [this](const iris_interfaces::msg::A5Status::SharedPtr msg) {
                msg->mode_and_status ;
        });
    led_command_publisher = qtros->create_publisher<iris_interfaces::msg::LedControl>("led_command", 10);
    
    // =========================================================
    // Main Layout
    // =========================================================
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(4,4,4,4);
    mainLayout->setSpacing(6);
    // Keep everything at top
    mainLayout->setAlignment(Qt::AlignTop);

    // =========================================================
    // Group Boxes
    // =========================================================

    QGroupBox *ultraBox = new QGroupBox("Ultrasonic Sensors");
    QGroupBox *encBox = new QGroupBox("Wheel Encoders");
    QGroupBox *ledBox = new QGroupBox("LED Commands");
    QGroupBox *waterBox = new QGroupBox("Fresh Water Level");

    // =========================================================
    // Prevent Vertical Stretching
    // =========================================================

    ultraBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    encBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    ledBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    waterBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);

    // =========================================================
    // Layouts Inside Group Boxes
    // =========================================================

    QVBoxLayout *ultraLayout = new QVBoxLayout;
    QHBoxLayout *encLayout = new QHBoxLayout;
    QHBoxLayout *ledLayout = new QHBoxLayout;
    QVBoxLayout *waterLayout = new QVBoxLayout;

    ultraLayout->setSpacing(4);
    encLayout->setSpacing(10);
    ledLayout->setSpacing(8);
    waterLayout->setSpacing(4);

    ultraBox->setLayout(ultraLayout);
    encBox->setLayout(encLayout);
    ledBox->setLayout(ledLayout);
    waterBox->setLayout(waterLayout);

    // =========================================================
    // Setup Each Section
    // =========================================================

    setupUltrasonicSection(ultraLayout);
    setupEncoderSection(encLayout);
    setupLedSection(ledLayout);
    setupWaterSection(waterLayout);

    // =========================================================
    // Add Group Boxes to Main Layout
    // =========================================================

    mainLayout->addWidget(ultraBox);
    mainLayout->addWidget(encBox);
    mainLayout->addWidget(ledBox);
    mainLayout->addWidget(waterBox);

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
    const QString sensorNames[3] = {
        "Ultrasonic 1",
        "Ultrasonic 2",
        "Ultrasonic 3"
    };

    for (int i = 0; i < 3; ++i)
    {
        QHBoxLayout *row = new QHBoxLayout;
        QLabel *light = new QLabel;
        light->setFixedSize(14,14);
        light->setStyleSheet(
            "background-color:#ef4444;"
            "border-radius:7px;"
        );

        QLabel *label =
            new QLabel(sensorNames[i]);

        row->addWidget(light);
        row->addSpacing(6);
        row->addWidget(label);
        row->addStretch();
        layout->addLayout(row);
        ultrasonicLights.append(light);
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
        connect(button,
                &QPushButton::clicked,
                this,
                [this, button]()
        {
            emit ledCommandRequested(
                button->text()
            );
        });
    }
    layout->addStretch();
}

// =============================================================
// Setup Water Section
// =============================================================

void A5_service::setupWaterSection(QBoxLayout *layout)
{
    freshWaterBar =
        new QProgressBar;

    freshWaterBar->setRange(0,100);

    freshWaterBar->setValue(0);

    layout->addWidget(freshWaterBar);
}

// =============================================================
// Fresh Water Level
// =============================================================

void A5_service::setFreshWaterLevel(int percent)
{
    if (freshWaterBar)
    {
        freshWaterBar->setValue(
            qBound(0, percent, 100)
        );
    }
}
