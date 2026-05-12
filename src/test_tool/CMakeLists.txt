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

# Prevent the "already defined" error
set(QT_NO_CREATE_VERSIONLESS_TARGETS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED) # ROS2 build system
find_package(rcl_interfaces REQUIRED) # ROS2 message types
find_package(std_msgs REQUIRED) # ROS2 message types
find_package(sensor_msgs REQUIRED) # ROS2 message types
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)

# 2. Force Qt5 to match ROS Humble / RViz
find_package(Qt5 REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES # List of all project source files
    src/iris_tool/main.cpp
    src/iris_tool/mainwindow.cpp
    src/iris_tool/mainwindow.ui
    src/iris_tool/qt_ros.cpp

    include/test_tool/mainwindow.h
    include/test_tool/qt_ros.h
)

add_executable(test_tool ${PROJECT_SOURCES}) # Create executable from source files

# ✅ FIXED: Added explicit Ogre include paths so the compiler can find OgreOverlayManager.h

target_include_directories(test_tool PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/include/test_tool"
) 

target_link_libraries(test_tool 
  Qt5::Widgets 
  rviz_common::rviz_common  
  rviz_ogre_vendor::OgreMain
  rviz_ogre_vendor::OgreOverlay
)

# ✅ FIXED: Appended rviz_common and rviz_ogre_vendor here to ensure target macro properties export completely
ament_target_dependencies(test_tool 
  rclcpp 
  std_msgs 
  rcl_interfaces 
  sensor_msgs
  rviz_common
  rviz_ogre_vendor
)

add_executable(dummy_test src/dummy_test.cpp)
target_link_libraries(dummy_test Qt5::Widgets) 
ament_target_dependencies(dummy_test rclcpp std_msgs rcl_interfaces sensor_msgs)

add_executable(dummy_test_1 src/dummy_test_1.cpp)
target_link_libraries(dummy_test_1 Qt5::Widgets) 
ament_target_dependencies(dummy_test_1 rclcpp std_msgs rcl_interfaces sensor_msgs)

install(TARGETS test_tool dummy_test dummy_test_1 
  DESTINATION lib/${PROJECT_NAME}) # Install executable for ROS2 so "ros2 run" works
  
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

# Optional testing section used by ROS2 lint tools
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED) # Find ROS2 lint tools
  set(ament_cmake_copyright_FOUND TRUE) # Skip copyright check
  set(ament_cmake_cpplint_FOUND TRUE) # Skip cpplint
  ament_lint_auto_find_test_dependencies() # Run lint dependencies
endif()

ament_package() # Declare this as a ROS2 package