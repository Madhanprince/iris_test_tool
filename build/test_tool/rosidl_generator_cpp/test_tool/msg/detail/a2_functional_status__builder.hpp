// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__BUILDER_HPP_
#define TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "test_tool/msg/detail/a2_functional_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace test_tool
{

namespace msg
{

namespace builder
{

class Init_A2FunctionalStatus_detergent_pump
{
public:
  explicit Init_A2FunctionalStatus_detergent_pump(::test_tool::msg::A2FunctionalStatus & msg)
  : msg_(msg)
  {}
  ::test_tool::msg::A2FunctionalStatus detergent_pump(::test_tool::msg::A2FunctionalStatus::_detergent_pump_type arg)
  {
    msg_.detergent_pump = std::move(arg);
    return std::move(msg_);
  }

private:
  ::test_tool::msg::A2FunctionalStatus msg_;
};

class Init_A2FunctionalStatus_water_pump
{
public:
  explicit Init_A2FunctionalStatus_water_pump(::test_tool::msg::A2FunctionalStatus & msg)
  : msg_(msg)
  {}
  Init_A2FunctionalStatus_detergent_pump water_pump(::test_tool::msg::A2FunctionalStatus::_water_pump_type arg)
  {
    msg_.water_pump = std::move(arg);
    return Init_A2FunctionalStatus_detergent_pump(msg_);
  }

private:
  ::test_tool::msg::A2FunctionalStatus msg_;
};

class Init_A2FunctionalStatus_vacuum
{
public:
  explicit Init_A2FunctionalStatus_vacuum(::test_tool::msg::A2FunctionalStatus & msg)
  : msg_(msg)
  {}
  Init_A2FunctionalStatus_water_pump vacuum(::test_tool::msg::A2FunctionalStatus::_vacuum_type arg)
  {
    msg_.vacuum = std::move(arg);
    return Init_A2FunctionalStatus_water_pump(msg_);
  }

private:
  ::test_tool::msg::A2FunctionalStatus msg_;
};

class Init_A2FunctionalStatus_brush
{
public:
  Init_A2FunctionalStatus_brush()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_A2FunctionalStatus_vacuum brush(::test_tool::msg::A2FunctionalStatus::_brush_type arg)
  {
    msg_.brush = std::move(arg);
    return Init_A2FunctionalStatus_vacuum(msg_);
  }

private:
  ::test_tool::msg::A2FunctionalStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::test_tool::msg::A2FunctionalStatus>()
{
  return test_tool::msg::builder::Init_A2FunctionalStatus_brush();
}

}  // namespace test_tool

#endif  // TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__BUILDER_HPP_
