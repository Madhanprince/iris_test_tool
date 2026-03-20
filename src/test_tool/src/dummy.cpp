#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <rclcpp/rclcpp.hpp>

class LoggerWindow : public QWidget
{
public:
    LoggerWindow(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr)
        : QWidget(parent), node_(node)
    {
        layout = new QVBoxLayout(this);

        textEdit = new QPlainTextEdit(this);
        textEdit->setReadOnly(true);

        layout->addWidget(textEdit);
    }

private:
    rclcpp::Node::SharedPtr node_;
    QVBoxLayout *layout;
    QPlainTextEdit *textEdit;
};

#include <QApplication>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("qt_logger_node");

    LoggerWindow window(node);
    window.show();

    std::thread ros_thread([&]() {
        rclcpp::spin(node);
    });

    int result = app.exec();

    rclcpp::shutdown();
    ros_thread.join();

    return result;
}