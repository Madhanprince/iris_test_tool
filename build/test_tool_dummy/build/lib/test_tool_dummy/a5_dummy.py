import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Range
from iris_interfaces.msg import (
    WheelEncoders,
    UltrasonicRanges,
    WaterTankLevels,
    A5Status,
    LedControl,
)


class A5DummyNode(Node):

    def __init__(self):
        super().__init__('a5_dummy')

        self.wheel_pub = self.create_publisher(WheelEncoders, 'wheel_encoders', 10)
        self.ultra_pub = self.create_publisher(UltrasonicRanges, 'ultrasonic_ranges', 10)
        self.water_pub = self.create_publisher(WaterTankLevels, 'water_tank_levels', 10)
        # self.status_pub = self.create_publisher(A5Status, 'a5_control_status', 10)

        self.led_sub = self.create_subscription(
            LedControl,
            'led_command',
            self.led_command_callback,
            10,
        )

        self.publish_timer = self.create_timer(1.0, self.publish_sensor_data)
        self.counter = 0

        self.get_logger().info('A5 dummy publisher started')

    def led_command_callback(self, msg: LedControl):
        self.get_logger().info(
            f'Received LED command={msg.led_command} left={msg.left_indicator} right={msg.right_indicator}'
        )

    def publish_sensor_data(self):
        wheel = WheelEncoders()
        wheel.left_wheel_ticks = int(self.counter * 10)
        wheel.right_wheel_ticks = int(self.counter * 10 + 5)
        self.wheel_pub.publish(wheel)

        ultra = UltrasonicRanges()
        ultra.ultrasonic_1 = Range()
        ultra.ultrasonic_2 = Range()
        ultra.ultrasonic_3 = Range()
        ultra.ultrasonic_4 = Range()

        ultra.ultrasonic_1.range = 0.25 + (self.counter % 5) * 0.05
        ultra.ultrasonic_2.range = 0.30 + (self.counter % 5) * 0.04
        ultra.ultrasonic_3.range = 0.35 + (self.counter % 5) * 0.03
        ultra.ultrasonic_4.range = 0.40 + (self.counter % 5) * 0.02
        self.ultra_pub.publish(ultra)

        water = WaterTankLevels()
        water.fresh_water_tank_level = int((self.counter * 7) % 101)
        water.dirty_water_tank_level = int((self.counter * 11) % 101)
        self.water_pub.publish(water)

        # status = A5Status()
        # status.mode_and_status = f'A5 dummy status {self.counter}'
        # self.status_pub.publish(status)

        # self.counter += 1


def main(args=None):
    rclpy.init(args=args)
    node = A5DummyNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
