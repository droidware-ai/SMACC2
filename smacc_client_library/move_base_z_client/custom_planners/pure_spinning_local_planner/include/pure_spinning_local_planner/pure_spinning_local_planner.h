/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#pragma once
//#include <dynamic_reconfigure/server.h>
//#include <pure_spinning_local_planner/PureSpinningLocalPlannerConfig.h>
#include <tf2/transform_datatypes.h>
#include <tf2/utils.h>
#include <tf2_ros/buffer.h>

#include <Eigen/Eigen>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav2_core/controller.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

typedef double meter;
typedef double rad;
typedef double rad_s;

namespace cl_move_base_z
{
namespace pure_spinning_local_planner
{
class PureSpinningLocalPlanner : public nav2_core::Controller
{
public:
  PureSpinningLocalPlanner();

  virtual ~PureSpinningLocalPlanner();

  void configure(const rclcpp_lifecycle::LifecycleNode::WeakPtr &parent, std::string name,
                 const std::shared_ptr<tf2_ros::Buffer> &tf,
                 const std::shared_ptr<nav2_costmap_2d::Costmap2DROS> &costmap_ros) override;

  void activate() override;
  void deactivate() override;
  void cleanup() override;

  /**
   * @brief nav2_core setPlan - Sets the global plan
   * @param path The global plan
   */
  void setPlan(const nav_msgs::msg::Path &path) override;

  /**
   * @brief nav2_core computeVelocityCommands - calculates the best command given the current pose and velocity
   *
   * It is presumed that the global plan is already set.
   *
   * This is mostly a wrapper for the protected computeVelocityCommands
   * function which has additional debugging info.
   *
   * @param pose Current robot pose
   * @param velocity Current robot velocity
   * @return The best command for the robot to drive
   */
  virtual geometry_msgs::msg::TwistStamped computeVelocityCommands(const geometry_msgs::msg::PoseStamped &pose,
                                                                   const geometry_msgs::msg::Twist &velocity,
                                                                   nav2_core::GoalChecker *goal_checker) override;

  /*deprecated in navigation2*/
  bool isGoalReached();

  virtual void setSpeedLimit(const double &speed_limit, const bool &percentage) override;

private:
  void updateParameters();
  nav2_util::LifecycleNode::SharedPtr nh_;
  std::string name_;
  void publishGoalMarker(double x, double y, double phi);

  std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmapRos_;

  std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<visualization_msgs::msg::MarkerArray>> goalMarkerPublisher_;

  std::vector<geometry_msgs::msg::PoseStamped> plan_;

  std::shared_ptr<tf2_ros::Buffer> tf_;

  // void reconfigCB(::pure_spinning_local_planner::PureSpinningLocalPlannerConfig &config, uint32_t level);

  // dynamic_reconfigure::Server<::pure_spinning_local_planner::PureSpinningLocalPlannerConfig> paramServer_;

  double k_betta_;
  bool goalReached_;
  int currentPoseIndex_;
  rad yaw_goal_tolerance_;
  rad intermediate_goal_yaw_tolerance_;
  rad_s max_angular_z_speed_;
  double transform_tolerance_;
};
}  // namespace pure_spinning_local_planner
}  // namespace cl_move_base_z