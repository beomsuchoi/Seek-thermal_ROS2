cmake_minimum_required(VERSION 3.8)
project(thermal_camera_ros)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(thermal_camera_node
  src/thermal_camera_node.cpp
)

ament_target_dependencies(thermal_camera_node
  rclcpp
  sensor_msgs
  cv_bridge
  OpenCV
)

target_link_libraries(thermal_camera_node
  seek
)

install(TARGETS
  thermal_camera_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include/
)

ament_package()