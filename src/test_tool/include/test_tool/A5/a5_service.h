#ifndef A5_SERVICE_H
#define A5_SERVICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QList>
#include <QBoxLayout>
#include <iris_interfaces/msg/ultrasonic_ranges.hpp>
#include <iris_interfaces/msg/wheel_encoders.hpp>
#include <iris_interfaces/msg/water_tank_levels.hpp>
#include <iris_interfaces/msg/a5_status.hpp>
#include <iris_interfaces/msg/led_control.hpp>
#include <rclcpp/rclcpp.hpp>
#include "qt_ros.h"
#include <memory>

class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;

class A5_service : public QWidget
{
    Q_OBJECT
public:
    explicit A5_service(std::shared_ptr<Qtros> qtros_node, QWidget *parent = nullptr);
    
    std::shared_ptr<Qtros> qtros;
    rclcpp::Subscription<iris_interfaces::msg::UltrasonicRanges>::SharedPtr ultrasonic_sub;
    rclcpp::Subscription<iris_interfaces::msg::WheelEncoders>::SharedPtr wheel_encoder_sub;
    rclcpp::Subscription<iris_interfaces::msg::WaterTankLevels>::SharedPtr water_level_sub; 
    rclcpp::Subscription<iris_interfaces::msg::A5Status>::SharedPtr a5_status_sub;
    rclcpp::Publisher<iris_interfaces::msg::LedControl>::SharedPtr led_command_publisher;

    void setUltrasonicValues(float ultrasonic1, float ultrasonic2, float ultrasonic3);
    void setEncoderValues(int left, int right);
    void setFreshWaterLevel(int fresh_level);
    void setDirtyWaterLevel(int dirty_level);

private:
    // UI Setup Functions
    void setupMainLayout();
    void setupUltrasonicSection(QBoxLayout *layout);
    void setupEncoderSection(QBoxLayout *layout);
    void setupLedSection(QBoxLayout *layout);
    void setupFreshWaterSection(QBoxLayout *layout);
    void setupDirtyWaterSection(QBoxLayout *layout);

    // UI Members
    QVBoxLayout *mainLayout = nullptr;
    QVBoxLayout *ultraLayout = nullptr;
    QHBoxLayout *encLayout = nullptr;
    QHBoxLayout *ledLayout = nullptr;
    QVBoxLayout *freshwaterLayout = nullptr;
    QVBoxLayout *dirtywaterLayout = nullptr;

    QGroupBox *ultraBox = nullptr;
    QGroupBox *encBox = nullptr;
    QGroupBox *ledBox = nullptr;
    QGroupBox *freshwaterBox = nullptr;
    QGroupBox *dirtywaterBox = nullptr;

    QLabel *encoderLeftLabel = nullptr;
    QLabel *encoderRightLabel = nullptr;
    QProgressBar *freshWaterBar = nullptr;
    QProgressBar *dirtyWaterBar = nullptr;
    QList<QPushButton*> ledButtons;
    QLabel *ultra_value = nullptr;
Slots:
    void freshWaterLevelUpdated(int fresh_level);
    void dirtyWaterLevelUpdated(int dirty_level);
    void ultrasonicValuesUpdated(float ultrasonic1, float ultrasonic2, float ultrasonic3);
    void encoderValuesUpdated(int left, int right);
    void a5_status_display(const iris_interfaces::msg::A5Status::SharedPtr msg);    
    // void ledButtonClicked(int index);
Signals:
    // void ledCommandUpdated(int index, bool state);
    void a5_status_updated(const iris_interfaces::msg::A5Status::SharedPtr msg);
    void setUltrasonicValues(float ultrasonic1, float ultrasonic2, float ultrasonic3);
    void setEncoderValues(int left, int right);
    void setFreshWaterLevel(int fresh_level);
    void setDirtyWaterLevel(int dirty_level);

};

#endif // A5_SERVICE_H
