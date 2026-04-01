#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 🔷 Sidebar → Page Switching
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            this, [=](int row){
                pages(row);
    });

    // 🔷 Default page
    ui->listWidget->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pages(int row)
{
    if (row == 0) {
        ui->stackedWidget->setCurrentIndex(row);
    }
    else if (row == 1) {
        ui->stackedWidget->setCurrentIndex(row);
        logs_op();
    }
    else if (row == 2) {
        ui->stackedWidget->setCurrentIndex(row);
    }
    else if (row == 3) {
        ui->stackedWidget->setCurrentIndex(row);
    }
    else if (row == 4) {
        ui->stackedWidget->setCurrentIndex(row);
    }
}


void MainWindow::logs_op(){  //Logs_operation
    ui->node_list->clear(); 
    QProcess process ;
    process.start("ros2",QStringList()<<"node"<<"list");
    process.waitForFinished();   //get the output of a command/program

    QString outputs = process.readAllStandardOutput();

    QStringList nodes = outputs.split("\n",Qt::KeepEmptyParts); //Qt::KeepEmptyParts -> [ "/talker", "/listener", "", "" ] skip empty part

    for (const QString &active_node : nodes){

        ui->node_list->addItem(active_node);
        node_list->addItem(checkbox);
        ui->
    }

    connect(ui->node_list,)
}

// void Mainwindow::Mapping(){

// }