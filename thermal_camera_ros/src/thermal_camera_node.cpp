#include "thermal_camera_ros/thermal_camera_node.hpp"

namespace thermal_camera_ros
{

ThermalCameraNode::ThermalCameraNode()
: Node("thermal_camera_node")
{
  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/thermal_camera/image_colored", 10);

  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(100),
    std::bind(&ThermalCameraNode::timer_callback, this));

  seek_cam_ = std::make_unique<LibSeek::SeekThermal>();
  if (!seek_cam_->open()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to open Seek Thermal camera");
    return;
  }
  RCLCPP_INFO(this->get_logger(), "Successfully opened Seek Thermal camera");
}

ThermalCameraNode::~ThermalCameraNode()
{
  if (seek_cam_) {
    seek_cam_->close();
  }
}

void ThermalCameraNode::timer_callback()
{
  cv::Mat thermal_frame;
  if (seek_cam_->read(thermal_frame)) {
    // Convert thermal data to colored image
    cv::Mat colored;
    cv::normalize(thermal_frame, thermal_frame, 0, 65535, cv::NORM_MINMAX);
    thermal_frame.convertTo(thermal_frame, CV_8UC1, 1.0/256.0);
    cv::applyColorMap(thermal_frame, colored, cv::COLORMAP_JET);

    // Convert to ROS message and publish
    sensor_msgs::msg::Image::SharedPtr msg = 
      cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", colored).toImageMsg();
    msg->header.stamp = this->now();
    msg->header.frame_id = "thermal_camera";
    publisher_->publish(*msg);
  } else {
    RCLCPP_WARN(this->get_logger(), "Failed to read frame from thermal camera");
  }
}

}  // namespace thermal_camera_ros

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<thermal_camera_ros::ThermalCameraNode>());
  rclcpp::shutdown();
  return 0;
}
