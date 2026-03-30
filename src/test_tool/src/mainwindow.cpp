#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 🔷 Sidebar → Page Switching
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            this, [=](int row){
        if(row >= 0)
            ui->stackedWidget->setCurrentIndex(row);
    });

    // 🔷 Default page
    ui->listWidget->setCurrentRow(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}
