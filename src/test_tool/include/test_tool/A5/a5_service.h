#ifndef A5_SERVICE_H
#define A5_SERVICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QList>
#include <iris_interfaces/msg/UltrasonicRanges.hpp>
#include <iris_interfaces/msg/WheelEncoders.hpp>
#include <iris_interfaces/msg/WaterTankLevels.hpp>
#include <iris_interfaces/msg/A5Status.hpp>
#include <iris_interfaces/msg/LedControl.hpp>
#include <rclcpp/rclcpp.hpp>

class A5_service : public QWidget
{
    Q_OBJECT
public:
    explicit A5_service(QWidget *parent = nullptr);
    rclcpp::Node::Subscription<iris_interfaces::msg::UltrasonicRanges>::SharedPtr ultrasonic_sub;
    rclcpp::Node::Subscription<iris_interfaces::msg::WheelEncoders>::SharedPtr wheel_encoder_sub;
    rclcpp::Node::Subscription<iris_interfaces::msg::WaterTankLevels>::SharedPtr water_level_sub; 
    rclcpp::Node::Subscription<iris_interfaces::msg::A5Status>::SharedPtr a5_status_sub;
    rclcpp::Publisher<iris_interfaces::msg::LedControl>::SharedPtr led_command_publisher;

public slots:
    void setUltrasonicActive(int idx, bool active);
    void setEncoderValues(int left, int right);
    void setFreshWaterLevel(int percent);

signals:
    void ledCommandRequested(const QString &cmd);

private:
    // UI Setup Functions
    void setupUltrasonicSection(QBoxLayout *layout);
    void setupEncoderSection(QBoxLayout *layout);
    void setupLedSection(QBoxLayout *layout);
    void setupWaterSection(QBoxLayout *layout);

    // UI Members
    QList<QLabel*> ultrasonicLights;
    QLabel *encoderLeftLabel = nullptr;
    QLabel *encoderRightLabel = nullptr;
    QProgressBar *freshWaterBar = nullptr;
    QList<QPushButton*> ledButtons;
};

#endif // A5_SERVICE_H
