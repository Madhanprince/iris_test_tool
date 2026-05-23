#ifndef A2_SERVICE_H
#define A2_SERVICE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class A2_service : public QWidget
{
    Q_OBJECT
public:
    explicit A2_service(QWidget *parent = nullptr);
    Ui::MainWindow *ui;

};

#endif // A2_SERVICE_H