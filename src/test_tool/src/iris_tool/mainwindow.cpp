#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QProcess>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) ,Node("iris_tool")
{
    ui->setupUi(this);

    // 🔷 Sidebar → Page Switching
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            this, [=](int row){
                pages(row);
    });
    // 🔷 Default page
    ui->listWidget->setCurrentRow(0);

    connect(ui->node_list,QListWidget::itemChanged,this,onItemChanged);

    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::refreshNodeList);
    Timer->start(500ms);

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
        refreshNodeList();
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


void MainWindow::refreshNodeList()
{
    QProcess process;
    process.start("ros2", QStringList() << "node" << "list");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList nodes = output.split("\n", Qt::SkipEmptyParts);

    // 🔹 Add new nodes
    for (const QString &node : nodes) {

        bool exists = false;
        for (int i = 0; i < ui->node_list->count(); i++) { 
            //Qt the initial condition here are no items to check 
            // exists remains false then we add the new node 
            if (ui->node_list->item(i)->text() == node) {
                exists = true;
                // break;
            }
        }
        if (!exists) {
            QListWidgetItem *item = new QListWidgetItem(node, ui->node_list);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }

    // 🔹 Remove stopped nodes
    for (int i = ui->node_list->count() - 1; i >= 0; i--) { //checks from the revers index {node_list count()-1}

        QListWidgetItem *item = ui->node_list->item(i);

        if (!nodes.contains(item->text())) {
            delete ui->node_list->takeItem(i);
        }
    }
}


void MainWindow::onItemChanged(){

    if (item->checkState() == Qt::Checked) {
        
    }
}

// void Mainwindow::Mapping(){ 

// }