// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_HPP_
#define TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_HPP_

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
#include "test_tool/msg/detail/brush_status__struct.hpp"
// Member 'vacuum'
#include "test_tool/msg/detail/vacuum_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__test_tool__msg__A2FunctionalStatus __attribute__((deprecated))
#else
# define DEPRECATED__test_tool__msg__A2FunctionalStatus __declspec(deprecated)
#endif

namespace test_tool
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct A2FunctionalStatus_
{
  using Type = A2FunctionalStatus_<ContainerAllocator>;

  explicit A2FunctionalStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : brush(_init),
    vacuum(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->water_pump = 0;
      this->detergent_pump = 0;
    }
  }

  explicit A2FunctionalStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : brush(_alloc, _init),
    vacuum(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->water_pump = 0;
      this->detergent_pump = 0;
    }
  }

  // field types and members
  using _brush_type =
    test_tool::msg::BrushStatus_<ContainerAllocator>;
  _brush_type brush;
  using _vacuum_type =
    test_tool::msg::VacuumStatus_<ContainerAllocator>;
  _vacuum_type vacuum;
  using _water_pump_type =
    uint8_t;
  _water_pump_type water_pump;
  using _detergent_pump_type =
    uint8_t;
  _detergent_pump_type detergent_pump;

  // setters for named parameter idiom
  Type & set__brush(
    const test_tool::msg::BrushStatus_<ContainerAllocator> & _arg)
  {
    this->brush = _arg;
    return *this;
  }
  Type & set__vacuum(
    const test_tool::msg::VacuumStatus_<ContainerAllocator> & _arg)
  {
    this->vacuum = _arg;
    return *this;
  }
  Type & set__water_pump(
    const uint8_t & _arg)
  {
    this->water_pump = _arg;
    return *this;
  }
  Type & set__detergent_pump(
    const uint8_t & _arg)
  {
    this->detergent_pump = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    test_tool::msg::A2FunctionalStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const test_tool::msg::A2FunctionalStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      test_tool::msg::A2FunctionalStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      test_tool::msg::A2FunctionalStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__test_tool__msg__A2FunctionalStatus
    std::shared_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__test_tool__msg__A2FunctionalStatus
    std::shared_ptr<test_tool::msg::A2FunctionalStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const A2FunctionalStatus_ & other) const
  {
    if (this->brush != other.brush) {
      return false;
    }
    if (this->vacuum != other.vacuum) {
      return false;
    }
    if (this->water_pump != other.water_pump) {
      return false;
    }
    if (this->detergent_pump != other.detergent_pump) {
      return false;
    }
    return true;
  }
  bool operator!=(const A2FunctionalStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct A2FunctionalStatus_

// alias to use template instance with default allocator
using A2FunctionalStatus =
  test_tool::msg::A2FunctionalStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace test_tool

#endif  // TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_HPP_
