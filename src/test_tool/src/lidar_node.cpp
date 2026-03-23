#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <chrono>
#include <random>

using namespace std::chrono_literals;

class LidarNode : public rclcpp::Node
{
public:
    LidarNode() : Node("lidar_node"), count_(0)
    {
        try {
            // Publisher
            publisher_ = this->create_publisher<sensor_msgs::msg::LaserScan>("scan", 10);

            // Timer (runs every 1 second)
            timer_ = this->create_wall_timer(
                1s, std::bind(&LidarNode::timer_callback, this));

            RCLCPP_INFO(this->get_logger(), "✅ Lidar node started");
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "❌ Initialization failed: %s", e.what());
        }
    }

private:
    void timer_callback()
    {
        try {
            count_++;

            // Create fake lidar message
            auto msg = sensor_msgs::msg::LaserScan();
            msg.header.stamp = this->get_clock()->now();
            msg.header.frame_id = "laser_frame";

            msg.angle_min = -1.57;
            msg.angle_max = 1.57;
            msg.angle_increment = 0.01;

            int size = (msg.angle_max - msg.angle_min) / msg.angle_increment;
            msg.ranges.resize(size);

            // Fill with random distances
            for (int i = 0; i < size; i++) {
                msg.ranges[i] = random_distance();
            }

            publisher_->publish(msg);

            // Normal log
            RCLCPP_INFO(this->get_logger(), "📡 Lidar running... count: %d", count_);

            // ⚠️ Warning simulation
            if (count_ == 3) {
                RCLCPP_WARN(this->get_logger(), "⚠️ Weak signal detected!");
            }

            // ❌ Error simulation
            if (count_ == 5) {
                RCLCPP_ERROR(this->get_logger(), "❌ Lidar sensor failure!");
            }

            // 💥 Exception simulation
            if (count_ == 7) {
                throw std::runtime_error("💥 Lidar hardware disconnected!");
            }

        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "❌ Exception caught: %s", e.what());
        }
    }

    float random_distance()
    {
        static std::default_random_engine eng(std::random_device{}());
        static std::uniform_real_distribution<float> dist(0.5, 10.0);
        return dist(eng);
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