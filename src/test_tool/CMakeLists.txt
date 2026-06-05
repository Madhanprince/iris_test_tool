cmake_minimum_required(VERSION 3.8)


project(test_tool VERSION 0.1 LANGUAGES CXX)

# Enable compiler warnings for GCC / Clang


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Prevent the "already defined" error
set(QT_NO_CREATE_VERSIONLESS_TARGETS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(iris_interfaces REQUIRED)
find_package(builtin_interfaces REQUIRED)

# Force Qt5 to match ROS Humble / RViz
find_package(Qt5 REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
    src/iris_tool/main.cpp
    src/iris_tool/mainwindow.cpp
    src/iris_tool/mainwindow.ui
    src/iris_tool/qt_ros.cpp
    src/iris_tool/A2/a2_service.cpp
    src/iris_tool/A5/a5_service.cpp

    include/test_tool/mainwindow.h
    include/test_tool/qt_ros.h
    include/test_tool/A2/a2_service.h
    include/test_tool/A5/a5_service.h
)

add_executable(test_tool_node  ${PROJECT_SOURCES})

# ✅ FIXED: Pointed directly to the UI folder so ui_mainwindow.h generates and links successfully
set_target_properties(test_tool_node PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/src/iris_tool"
)

# ✅ FIXED: Standardized target directory to allow #include "test_tool/mainwindow.h"
target_include_directories(test_tool_node PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/include/test_tool"
) 

target_link_libraries(test_tool_node 
  Qt5::Widgets 
  rviz_common::rviz_common 
)

ament_target_dependencies(test_tool_node 
  rclcpp 
  std_msgs 
  iris_interfaces
  sensor_msgs
  rviz_common
 
)
ament_export_dependencies(rosidl_default_runtime)             
# Dummy test binaries
add_executable(dummy_test src/test_node/dummy_test.cpp)
ament_target_dependencies(dummy_test rclcpp std_msgs rcl_interfaces sensor_msgs)

add_executable(dummy_test_1 src/test_node/dummy_test_1.cpp)
ament_target_dependencies(dummy_test_1 rclcpp std_msgs rcl_interfaces sensor_msgs)

ament_export_dependencies(rosidl_default_runtime)

# Installation
install(TARGETS test_tool_node dummy_test dummy_test_1 
  DESTINATION lib/${PROJECT_NAME})
  
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

# Testing configuration
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()