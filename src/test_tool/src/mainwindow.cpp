#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>


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

    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::logs_op);
    Timer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void refresh(){

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


void MainWindow::logs_op() {

    // ui->node_list->clear();
    QProcess process;
    process.start("ros2", QStringList() << "node" << "list");
    process.waitForFinished();

    QString outputs = process.readAllStandardOutput();
    QStringList nodes = outputs.split("\n", Qt::SkipEmptyParts); //this used to skip the empty string to the list one after the other 

    if (ui->node_list->count() <= 0){
        for (const QString &active_node : nodes) {

            item = new QListWidgetItem(active_node, ui->node_list);

            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);//These are options (features) you can enable/disable for an item.
            item->setCheckState(Qt::Unchecked);

            connect(ui->node_list, &QListWidget::itemChanged,
            this, [this](){
                 if (item->checkState() == Qt::Checked) {
                    qDebug() << "Checked:" << item->text();
                }
            });       
        }
    }
}

// void MainWindow::onItemChanged(){

//     if (item->checkState() == Qt::Checked) {
//         qDebug() << "Checked:" << item->text();
//     }
// }

// void Mainwindow::Mapping(){ 

// }