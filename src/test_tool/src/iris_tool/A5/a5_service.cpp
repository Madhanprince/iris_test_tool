#include "A5/a5_service.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QString>
#include <QFont>
#include <QSpacerItem>

A5_service::A5_service(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(6,6,6,6);
    mainLayout->setSpacing(8);

    // Try to find group boxes in the parent UI (created by Qt Designer)
    QWidget *p = parentWidget();

    QGroupBox *ultraBox = nullptr;
    QGroupBox *encBox = nullptr;
    QGroupBox *ledBox = nullptr;
    QGroupBox *waterBox = nullptr;

    if (p) {
        ultraBox = p->findChild<QGroupBox *>("groupBox_2");
        encBox = p->findChild<QGroupBox *>("groupBox_3");
        ledBox = p->findChild<QGroupBox *>("groupBox_4");
        waterBox = p->findChild<QGroupBox *>("groupBox_5");
    }

    // If any group missing, create local ones and add to mainLayout
    
    if (!ultraBox) {
        ultraBox = new QGroupBox("Ultrasonic Sensors", this);
        mainLayout->addWidget(ultraBox);
    }
    if (!encBox) {
        encBox = new QGroupBox("Wheel Encoders (live)", this);
        mainLayout->addWidget(encBox);
    }
    if (!ledBox) {
        ledBox = new QGroupBox("LED Commands", this);
        mainLayout->addWidget(ledBox);
    }
    if (!waterBox) {
        waterBox = new QGroupBox("Fresh Water Level", this);
        mainLayout->addWidget(waterBox);
    }

    // Ensure each target box has a QBoxLayout so we can use spacing/stretch methods
    auto ensureBoxLayout = [](QGroupBox *box, bool horizontal)->QBoxLayout* {
        if (!box->layout()) {
            if (horizontal)
                box->setLayout(new QHBoxLayout(box));
            else
                box->setLayout(new QVBoxLayout(box));
        }
        return qobject_cast<QBoxLayout*>(box->layout());
    };

    QBoxLayout *ultraLayout = ensureBoxLayout(ultraBox, false);
    QBoxLayout *encLayout = ensureBoxLayout(encBox, true);
    QBoxLayout *ledLayout = ensureBoxLayout(ledBox, true);
    QBoxLayout *waterLayout = ensureBoxLayout(waterBox, false);

    // Populate Ultrasonic layout
    const QString sensorNames[3] = {"Ultrasonic 1", "Ultrasonic 2", "Ultrasonic 3"};
    for (int i = 0; i < 3; ++i) {
        QHBoxLayout *row = new QHBoxLayout;
        QLabel *light = new QLabel;
        light->setFixedSize(14,14);
        light->setStyleSheet("background-color:#ef4444;border-radius:7px;"); // default red
        QLabel *label = new QLabel(sensorNames[i]);
        label->setMinimumWidth(120);
        row->addWidget(light);
        row->addSpacing(8);
        row->addWidget(label);
        row->addStretch();
        ultraLayout->addLayout(row);
        ultrasonicLights.append(light);
    }

    // Populate Encoder layout
    QVBoxLayout *leftCol = new QVBoxLayout;
    QLabel *leftTitle = new QLabel("Left Wheel");
    encoderLeftLabel = new QLabel("0");
    encoderLeftLabel->setStyleSheet("font-weight:600;font-size:14px;");
    leftCol->addWidget(leftTitle);
    leftCol->addWidget(encoderLeftLabel);

    QVBoxLayout *rightCol = new QVBoxLayout;
    QLabel *rightTitle = new QLabel("Right Wheel");
    encoderRightLabel = new QLabel("0");
    encoderRightLabel->setStyleSheet("font-weight:600;font-size:14px;");
    rightCol->addWidget(rightTitle);
    rightCol->addWidget(encoderRightLabel);

    encLayout->addLayout(leftCol);
    encLayout->addSpacing(16);
    encLayout->addLayout(rightCol);
    encLayout->addStretch();

    // Populate LED buttons
    const QString cmds[5] = {"OFF","BOOTUP_WAIT","STANDBY","RUNNING","ERROR"};
    for (int i = 0; i < 5; ++i) {
        QPushButton *b = new QPushButton(cmds[i]);
        b->setMinimumWidth(86);
        ledLayout->addWidget(b);
        ledButtons.append(b);
        connect(b, &QPushButton::clicked, this, [this, b]() {
            emit ledCommandRequested(b->text());
        });
    }
    ledLayout->addStretch();

    // Populate water progress
    freshWaterBar = new QProgressBar;
    freshWaterBar->setRange(0,100);
    // freshWaterBar->setValue(0);
    waterLayout->addWidget(freshWaterBar);

    // If we used local group boxes we've already added them to mainLayout; otherwise mainLayout remains unused but that's fine.
    setLayout(mainLayout);
}

void A5_service::setUltrasonicActive(int idx, bool active)
{
    if (idx < 0 || idx >= ultrasonicLights.size()) return;
    if (active)
        ultrasonicLights[idx]->setStyleSheet("background-color:#22c55e;border-radius:7px;");
    else
        ultrasonicLights[idx]->setStyleSheet("background-color:#ef4444;border-radius:7px;");
}

void A5_service::setEncoderValues(int left, int right)
{
    if (encoderLeftLabel) encoderLeftLabel->setText(QString::number(left));
    if (encoderRightLabel) encoderRightLabel->setText(QString::number(right));
}

void A5_service::setFreshWaterLevel(int percent)
{
    if (freshWaterBar) freshWaterBar->setValue(qBound(0, percent, 100));
}
