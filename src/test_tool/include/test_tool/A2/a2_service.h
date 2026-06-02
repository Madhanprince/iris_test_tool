#ifndef A2_SERVICE_H
#define A2_SERVICE_H

#include <rclcpp/rclcpp.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "qt_ros.h"
#include <memory>
#include "iris_interfaces/srv/a2_command.hpp"
#include "iris_interfaces/msg/a2_functional_status.hpp"
#include "iris_interfaces/msg/a2_fault_status.hpp"
#include "iris_interfaces/msg/a2_command.hpp"

class A2_service : public QWidget 
{
    Q_OBJECT

public:
    explicit A2_service(Ui::MainWindow *mainUi,
                        std::shared_ptr<Qtros> qtros_node,
                        QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    std::shared_ptr<Qtros> qtros;
    rclcpp::Client<iris_interfaces::srv::A2Command>::SharedPtr client_brush_;
    rclcpp::Client<iris_interfaces::srv::A2Command>::SharedPtr client_vaccum_;
    rclcpp::Publisher<iris_interfaces::msg::A2Command>::SharedPtr publisher_;
    rclcpp::Subscription<iris_interfaces::msg::A2FunctionalStatus>::SharedPtr brush_vaccum_status_subscriber;
    rclcpp::Subscription<iris_interfaces::msg::A2FaultStatus>::SharedPtr brush_vaccum_faults_subscriber;
    QHBoxLayout *rowLayout;
    QLabel *light_layout;
    QVector<QLabel*> lights;
    bool ui_created = false;
    QVBoxLayout *faults_mainLayout = nullptr;
    QVBoxLayout *faults_Group_Layout = nullptr;
    QHBoxLayout *brushMotorFaultsLayout = nullptr;
    QHBoxLayout *vaccumMotorFaultsLayout = nullptr;
    QLabel *faults_Label = nullptr;
    QGroupBox *faults_Group = nullptr;
    QGroupBox *BrushMotor_faults_Group = nullptr;
    QGroupBox *VaccumMotor_faults_Group = nullptr;

    void a2_status_display(const iris_interfaces::msg::A2FunctionalStatus::SharedPtr msg);
    void a2_faults_display(const iris_interfaces::msg::A2FaultStatus::SharedPtr msg);
    void a2_status_list();
    void create_faults_group_box();

    const QString ACTIVE_BUTTON_STYLE =
    "background-color:#22c55e;";

    const QString INACTIVE_BUTTON_STYLE =
    "background-color:#ef4444;";

    const QString LIGHT_GREEN_STYLE =
    "background-color:#86efac;";

    const QString LIGHT_RED_STYLE =
    "background-color:#fca5a5;";

private slots:
    void on_water_level_slider_valueChanged(int value);
    void brush_on_control();
    void brush_off_control();
    void vaccum_on_control();
    void vaccum_off_control();
};

#endif // A2_SERVICE_H