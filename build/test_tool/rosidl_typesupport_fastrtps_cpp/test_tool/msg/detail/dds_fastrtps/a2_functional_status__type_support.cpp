// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice
#include "test_tool/msg/detail/a2_functional_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "test_tool/msg/detail/a2_functional_status__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace test_tool
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const test_tool::msg::BrushStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  test_tool::msg::BrushStatus &);
size_t get_serialized_size(
  const test_tool::msg::BrushStatus &,
  size_t current_alignment);
size_t
max_serialized_size_BrushStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace test_tool

namespace test_tool
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const test_tool::msg::VacuumStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  test_tool::msg::VacuumStatus &);
size_t get_serialized_size(
  const test_tool::msg::VacuumStatus &,
  size_t current_alignment);
size_t
max_serialized_size_VacuumStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace test_tool


namespace test_tool
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_test_tool
cdr_serialize(
  const test_tool::msg::A2FunctionalStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: brush
  test_tool::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.brush,
    cdr);
  // Member: vacuum
  test_tool::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.vacuum,
    cdr);
  // Member: water_pump
  cdr << ros_message.water_pump;
  // Member: detergent_pump
  cdr << ros_message.detergent_pump;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_test_tool
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  test_tool::msg::A2FunctionalStatus & ros_message)
{
  // Member: brush
  test_tool::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.brush);

  // Member: vacuum
  test_tool::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.vacuum);

  // Member: water_pump
  cdr >> ros_message.water_pump;

  // Member: detergent_pump
  cdr >> ros_message.detergent_pump;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_test_tool
get_serialized_size(
  const test_tool::msg::A2FunctionalStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: brush

  current_alignment +=
    test_tool::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.brush, current_alignment);
  // Member: vacuum

  current_alignment +=
    test_tool::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.vacuum, current_alignment);
  // Member: water_pump
  {
    size_t item_size = sizeof(ros_message.water_pump);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: detergent_pump
  {
    size_t item_size = sizeof(ros_message.detergent_pump);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_test_tool
max_serialized_size_A2FunctionalStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: brush
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        test_tool::msg::typesupport_fastrtps_cpp::max_serialized_size_BrushStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: vacuum
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        test_tool::msg::typesupport_fastrtps_cpp::max_serialized_size_VacuumStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: water_pump
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: detergent_pump
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = test_tool::msg::A2FunctionalStatus;
    is_plain =
      (
      offsetof(DataType, detergent_pump) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _A2FunctionalStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const test_tool::msg::A2FunctionalStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _A2FunctionalStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<test_tool::msg::A2FunctionalStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _A2FunctionalStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const test_tool::msg::A2FunctionalStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _A2FunctionalStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_A2FunctionalStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _A2FunctionalStatus__callbacks = {
  "test_tool::msg",
  "A2FunctionalStatus",
  _A2FunctionalStatus__cdr_serialize,
  _A2FunctionalStatus__cdr_deserialize,
  _A2FunctionalStatus__get_serialized_size,
  _A2FunctionalStatus__max_serialized_size
};

static rosidl_message_type_support_t _A2FunctionalStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_A2FunctionalStatus__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace test_tool

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_test_tool
const rosidl_message_type_support_t *
get_message_type_support_handle<test_tool::msg::A2FunctionalStatus>()
{
  return &test_tool::msg::typesupport_fastrtps_cpp::_A2FunctionalStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, test_tool, msg, A2FunctionalStatus)() {
  return &test_tool::msg::typesupport_fastrtps_cpp::_A2FunctionalStatus__handle;
}

#ifdef __cplusplus
}
#endif
