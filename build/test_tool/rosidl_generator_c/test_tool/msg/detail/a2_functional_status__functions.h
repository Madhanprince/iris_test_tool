// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from test_tool:msg/A2FunctionalStatus.idl
// generated code does not contain a copyright notice

#ifndef TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__FUNCTIONS_H_
#define TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "test_tool/msg/rosidl_generator_c__visibility_control.h"

#include "test_tool/msg/detail/a2_functional_status__struct.h"

/// Initialize msg/A2FunctionalStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * test_tool__msg__A2FunctionalStatus
 * )) before or use
 * test_tool__msg__A2FunctionalStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__init(test_tool__msg__A2FunctionalStatus * msg);

/// Finalize msg/A2FunctionalStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
void
test_tool__msg__A2FunctionalStatus__fini(test_tool__msg__A2FunctionalStatus * msg);

/// Create msg/A2FunctionalStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * test_tool__msg__A2FunctionalStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
test_tool__msg__A2FunctionalStatus *
test_tool__msg__A2FunctionalStatus__create();

/// Destroy msg/A2FunctionalStatus message.
/**
 * It calls
 * test_tool__msg__A2FunctionalStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
void
test_tool__msg__A2FunctionalStatus__destroy(test_tool__msg__A2FunctionalStatus * msg);

/// Check for msg/A2FunctionalStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__are_equal(const test_tool__msg__A2FunctionalStatus * lhs, const test_tool__msg__A2FunctionalStatus * rhs);

/// Copy a msg/A2FunctionalStatus message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__copy(
  const test_tool__msg__A2FunctionalStatus * input,
  test_tool__msg__A2FunctionalStatus * output);

/// Initialize array of msg/A2FunctionalStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * test_tool__msg__A2FunctionalStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__Sequence__init(test_tool__msg__A2FunctionalStatus__Sequence * array, size_t size);

/// Finalize array of msg/A2FunctionalStatus messages.
/**
 * It calls
 * test_tool__msg__A2FunctionalStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
void
test_tool__msg__A2FunctionalStatus__Sequence__fini(test_tool__msg__A2FunctionalStatus__Sequence * array);

/// Create array of msg/A2FunctionalStatus messages.
/**
 * It allocates the memory for the array and calls
 * test_tool__msg__A2FunctionalStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
test_tool__msg__A2FunctionalStatus__Sequence *
test_tool__msg__A2FunctionalStatus__Sequence__create(size_t size);

/// Destroy array of msg/A2FunctionalStatus messages.
/**
 * It calls
 * test_tool__msg__A2FunctionalStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
void
test_tool__msg__A2FunctionalStatus__Sequence__destroy(test_tool__msg__A2FunctionalStatus__Sequence * array);

/// Check for msg/A2FunctionalStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__Sequence__are_equal(const test_tool__msg__A2FunctionalStatus__Sequence * lhs, const test_tool__msg__A2FunctionalStatus__Sequence * rhs);

/// Copy an array of msg/A2FunctionalStatus messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_test_tool
bool
test_tool__msg__A2FunctionalStatus__Sequence__copy(
  const test_tool__msg__A2FunctionalStatus__Sequence * input,
  test_tool__msg__A2FunctionalStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TEST_TOOL__MSG__DETAIL__A2_FUNCTIONAL_STATUS__FUNCTIONS_H_
