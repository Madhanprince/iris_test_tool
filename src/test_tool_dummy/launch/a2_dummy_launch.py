from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='test_tool_dummy',
            executable='a2_dummy',
            name='a2_dummy',
            output='screen'
        )
    ])
