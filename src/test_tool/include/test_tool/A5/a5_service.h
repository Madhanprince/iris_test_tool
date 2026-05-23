#ifndef A5_SERVICE_H
#define A5_SERVICE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QList>

class A5_service : public QWidget
{
    Q_OBJECT
public:
    explicit A5_service(QWidget *parent = nullptr);

public slots:
    void setUltrasonicActive(int idx, bool active);
    void setEncoderValues(int left, int right);
    void setFreshWaterLevel(int percent);

signals:
    void ledCommandRequested(const QString &cmd);

private:
    QList<QLabel*> ultrasonicLights;
    QLabel *encoderLeftLabel = nullptr;
    QLabel *encoderRightLabel = nullptr;
    QProgressBar *freshWaterBar = nullptr;
    QList<QPushButton*> ledButtons;
};

#endif // A5_SERVICE_H
