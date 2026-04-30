from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        Node(
            package='test_tool',
            executable='dummy_test',
            name='dummy_node_1',
            output='screen'
        ),

        Node(
            package='test_tool',
            executable='dummy_test_1',
            name='dummy_node',
            output='screen'
        )
    ])