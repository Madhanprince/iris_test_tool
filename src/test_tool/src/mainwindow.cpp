#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <filesystem>
#include <QDebug>
#include <QProcess>
#include <iostream>
#include <filesystem>
#include <QDir>
#include <QString>

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
        std::bind(&MainWindow::logcallback, this, std::placeholders::_1));
        


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
void MainWindow::on_log_button_clicked()
{
    logWidget = new QWidget(this);
    logWidget->setStyleSheet("background-color: lightgray;");
    logWidget->setWindowTitle("ROS2 Logs");
    logWidget->setWindowFlags(Qt::Window);

    QVBoxLayout *layout = new QVBoxLayout(logWidget);
    QComboBox *logLevelComboBox = new QComboBox(logWidget);
    logLevelComboBox->setMaximumWidth(150);

    QStringList text_file;
    QDir diretory;
    QString path = "/home/maddy/iris_test_tool/src/test_tool/src/logfiles";

    // 1. Define the specific path
    QDir directory(path);

// 2. Filter for only .txt files
    QStringList filters;
    filters << "*.txt";
    directory.setNameFilters(filters);

// 3. Get the list of files and add them to the box
    QStringList text_files = directory.entryList(QDir::Files);
    logLevelComboBox->addItems(text_files);
    layout->addWidget(logLevelComboBox);

    QTextEdit *textEdit = new QTextEdit(logWidget);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);

    logWidget->showMaximized();

    
}


void MainWindow::logcallback(const rcl_interfaces::msg::Log::SharedPtr msg)
{
    std::string node_name=msg->name;
    if (node_name == "test_logger_node")
    {
        switch (msg->level)
        {
            case rcl_interfaces::msg::Log::ERROR:
            case rcl_interfaces::msg::Log::FATAL:
                QMetaObject::invokeMethod(this, [=]() {
                ui->pushButton_5->setStyleSheet("background-color: red;");
            });
            break;

            case rcl_interfaces::msg::Log::INFO:
                QMetaObject::invokeMethod(this, [=]() {
                ui->pushButton_5->setStyleSheet("background-color: green;");
                });
            break;
        }
    }
    if(node_name == "lidar_node")
    {
        switch (msg->level)
        {
            case rcl_interfaces::msg::Log::ERROR:
            case rcl_interfaces::msg::Log::FATAL:
                QMetaObject::invokeMethod(this, [=]() {
                ui->pushButton_6->setStyleSheet("background-color: red;");
            });
            break;
            case rcl_interfaces::msg::Log::INFO:
                QMetaObject::invokeMethod(this, [=]() {
                ui->pushButton_6->setStyleSheet("background-color: green;");
                });        
        }   
    }
}
