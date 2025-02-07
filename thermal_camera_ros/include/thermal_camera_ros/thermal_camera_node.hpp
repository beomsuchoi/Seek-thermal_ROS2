#ifndef THERMAL_CAMERA_NODE_HPP_
#define THERMAL_CAMERA_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <memory>
#include <seek/seek.h>
#include <seek/SeekThermal.h>
#include <opencv2/opencv.hpp>

namespace thermal_camera_ros
{

class ThermalCameraNode : public rclcpp::Node
{
public:
  ThermalCameraNode();
  virtual ~ThermalCameraNode();

private:
  void timer_callback();
  
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::unique_ptr<LibSeek::SeekThermal> seek_cam_;
};

}  // namespace thermal_camera_ros

#endif  // THERMAL_CAMERA_NODE_HPP_
