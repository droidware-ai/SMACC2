#pragma once

#include <multirole_sensor_client/client_behaviors/cb_default_multirole_sensor_behavior.h>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sm_dance_bot/clients/cl_lidar/cl_lidar.h>

namespace sm_dance_bot
{
namespace cl_lidar
{
struct CbLidarSensor : cl_multirole_sensor::CbDefaultMultiRoleSensorBehavior<ClLidarSensor>
{
public:
  CbLidarSensor()
  {
    
  }

  virtual void onEntry() override
  {
    RCLCPP_INFO(getNode()->get_logger(),"[CbLidarSensor] onEntry");
    cl_multirole_sensor::CbDefaultMultiRoleSensorBehavior<ClLidarSensor>::onEntry();
  }

  virtual void onMessageCallback(const sensor_msgs::msg::LaserScan &/*msg*/) override
  {
  }
};
} // namespace cl_lidar
} // namespace sm_dance_bot
