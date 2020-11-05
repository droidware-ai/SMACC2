/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <move_base_z_client_plugin/move_base_z_client_plugin.h>
#include <pluginlib/class_list_macros.hpp>

namespace cl_move_base_z
{

ClMoveBaseZ::ClMoveBaseZ(std::string moveBaseName)
 : Base(moveBaseName)
{
    //RCLCPP_INFO(getNode()->get_logger(),"Smacc Move Base Action Client");
}

std::string ClMoveBaseZ::getName() const
{
    return "MOVE BASE ACTION CLIENT";
}

void ClMoveBaseZ::initialize()
{
    SmaccActionClientBase<nav2_msgs::action::NavigateToPose>::initialize();
}

ClMoveBaseZ::~ClMoveBaseZ()
{
}
} // namespace smacc

PLUGINLIB_EXPORT_CLASS(cl_move_base_z::ClMoveBaseZ, smacc::ISmaccClient)