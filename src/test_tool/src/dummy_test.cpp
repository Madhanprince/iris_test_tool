// #include <QWidget>
// #include <QVBoxLayout>
// #include <QPlainTextEdit>
// #include <rclcpp/rclcpp.hpp>

// class LoggerWindow : public QWidget
// {
// public:
//     LoggerWindow(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr)
//         : QWidget(parent), node_(node)
//     {
//         layout = new QVBoxLayout(this);

//         textEdit = new QPlainTextEdit(this);
//         textEdit->setReadOnly(true);

//         layout->addWidget(textEdit);
//     }

// private:
//     rclcpp::Node::SharedPtr node_;
//     QVBoxLayout *layout;
//     QPlainTextEdit *textEdit;
// };

// #include <QApplication>

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);
//     QApplication app(argc, argv);

//     auto node = std::make_shared<rclcpp::Node>("qt_logger_node");

//     LoggerWindow window(node);
//     window.show();

//     std::thread ros_thread([&]() {
//         rclcpp::spin(node);
//     });

//     int result = app.exec();

//     rclcpp::shutdown();
//     ros_thread.join();

//     return result;
// }

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>

using namespace std::chrono_literals;

class TestLoggerNode : public rclcpp::Node
{
public:
    TestLoggerNode() : Node("test_logger_node")
    {
        try {
            // Create timer
            timer_ = this->create_wall_timer(
                1s, std::bind(&TestLoggerNode::timer_callback, this));

            RCLCPP_INFO(this->get_logger(), "Node started successfully!");
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Initialization failed: %s", e.what());
        }
    }

private:
    void timer_callback()
    {
        try {
            count_++;

            // Normal log
            RCLCPP_INFO(this->get_logger(), "Running count: %d", count_);

            // Generate warning
            if (count_ == 3) {
                RCLCPP_WARN(this->get_logger(), "This is a warning test!");
            }

            // Generate error
            if (count_ == 5) {
                RCLCPP_ERROR(this->get_logger(), "This is a test ERROR!");
            }

            // Force exception
            if (count_ == 7) {
                throw std::runtime_error("Manual exception triggered!");
            }
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Exception caught: %s", e.what());
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int count_ = 0;
};

int main(int argc, char **argv)
{
    try {
        rclcpp::init(argc, argv);

        auto node = std::make_shared<TestLoggerNode>();

        rclcpp::spin(node);

        rclcpp::shutdown();
    }
    catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred!" << std::endl;
        return -1;
    }

    return 0;
}