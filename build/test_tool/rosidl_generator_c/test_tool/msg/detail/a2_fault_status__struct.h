// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from test_tool:msg/A2FaultStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_H_
#define TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_H_

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
#include "test_tool/msg/detail/brush_faults__struct.h"
// Member 'vacuum'
#include "test_tool/msg/detail/vacuum_faults__struct.h"

/// Struct defined in msg/A2FaultStatus in the package test_tool.
typedef struct test_tool__msg__A2FaultStatus
{
  uint8_t a2_fault_status;
  test_tool__msg__BrushFaults brush;
  test_tool__msg__VacuumFaults vacuum;
  uint8_t water_pump_digital_fault;
  uint8_t detergent_pump_digital_fault;
  uint8_t brush_vacuum_motor_driver_digital_fault;
  uint8_t water_and_detergent_pump_flow_fault;
} test_tool__msg__A2FaultStatus;

// Struct for a sequence of test_tool__msg__A2FaultStatus.
typedef struct test_tool__msg__A2FaultStatus__Sequence
{
  test_tool__msg__A2FaultStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} test_tool__msg__A2FaultStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TEST_TOOL__MSG__DETAIL__A2_FAULT_STATUS__STRUCT_H_
