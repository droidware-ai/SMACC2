cmake_minimum_required(VERSION 3.5)
project(pure_spinning_local_planner)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(nav2_core)
find_package(nav_msgs)
find_package(nav2_costmap_2d)
find_package(geometry_msgs)
find_package(tf2)
find_package(move_base_z_planners_common)
find_package(pluginlib)
find_package(nav_2d_utils)

set(dependencies
    nav2_core
    nav_msgs
    nav2_costmap_2d
    geometry_msgs
    tf2
    move_base_z_planners_common
    pluginlib
    nav_2d_utils)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
            src/${PROJECT_NAME}/pure_spinning_local_planner.cpp)

# prevent pluginlib from using boost
target_compile_definitions(${PROJECT_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")
pluginlib_export_plugin_description_file(nav2_core pslp_plugin.xml)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies})

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
)

install(FILES
   pslp_plugin.xml
   DESTINATION share
)


ament_package()
