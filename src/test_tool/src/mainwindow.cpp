#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <filesystem>

namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), listview(nullptr)
{
    ui->setupUi(this);

    connect(ui->launch_button, &QPushButton::clicked,
            this, &MainWindow::on_launch_button_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_launch_button_clicked()
{
    // Toggle close
    // if (listview) {
    //     listview->close();
    //     delete listview;
    //     return;
    // }

    listview = new QListView(this);

    QStringList launch_files;

    std::string path = "/home/maddy/iris_test_tool/src/ros_tutorials/turtlesim/launch";
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


}
