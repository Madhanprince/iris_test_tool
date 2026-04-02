#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QListWidgetItem *item;
    QTimer *Timer;
    QStringList *nodes;
    QString *outputs ;

    void logs_op();
    void pages(int row);
    void onItemChanged();
    void listupdate();
};
#endif // MAINWINDOW_H
