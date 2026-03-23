#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <filesystem>
#include <QDebug>
#include <QProcess>

namespace fs = std::filesystem;  // Add this for older compilers

MainWindow::MainWindow(rclcpp::Node::SharedPtr node,
    QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), listview(nullptr), model(nullptr), node_(node)
{
    ui->setupUi(this);

    connect(ui->launch_button, &QPushButton::clicked,
            this, &MainWindow::on_launch_button_clicked);
    // connect(ui->log_button, &QPushButton::clicked,
    //         this, &MainWindow::on_log_button_clicked);
    log_subscription_= node_->create_subscription<rcl_interfaces::msg::Log>("/rosout", 10,
        [this](const rcl_interfaces::msg::Log::SharedPtr msg){
           std::string node_name=msg->name;
           if (msg->level>= rcl_interfaces::msg::Log::ERROR){
               if (node_name=="test_logger_node"){
                    QMetaObject::invokeMethod(this, [=]() { // used for updating UI from non-UI thread
                        ui->pushButton_5->setStyleSheet("background-color: red;");
                    });
                    if (msg->level == rcl_interfaces::msg::Log::INFO)
                    {
                        QMetaObject::invokeMethod(this, [=]() { // used for updating UI from non-UI thread
                            ui->pushButton_5->setStyleSheet("background-color: green;");
                    });
                    }
                }else if (node_name=="lidar_node")
                {
                    QMetaObject::invokeMethod(this, [=]() {
                        ui->pushButton_6->setStyleSheet("background-color: red;");
                    });/* code */
                    if (msg->level == rcl_interfaces::msg::Log::INFO)
                    {
                        QMetaObject::invokeMethod(this, [=]() { // used for updating UI from non-UI thread
                            ui->pushButton_5->setStyleSheet("background-color: green;");
                    });
                    }
                }
                
            }
        });


}

MainWindow::~MainWindow()
{
}

void MainWindow::on_launch_button_clicked()
{
    if (listview) {
        listview = new QListView(this);

        QStringList launch_files;

        std::string path = "/opt/ros/humble/share/turtlesim/launch";
        launch_files <<"madhan"
                     <<"roots";

        for (const auto &entry : fs::directory_iterator(path))
        {
            if (entry.path().extension() == ".py")
            {
                launch_files << QString::fromStdString(entry.path().filename().string());
            }
        }

        model = new QStringListModel(launch_files);
        listview->setModel(model);

        listview->setGeometry(100, 100, 300, 200);
        listview->show();

        connect(listview,&QListView::clicked,this,
            [=](const QModelIndex &index){
                QString filename = model->data(index,Qt::DisplayRole).toString();
                QString fullpath = QString::fromStdString(path)+"/"+filename;
                qDebug()<<"selected file"<<fullpath;
                QProcess *process = new QProcess(this);
                process ->start("ros2",QStringList() <<"launch"<<"turtlesim"<<filename);
        });
    }else{
        listview->setVisible(!listview->isVisible());
        return;    
    }


}
// void MainWindow::on_log_button_clicked()
// {
//     logWidget = new QWidget(this);
//     logWidget->setStyleSheet("background-color: lightgray;");
//     logWidget->setWindowTitle("ROS2 Logs");
//     logWidget->setWindowFlags(Qt::Window );

//     QVBoxLayout *layout = new QVBoxLayout(logWidget);
//     QComboBox *logLevelComboBox = new QComboBox(logWidget);
//     logLevelComboBox->setMaximumWidth(150);
//     logLevelComboBox->addItems({"DEBUG", "INFO", "WARN", "ERROR", "FATAL"});
//     layout->addWidget(logLevelComboBox);

//     QTextEdit *textEdit = new QTextEdit(logWidget);
//     textEdit->setReadOnly(true);
//     layout->addWidget(textEdit);

//     logWidget->showMaximized();
// }


// void MainWindow::on_pushButton_5_clicked()
// {
//     ui->pushButton_5->setStyleSheet("background-color: red;");
// }

