#include "qt_ros.h"


Qtros::Qtros() : Node("iris_tool") {
    
    Qtros::subscription = this->create_subscription<rcl_interfaces::msg::Log>(
        "/rosout", 10, std::bind(&Qtros::logscallback, this, std::placeholders::_1));
}

void Qtros::logscallback(const rcl_interfaces::msg::Log::SharedPtr msg) {
    emit logReceived(
        QString::fromStdString(msg->msg),
        QString::fromStdString("/"+msg->name),
        msg->level
    );// Emit the signal with the received message

    
 }