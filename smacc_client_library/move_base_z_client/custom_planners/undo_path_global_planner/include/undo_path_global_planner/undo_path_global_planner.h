/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <nav2_core/global_planner.hpp>
#include <nav_msgs/msg/path.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

namespace cl_move_base_z
{
namespace undo_path_global_planner
{
class UndoPathGlobalPlanner : public nav2_core::GlobalPlanner
{
public:

  UndoPathGlobalPlanner();

  /**
   * @brief Virtual destructor
   */
  virtual ~UndoPathGlobalPlanner();

  /**
   * @param  parent pointer to user's node
   * @param  name The name of this planner
   * @param  tf A pointer to a TF buffer
   * @param  costmap_ros A pointer to the costmap
   */
  virtual void configure(
    const rclcpp_lifecycle::LifecycleNode::WeakPtr& parent,
    std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
    std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros);

    /**
     * @brief Method to cleanup resources used on shutdown.
     */
    virtual void cleanup();

    /**
     * @brief Method to active planner and any threads involved in execution.
     */
    virtual void activate() ;

    /**
     * @brief Method to deactive planner and any threads involved in execution.
     */
    virtual void deactivate() ;

    /**
     * @brief Method create the plan from a starting and ending goal.
     * @param start The starting pose of the robot
     * @param goal  The goal pose of the robot
     * @return      The sequence of poses to get from start to goal, if any
     */
    virtual nav_msgs::msg::Path createPlan(
        const geometry_msgs::msg::PoseStamped & start,
        const geometry_msgs::msg::PoseStamped & goal);


private:
    // ros::NodeHandle nh_;
    rclcpp_lifecycle::LifecycleNode::SharedPtr nh_;
    rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr forwardPathSub_;

    rclcpp_lifecycle::LifecyclePublisher<nav_msgs::msg::Path>::SharedPtr planPub_;

    rclcpp_lifecycle::LifecyclePublisher<visualization_msgs::msg::MarkerArray>::SharedPtr markersPub_;

    nav_msgs::msg::Path lastForwardPathMsg_;

    /// stored but almost not used
    std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros_;

    void onForwardTrailMsg(const nav_msgs::msg::Path::SharedPtr trailMessage);

    void publishGoalMarker(const geometry_msgs::msg::Pose &pose, double r, double g, double b);

    void clearGoalMarker();

    virtual void createDefaultUndoPathPlan(const geometry_msgs::msg::PoseStamped &start,
                                           const geometry_msgs::msg::PoseStamped &goal, std::vector<geometry_msgs::msg::PoseStamped> &plan);

    double skip_straight_motion_distance_; //meters

    double puresSpinningRadStep_; // rads

    double transform_tolerance_;

    std::string name_;

    std::shared_ptr<tf2_ros::Buffer> tf_;

};
} // namespace backward_global_planner
} // namespace cl_move_base_z