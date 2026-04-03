#include <rclcpp/rclcpp.hpp>
#include <rcl_interfaces/msg/log.hpp>
#include <QObject>


class Qtros : public QObject, public rclcpp::Node
{
    Q_OBJECT   // needed for signals

public:
    Qtros();

signals:
    void logReceived(const QString &name, const QString &msg, int level); // signal to emit logs to MainWindow

private:
    void logscallback(const rcl_interfaces::msg::Log::SharedPtr msg); // callback for ROS logs
    rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr subscription;
};
