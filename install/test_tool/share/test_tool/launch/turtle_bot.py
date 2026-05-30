from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():

    turtlebot_pkg = get_package_share_directory('turtlebot3_gazebo')

    slam_pkg = get_package_share_directory('slam_toolbox')


    turtlebot_launch = os.path.join(
        turtlebot_pkg,
        'launch',
        'turtlebot3_world.launch.py'
    )

    slam_launch = os.path.join(
        slam_pkg,
        'launch',
        'online_async_launch.py'
    )

    return LaunchDescription([

        # Set TurtleBot3 Model
        SetEnvironmentVariable(
            name='TURTLEBOT3_MODEL',
            value='burger'
        ),

        # TurtleBot3 Gazebo
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(turtlebot_launch)
        ),

        # SLAM Toolbox
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(slam_launch)
        ),

    ])