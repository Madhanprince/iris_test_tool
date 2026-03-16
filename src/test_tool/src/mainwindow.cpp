#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),logFile("touch.txt"),
      logStream(&logFile)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    
}

void function(){

}






