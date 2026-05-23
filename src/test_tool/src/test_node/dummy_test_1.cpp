#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <chrono>

using namespace std::chrono_literals;

class LidarNode : public rclcpp::Node
{
public:
    LidarNode() : Node("dummy_node_1"), count_(0)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::LaserScan>("dummy_1", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&LidarNode::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Lidar node started");
    }

private:
    void timer_callback()
    {
        try {
            count_++;

            auto msg = sensor_msgs::msg::LaserScan();
            // (You can fill message fields if needed)

            publisher_->publish(msg);

            RCLCPP_INFO(this->get_logger(), "Lidar running... count: %d", count_);

            if (count_ == 3) {
                RCLCPP_WARN(this->get_logger(), "Weak signal detected!");
            }

            if (count_ == 5) {
                RCLCPP_ERROR(this->get_logger(), "Lidar sensor failure!");
            }

            if (count_ == 7) {
                throw std::runtime_error("Lidar hardware disconnected!");
            }

        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Exception caught: %s", e.what());
        }
    }

    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char **argv)
{
    try {
        rclcpp::init(argc, argv);

        auto node = std::make_shared<LidarNode>();

        rclcpp::spin(node);

        rclcpp::shutdown();
    }
    catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}