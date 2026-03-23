cmake_minimum_required(VERSION 3.8) # Minimum CMake version required

project(test_tool VERSION 0.1 LANGUAGES CXX) # Project name and language

# Enable compiler warnings for GCC / Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic) # Recommended compile warnings
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Include current directory automatically

set(CMAKE_AUTOUIC ON) # Automatically process Qt UI files (.ui)
set(CMAKE_AUTOMOC ON) # Automatically process Qt signals/slots (Q_OBJECT)
set(CMAKE_AUTORCC ON) # Automatically process Qt resource files (.qrc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Enforce C++17

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) # ROS2 build system
find_package(rcl_interfaces REQUIRED) # ROS2 message types
find_package(std_msgs REQUIRED) # ROS2 message types
find_package(sensor_msgs REQUIRED) # ROS2 message types

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets) # Find Qt version
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets) # Load correct Qt Widgets module

set(PROJECT_SOURCES # List of all project source files
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    include/test_tool/mainwindow.h
)

add_executable(test_tool ${PROJECT_SOURCES}) # Create executable from source files

ament_target_dependencies(test_tool
  rclcpp
  rcl_interfaces   # ✅ ADD THIS
  std_msgs          # ✅ ADD THIS
)

target_include_directories(test_tool PUBLIC include/test_tool) # Include header directory
target_link_libraries(test_tool Qt${QT_VERSION_MAJOR}::Widgets) # Link Qt Widgets library

add_executable(dummy_test src/dummy_test.cpp) # Create dummy test executable 
ament_target_dependencies(dummy_test
  rclcpp
  rcl_interfaces   # ✅ ADD THIS
  std_msgs          # ✅ ADD THIS
)

add_executable(lidar_node src/lidar_node.cpp) # Create lidar_node executable
ament_target_dependencies(lidar_node
  rclcpp
  rcl_interfaces
  std_msgs
  sensor_msgs
)

install(TARGETS test_tool dummy_test lidar_node DESTINATION lib/${PROJECT_NAME}) # Install executable for ROS2 so "ros2 run" works

# Optional testing section used by ROS2 lint tools
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED) # Find ROS2 lint tools
  set(ament_cmake_copyright_FOUND TRUE) # Skip copyright check
  set(ament_cmake_cpplint_FOUND TRUE) # Skip cpplint
  ament_lint_auto_find_test_dependencies() # Run lint dependencies
endif()

ament_package() # Declare this as a ROS2 package
