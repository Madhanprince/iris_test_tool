#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QProcess>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QString>

using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) ,Node("iris_tool")
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::currentRowChanged, // Sidebar → Page Switching
            this, [=](int row){
                pages(row);
    });
    ui->listWidget->setCurrentRow(0); //Default page

    qtros = new Qtros();
    connect(qtros,&Qtros::logReceived,this,&MainWindow::onLogReceived);// once the message is received from the subscription in qtros, 
    //it will emit a signal logReceived which is connected to the onLogReceived slot in MainWindow.

    connect(ui->node_list,QListWidget::itemChanged,this,&MainWindow::onItemChanged);

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

void MainWindow::onItemChanged(QListWidgetItem *item, const rcl_interfaces::msg::Log::SharedPtr msg)
{
    int index 
    if (item->checkState() == Qt::Checked) {
        for (const QString &selected_node : nodes){
            index = ui->node_list->row(selected_node);
            if (msg->name.c_str() == item->text(index)){
               onLogReceived(msg);
            }
        }       
    }else {
        if(item->checkState() == Qt::Unchecked){
            index = ui->node_list->row(item);
            QString unselected_node=item->text(index);
            return; // Skip processing logs for this node
        }
    }
}


void MainWindow::onLogReceived(const rcl_interfaces::msg::Log::SharedPtr msg)
{
    QString logMessage = QString("[%1] %2: %3").arg(QString::fromStdString(msg->name))
                                        .arg(QString::fromStdString(msg->msg))
                                        .arg(QString::fromStdString(msg->file));
    if (msg->level >= 40) {
        ui->plainTextEdit_3->appendPlainText(logMessage); // ERROR
    }
    else if (msg->level >= 30) {
        ui->plainTextEdit_2->appendPlainText(logMessage); // WARN
    }
    else {
        ui->plainTextEdit->appendPlainText(logMessage);   // INFO
    }
}