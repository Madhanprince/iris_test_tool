// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice
#include "test_tool/msg/detail/a2_functional_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `brush`
#include "test_tool/msg/detail/brush_status__functions.h"
// Member `vacuum`
#include "test_tool/msg/detail/vacuum_status__functions.h"

bool
test_tool__msg__A2FunctionalStatus__init(test_tool__msg__A2FunctionalStatus * msg)
{
  if (!msg) {
    return false;
  }
  // brush
  if (!test_tool__msg__BrushStatus__init(&msg->brush)) {
    test_tool__msg__A2FunctionalStatus__fini(msg);
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumStatus__init(&msg->vacuum)) {
    test_tool__msg__A2FunctionalStatus__fini(msg);
    return false;
  }
  // water_pump
  // detergent_pump
  return true;
}

void
test_tool__msg__A2FunctionalStatus__fini(test_tool__msg__A2FunctionalStatus * msg)
{
  if (!msg) {
    return;
  }
  // brush
  test_tool__msg__BrushStatus__fini(&msg->brush);
  // vacuum
  test_tool__msg__VacuumStatus__fini(&msg->vacuum);
  // water_pump
  // detergent_pump
}

bool
test_tool__msg__A2FunctionalStatus__are_equal(const test_tool__msg__A2FunctionalStatus * lhs, const test_tool__msg__A2FunctionalStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // brush
  if (!test_tool__msg__BrushStatus__are_equal(
      &(lhs->brush), &(rhs->brush)))
  {
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumStatus__are_equal(
      &(lhs->vacuum), &(rhs->vacuum)))
  {
    return false;
  }
  // water_pump
  if (lhs->water_pump != rhs->water_pump) {
    return false;
  }
  // detergent_pump
  if (lhs->detergent_pump != rhs->detergent_pump) {
    return false;
  }
  return true;
}

bool
test_tool__msg__A2FunctionalStatus__copy(
  const test_tool__msg__A2FunctionalStatus * input,
  test_tool__msg__A2FunctionalStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // brush
  if (!test_tool__msg__BrushStatus__copy(
      &(input->brush), &(output->brush)))
  {
    return false;
  }
  // vacuum
  if (!test_tool__msg__VacuumStatus__copy(
      &(input->vacuum), &(output->vacuum)))
  {
    return false;
  }
  // water_pump
  output->water_pump = input->water_pump;
  // detergent_pump
  output->detergent_pump = input->detergent_pump;
  return true;
}

test_tool__msg__A2FunctionalStatus *
test_tool__msg__A2FunctionalStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FunctionalStatus * msg = (test_tool__msg__A2FunctionalStatus *)allocator.allocate(sizeof(test_tool__msg__A2FunctionalStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(test_tool__msg__A2FunctionalStatus));
  bool success = test_tool__msg__A2FunctionalStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
test_tool__msg__A2FunctionalStatus__destroy(test_tool__msg__A2FunctionalStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    test_tool__msg__A2FunctionalStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
test_tool__msg__A2FunctionalStatus__Sequence__init(test_tool__msg__A2FunctionalStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FunctionalStatus * data = NULL;

  if (size) {
    data = (test_tool__msg__A2FunctionalStatus *)allocator.zero_allocate(size, sizeof(test_tool__msg__A2FunctionalStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = test_tool__msg__A2FunctionalStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        test_tool__msg__A2FunctionalStatus__fini(&data[i - 1]);
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
test_tool__msg__A2FunctionalStatus__Sequence__fini(test_tool__msg__A2FunctionalStatus__Sequence * array)
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
      test_tool__msg__A2FunctionalStatus__fini(&array->data[i]);
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

test_tool__msg__A2FunctionalStatus__Sequence *
test_tool__msg__A2FunctionalStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  test_tool__msg__A2FunctionalStatus__Sequence * array = (test_tool__msg__A2FunctionalStatus__Sequence *)allocator.allocate(sizeof(test_tool__msg__A2FunctionalStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = test_tool__msg__A2FunctionalStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
test_tool__msg__A2FunctionalStatus__Sequence__destroy(test_tool__msg__A2FunctionalStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    test_tool__msg__A2FunctionalStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
test_tool__msg__A2FunctionalStatus__Sequence__are_equal(const test_tool__msg__A2FunctionalStatus__Sequence * lhs, const test_tool__msg__A2FunctionalStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!test_tool__msg__A2FunctionalStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
test_tool__msg__A2FunctionalStatus__Sequence__copy(
  const test_tool__msg__A2FunctionalStatus__Sequence * input,
  test_tool__msg__A2FunctionalStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(test_tool__msg__A2FunctionalStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    test_tool__msg__A2FunctionalStatus * data =
      (test_tool__msg__A2FunctionalStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!test_tool__msg__A2FunctionalStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          test_tool__msg__A2FunctionalStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!test_tool__msg__A2FunctionalStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
