// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from test_tool:msg/A2FaultStatus.idl
// generated code does not contain a copyright notice
#include "test_tool/msg/detail/a2_fault_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `brush`
#include "test_tool/msg/detail/brush_faults__functions.h"
// Member `vacuum`
#include "test_tool/msg/detail/vacuum_faults__functions.h"

bool
test_tool__msg__A2FaultStatus__init(test_tool__msg__A2FaultStatus * msg)
{
  if (!msg) {
    return false;
  }
  // a2_fault_status
  // brush
  if (!test_tool__msg__BrushFaults__init(&msg->brush)) {
    test_tool__msg__A2FaultStatus__fini(msg);
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumFaults__init(&msg->vacuum)) {
    test_tool__msg__A2FaultStatus__fini(msg);
    return false;
  }
  // water_pump_digital_fault
  // detergent_pump_digital_fault
  // brush_vacuum_motor_driver_digital_fault
  // water_and_detergent_pump_flow_fault
  return true;
}

void
test_tool__msg__A2FaultStatus__fini(test_tool__msg__A2FaultStatus * msg)
{
  if (!msg) {
    return;
  }
  // a2_fault_status
  // brush
  test_tool__msg__BrushFaults__fini(&msg->brush);
  // vacuum
  test_tool__msg__VacuumFaults__fini(&msg->vacuum);
  // water_pump_digital_fault
  // detergent_pump_digital_fault
  // brush_vacuum_motor_driver_digital_fault
  // water_and_detergent_pump_flow_fault
}

bool
test_tool__msg__A2FaultStatus__are_equal(const test_tool__msg__A2FaultStatus * lhs, const test_tool__msg__A2FaultStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // a2_fault_status
  if (lhs->a2_fault_status != rhs->a2_fault_status) {
    return false;
  }
  // brush
  if (!test_tool__msg__BrushFaults__are_equal(
      &(lhs->brush), &(rhs->brush)))
  {
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumFaults__are_equal(
      &(lhs->vacuum), &(rhs->vacuum)))
  {
    return false;
  }
  // water_pump_digital_fault
  if (lhs->water_pump_digital_fault != rhs->water_pump_digital_fault) {
    return false;
  }
  // detergent_pump_digital_fault
  if (lhs->detergent_pump_digital_fault != rhs->detergent_pump_digital_fault) {
    return false;
  }
  // brush_vacuum_motor_driver_digital_fault
  if (lhs->brush_vacuum_motor_driver_digital_fault != rhs->brush_vacuum_motor_driver_digital_fault) {
    return false;
  }
  // water_and_detergent_pump_flow_fault
  if (lhs->water_and_detergent_pump_flow_fault != rhs->water_and_detergent_pump_flow_fault) {
    return false;
  }
  return true;
}

bool
test_tool__msg__A2FaultStatus__copy(
  const test_tool__msg__A2FaultStatus * input,
  test_tool__msg__A2FaultStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // a2_fault_status
  output->a2_fault_status = input->a2_fault_status;
  // brush
  if (!test_tool__msg__BrushFaults__copy(
      &(input->brush), &(output->brush)))
  {
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumFaults__copy(
      &(input->vacuum), &(output->vacuum)))
  {
    return false;
  }
  // water_pump_digital_fault
  output->water_pump_digital_fault = input->water_pump_digital_fault;
  // detergent_pump_digital_fault
  output->detergent_pump_digital_fault = input->detergent_pump_digital_fault;
  // brush_vacuum_motor_driver_digital_fault
  output->brush_vacuum_motor_driver_digital_fault = input->brush_vacuum_motor_driver_digital_fault;
  // water_and_detergent_pump_flow_fault
  output->water_and_detergent_pump_flow_fault = input->water_and_detergent_pump_flow_fault;
  return true;
}

test_tool__msg__A2FaultStatus *
test_tool__msg__A2FaultStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FaultStatus * msg = (test_tool__msg__A2FaultStatus *)allocator.allocate(sizeof(test_tool__msg__A2FaultStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(test_tool__msg__A2FaultStatus));
  bool success = test_tool__msg__A2FaultStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
test_tool__msg__A2FaultStatus__destroy(test_tool__msg__A2FaultStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    test_tool__msg__A2FaultStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
test_tool__msg__A2FaultStatus__Sequence__init(test_tool__msg__A2FaultStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FaultStatus * data = NULL;

  if (size) {
    data = (test_tool__msg__A2FaultStatus *)allocator.zero_allocate(size, sizeof(test_tool__msg__A2FaultStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = test_tool__msg__A2FaultStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        test_tool__msg__A2FaultStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
test_tool__msg__A2FaultStatus__Sequence__fini(test_tool__msg__A2FaultStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      test_tool__msg__A2FaultStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

test_tool__msg__A2FaultStatus__Sequence *
test_tool__msg__A2FaultStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FaultStatus__Sequence * array = (test_tool__msg__A2FaultStatus__Sequence *)allocator.allocate(sizeof(test_tool__msg__A2FaultStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = test_tool__msg__A2FaultStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
test_tool__msg__A2FaultStatus__Sequence__destroy(test_tool__msg__A2FaultStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    test_tool__msg__A2FaultStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
test_tool__msg__A2FaultStatus__Sequence__are_equal(const test_tool__msg__A2FaultStatus__Sequence * lhs, const test_tool__msg__A2FaultStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!test_tool__msg__A2FaultStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
test_tool__msg__A2FaultStatus__Sequence__copy(
  const test_tool__msg__A2FaultStatus__Sequence * input,
  test_tool__msg__A2FaultStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(test_tool__msg__A2FaultStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    test_tool__msg__A2FaultStatus * data =
      (test_tool__msg__A2FaultStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!test_tool__msg__A2FaultStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          test_tool__msg__A2FaultStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!test_tool__msg__A2FaultStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
