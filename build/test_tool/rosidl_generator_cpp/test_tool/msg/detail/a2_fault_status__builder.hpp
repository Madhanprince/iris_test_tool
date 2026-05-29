// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from test_tool:msg/A2FaultStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__BUILDER_HPP_
#define TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "test_tool/msg/detail/a2_fault_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace test_tool
{

namespace msg
{

namespace builder
{

class Init_A2FaultStatus_water_and_detergent_pump_flow_fault
{
public:
  explicit Init_A2FaultStatus_water_and_detergent_pump_flow_fault(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  ::test_tool::msg::A2FaultStatus water_and_detergent_pump_flow_fault(::test_tool::msg::A2FaultStatus::_water_and_detergent_pump_flow_fault_type arg)
  {
    msg_.water_and_detergent_pump_flow_fault = std::move(arg);
    return std::move(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_brush_vacuum_motor_driver_digital_fault
{
public:
  explicit Init_A2FaultStatus_brush_vacuum_motor_driver_digital_fault(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  Init_A2FaultStatus_water_and_detergent_pump_flow_fault brush_vacuum_motor_driver_digital_fault(::test_tool::msg::A2FaultStatus::_brush_vacuum_motor_driver_digital_fault_type arg)
  {
    msg_.brush_vacuum_motor_driver_digital_fault = std::move(arg);
    return Init_A2FaultStatus_water_and_detergent_pump_flow_fault(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_detergent_pump_digital_fault
{
public:
  explicit Init_A2FaultStatus_detergent_pump_digital_fault(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  Init_A2FaultStatus_brush_vacuum_motor_driver_digital_fault detergent_pump_digital_fault(::test_tool::msg::A2FaultStatus::_detergent_pump_digital_fault_type arg)
  {
    msg_.detergent_pump_digital_fault = std::move(arg);
    return Init_A2FaultStatus_brush_vacuum_motor_driver_digital_fault(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_water_pump_digital_fault
{
public:
  explicit Init_A2FaultStatus_water_pump_digital_fault(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  Init_A2FaultStatus_detergent_pump_digital_fault water_pump_digital_fault(::test_tool::msg::A2FaultStatus::_water_pump_digital_fault_type arg)
  {
    msg_.water_pump_digital_fault = std::move(arg);
    return Init_A2FaultStatus_detergent_pump_digital_fault(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_vacuum
{
public:
  explicit Init_A2FaultStatus_vacuum(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  Init_A2FaultStatus_water_pump_digital_fault vacuum(::test_tool::msg::A2FaultStatus::_vacuum_type arg)
  {
    msg_.vacuum = std::move(arg);
    return Init_A2FaultStatus_water_pump_digital_fault(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_brush
{
public:
  explicit Init_A2FaultStatus_brush(::test_tool::msg::A2FaultStatus & msg)
  : msg_(msg)
  {}
  Init_A2FaultStatus_vacuum brush(::test_tool::msg::A2FaultStatus::_brush_type arg)
  {
    msg_.brush = std::move(arg);
    return Init_A2FaultStatus_vacuum(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

class Init_A2FaultStatus_a2_fault_status
{
public:
  Init_A2FaultStatus_a2_fault_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_A2FaultStatus_brush a2_fault_status(::test_tool::msg::A2FaultStatus::_a2_fault_status_type arg)
  {
    msg_.a2_fault_status = std::move(arg);
    return Init_A2FaultStatus_brush(msg_);
  }

private:
  ::test_tool::msg::A2FaultStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::test_tool::msg::A2FaultStatus>()
{
  return test_tool::msg::builder::Init_A2FaultStatus_a2_fault_status();
}

}  // namespace test_tool

#endif  // TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__BUILDER_HPP_
