#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <filesystem>
#include <QDebug>
#include <QProcess>

namespace fs = std::filesystem;  // Add this for older compilers

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), listview(nullptr), model(nullptr)
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