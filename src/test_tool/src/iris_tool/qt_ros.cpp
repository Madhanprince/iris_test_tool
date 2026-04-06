#include "qt_ros.h"

Qtros::Qtros() : rclcpp::Node("iris_tool")  {

    Qtros::subscription = create_subscription<rcl_interfaces::msg::Log>(
        "/rosout", 10, std::bind(&Qtros::logscallback, this, std::placeholders::_1));
    }

void Qtros::logscallback(const rcl_interfaces::msg::Log::SharedPtr msg) {
    emit logReceived(
        QString::fromStdString(msg->name),
        QString::fromStdString(msg->msg),
        msg->level
    );// Emit the signal with the received message

    
 }