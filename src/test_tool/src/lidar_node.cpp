#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <chrono>
#include <random>
#include <fstream>  // 1. Include the file stream header
#include <filesystem>

using namespace std::chrono_literals;

class LidarNode : public rclcpp::Node
{
public:
    LidarNode() : Node("lidar_node"), count_(0)
    {
        // 2. Open the file (appends to existing content)
    std::string folder = "/home/maddy/iris_test_tool/src/test_tool/src/logfiles";
    std::filesystem::create_directories(folder);

    std::string file_path = folder + "/camera.txt";
    log_file_.open(file_path, std::ios::app);

    if (!log_file_.is_open()) {
        throw std::runtime_error("Failed to open log file!");
    }     

        publisher_ = this->create_publisher<sensor_msgs::msg::LaserScan>("scan", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&LidarNode::timer_callback, this));
        
        write_to_file("INFO: Lidar node started");
    }

    // 3. Destructor to ensure the file closes properly
    ~LidarNode() {
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }

private:
    void write_to_file(const std::string& message) {
        if (log_file_.is_open()) {
            // Add a timestamp or count for better records
            log_file_ << "[" << this->get_clock()->now().seconds() << "] " << message << std::endl;
        }
    }

    void timer_callback()
    {
        try {
            count_++;
            auto msg = sensor_msgs::msg::LaserScan();
            // ... (rest of your message logic) ...

            publisher_->publish(msg);
            
            // 4. Write logs to the file
            write_to_file("INFO: Lidar running... count: " + std::to_string(count_));

            if (count_ == 3) {
                write_to_file("WARN: Weak signal detected!");
            }

            if (count_ == 5) {
                write_to_file("ERROR: Lidar sensor failure!");
            }

            if (count_ == 7) {
                throw std::runtime_error("Lidar hardware disconnected!");
            }

        } catch (const std::exception &e) {
            write_to_file("EXCEPTION: " + std::string(e.what()));
            RCLCPP_ERROR(this->get_logger(), "Exception caught: %s", e.what());
        }
    }

    // ... (random_distance function) ...

    std::ofstream log_file_; // 5. File stream object
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char **argv)
{
    try {
        // 1. Initialize ROS 2
        rclcpp::init(argc, argv);

        // 2. Create the node instance
        // make_shared handles memory management for the LidarNode
        auto node = std::make_shared<LidarNode>();

        // 3. Keep the node running
        // This starts the timer and waits for callbacks
        rclcpp::spin(node);

        // 4. Shutdown ROS 2 when finished (e.g., Ctrl+C)
        rclcpp::shutdown();
    }
    catch (const std::exception &e) {
        // Catch any fatal errors that crash the node
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

// ... (main function) ...