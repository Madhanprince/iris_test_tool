// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__TRAITS_HPP_
#define TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "test_tool/msg/detail/a2_functional_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'brush'
#include "test_tool/msg/detail/brush_status__traits.hpp"
// Member 'vacuum'
#include "test_tool/msg/detail/vacuum_status__traits.hpp"

namespace test_tool
{

namespace msg
{

inline void to_flow_style_yaml(
  const A2FunctionalStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: brush
  {
    out << "brush: ";
    to_flow_style_yaml(msg.brush, out);
    out << ", ";
  }

  // member: vacuum
  {
    out << "vacuum: ";
    to_flow_style_yaml(msg.vacuum, out);
    out << ", ";
  }

  // member: water_pump
  {
    out << "water_pump: ";
    rosidl_generator_traits::value_to_yaml(msg.water_pump, out);
    out << ", ";
  }

  // member: detergent_pump
  {
    out << "detergent_pump: ";
    rosidl_generator_traits::value_to_yaml(msg.detergent_pump, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const A2FunctionalStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: brush
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brush:\n";
    to_block_style_yaml(msg.brush, out, indentation + 2);
  }

  // member: vacuum
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vacuum:\n";
    to_block_style_yaml(msg.vacuum, out, indentation + 2);
  }

  // member: water_pump
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "water_pump: ";
    rosidl_generator_traits::value_to_yaml(msg.water_pump, out);
    out << "\n";
  }

  // member: detergent_pump
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detergent_pump: ";
    rosidl_generator_traits::value_to_yaml(msg.detergent_pump, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const A2FunctionalStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace test_tool

namespace rosidl_generator_traits
{

[[deprecated("use test_tool::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const test_tool::msg::A2FunctionalStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  test_tool::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use test_tool::msg::to_yaml() instead")]]
inline std::string to_yaml(const test_tool::msg::A2FunctionalStatus & msg)
{
  return test_tool::msg::to_yaml(msg);
}

template<>
inline const char * data_type<test_tool::msg::A2FunctionalStatus>()
{
  return "test_tool::msg::A2FunctionalStatus";
}

template<>
inline const char * name<test_tool::msg::A2FunctionalStatus>()
{
  return "test_tool/msg/A2FunctionalStatus";
}

template<>
struct has_fixed_size<test_tool::msg::A2FunctionalStatus>
  : std::integral_constant<bool, has_fixed_size<test_tool::msg::BrushStatus>::value && has_fixed_size<test_tool::msg::VacuumStatus>::value> {};

template<>
struct has_bounded_size<test_tool::msg::A2FunctionalStatus>
  : std::integral_constant<bool, has_bounded_size<test_tool::msg::BrushStatus>::value && has_bounded_size<test_tool::msg::VacuumStatus>::value> {};

template<>
struct is_message<test_tool::msg::A2FunctionalStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__TRAITS_HPP_
