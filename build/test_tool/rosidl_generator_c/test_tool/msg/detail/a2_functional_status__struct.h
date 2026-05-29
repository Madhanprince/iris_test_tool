// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_H_
#define TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'brush'
#include "test_tool/msg/detail/brush_status__struct.h"
// Member 'vacuum'
#include "test_tool/msg/detail/vacuum_status__struct.h"

/// Struct defined in msg/A2FunctionalStatus in the package test_tool.
typedef struct test_tool__msg__A2FunctionalStatus
{
  test_tool__msg__BrushStatus brush;
  test_tool__msg__VacuumStatus vacuum;
  uint8_t water_pump;
  uint8_t detergent_pump;
} test_tool__msg__A2FunctionalStatus;

// Struct for a sequence of test_tool__msg__A2FunctionalStatus.
typedef struct test_tool__msg__A2FunctionalStatus__Sequence
{
  test_tool__msg__A2FunctionalStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} test_tool__msg__A2FunctionalStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__STRUCT_H_
