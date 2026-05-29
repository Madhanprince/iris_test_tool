// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from test_tool:msg/A2FaultStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_HPP_
#define TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'brush'
#include "test_tool/msg/detail/brush_faults__struct.hpp"
// Member 'vacuum'
#include "test_tool/msg/detail/vacuum_faults__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__test_tool__msg__A2FaultStatus __attribute__((deprecated))
#else
# define DEPRECATED__test_tool__msg__A2FaultStatus __declspec(deprecated)
#endif

namespace test_tool
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct A2FaultStatus_
{
  using Type = A2FaultStatus_<ContainerAllocator>;

  explicit A2FaultStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : brush(_init),
    vacuum(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a2_fault_status = 0;
      this->water_pump_digital_fault = 0;
      this->detergent_pump_digital_fault = 0;
      this->brush_vacuum_motor_driver_digital_fault = 0;
      this->water_and_detergent_pump_flow_fault = 0;
    }
  }

  explicit A2FaultStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : brush(_alloc, _init),
    vacuum(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a2_fault_status = 0;
      this->water_pump_digital_fault = 0;
      this->detergent_pump_digital_fault = 0;
      this->brush_vacuum_motor_driver_digital_fault = 0;
      this->water_and_detergent_pump_flow_fault = 0;
    }
  }

  // field types and members
  using _a2_fault_status_type =
    uint8_t;
  _a2_fault_status_type a2_fault_status;
  using _brush_type =
    test_tool::msg::BrushFaults_<ContainerAllocator>;
  _brush_type brush;
  using _vacuum_type =
    test_tool::msg::VacuumFaults_<ContainerAllocator>;
  _vacuum_type vacuum;
  using _water_pump_digital_fault_type =
    uint8_t;
  _water_pump_digital_fault_type water_pump_digital_fault;
  using _detergent_pump_digital_fault_type =
    uint8_t;
  _detergent_pump_digital_fault_type detergent_pump_digital_fault;
  using _brush_vacuum_motor_driver_digital_fault_type =
    uint8_t;
  _brush_vacuum_motor_driver_digital_fault_type brush_vacuum_motor_driver_digital_fault;
  using _water_and_detergent_pump_flow_fault_type =
    uint8_t;
  _water_and_detergent_pump_flow_fault_type water_and_detergent_pump_flow_fault;

  // setters for named parameter idiom
  Type & set__a2_fault_status(
    const uint8_t & _arg)
  {
    this->a2_fault_status = _arg;
    return *this;
  }
  Type & set__brush(
    const test_tool::msg::BrushFaults_<ContainerAllocator> & _arg)
  {
    this->brush = _arg;
    return *this;
  }
  Type & set__vacuum(
    const test_tool::msg::VacuumFaults_<ContainerAllocator> & _arg)
  {
    this->vacuum = _arg;
    return *this;
  }
  Type & set__water_pump_digital_fault(
    const uint8_t & _arg)
  {
    this->water_pump_digital_fault = _arg;
    return *this;
  }
  Type & set__detergent_pump_digital_fault(
    const uint8_t & _arg)
  {
    this->detergent_pump_digital_fault = _arg;
    return *this;
  }
  Type & set__brush_vacuum_motor_driver_digital_fault(
    const uint8_t & _arg)
  {
    this->brush_vacuum_motor_driver_digital_fault = _arg;
    return *this;
  }
  Type & set__water_and_detergent_pump_flow_fault(
    const uint8_t & _arg)
  {
    this->water_and_detergent_pump_flow_fault = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    test_tool::msg::A2FaultStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const test_tool::msg::A2FaultStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      test_tool::msg::A2FaultStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      test_tool::msg::A2FaultStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__test_tool__msg__A2FaultStatus
    std::shared_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__test_tool__msg__A2FaultStatus
    std::shared_ptr<test_tool::msg::A2FaultStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const A2FaultStatus_ & other) const
  {
    if (this->a2_fault_status != other.a2_fault_status) {
      return false;
    }
    if (this->brush != other.brush) {
      return false;
    }
    if (this->vacuum != other.vacuum) {
      return false;
    }
    if (this->water_pump_digital_fault != other.water_pump_digital_fault) {
      return false;
    }
    if (this->detergent_pump_digital_fault != other.detergent_pump_digital_fault) {
      return false;
    }
    if (this->brush_vacuum_motor_driver_digital_fault != other.brush_vacuum_motor_driver_digital_fault) {
      return false;
    }
    if (this->water_and_detergent_pump_flow_fault != other.water_and_detergent_pump_flow_fault) {
      return false;
    }
    return true;
  }
  bool operator!=(const A2FaultStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct A2FaultStatus_

// alias to use template instance with default allocator
using A2FaultStatus =
  test_tool::msg::A2FaultStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace test_tool

#endif  // TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_HPP_
