import rclpy
from rclpy.node import Node

from iris_interfaces.srv import A2Command
from iris_interfaces.msg import (
    A2FunctionalStatus,
    A2FaultStatus,
    BrushStatus,
    VacuumStatus,
    ActuatorStatus,
    BrushFaults,
    VacuumFaults
)


class A2DummyNode(Node):

    def __init__(self):
        super().__init__('a2_dummy')

        self.srv = self.create_service(
            A2Command,
            'a2_control/a2_command',
            self.handle_a2_command
        )

        self.status_pub = self.create_publisher(
            A2FunctionalStatus,
            '/a2_status',
            10
        )

        self.fault_pub = self.create_publisher(
            A2FaultStatus,
            '/a2_faults',
            10
        )

        # internal state
        self.brush_status = 0
        self.vacuum_status = 0

        self.get_logger().info('A2 dummy server started')

    def handle_a2_command(self, request, response):

        # Brush command
        if hasattr(request, 'brush_command'):
            if request.brush_command:
                self.brush_status = 1
            else:
                self.brush_status = 0

        # Vacuum command
        if hasattr(request, 'vacuum_command'):
            if request.vacuum_command:
                self.vacuum_status = 1
            else:
                self.vacuum_status = 0

        response.brush_status = int(self.brush_status)
        response.vacuum_status = int(self.vacuum_status)

        # publish updated status
        self.publish_status()

        return response

    def publish_status(self):

        msg = A2FunctionalStatus()

        # ---------------- BRUSH ----------------
        brush = BrushStatus()

        brush.brush_motor_command = int(self.brush_status)
        brush.brush_motor_status = int(self.brush_status)

        brush.brush_actuator = ActuatorStatus()

        # Brush ON
        if self.brush_status == 1:
            brush.brush_actuator.moving_down = 1
            brush.brush_actuator.hold_down = 1
            brush.brush_actuator.moving_up = 0
            brush.brush_actuator.hold_up = 0

        # Brush OFF
        else:
            brush.brush_actuator.moving_down = 0
            brush.brush_actuator.hold_down = 0
            brush.brush_actuator.moving_up = 1
            brush.brush_actuator.hold_up = 1

        # ---------------- VACUUM ----------------
        vacuum = VacuumStatus()

        vacuum.vacuum_motor_command = int(self.vacuum_status)
        vacuum.vacuum_motor_status = int(self.vacuum_status)

        vacuum.squeeze_actuator = ActuatorStatus()

        # Vacuum ON
        if self.vacuum_status == 1:
            vacuum.squeeze_actuator.moving_down = 1
            vacuum.squeeze_actuator.hold_down = 1
            vacuum.squeeze_actuator.moving_up = 0
            vacuum.squeeze_actuator.hold_up = 0

        # Vacuum OFF
        else:
            vacuum.squeeze_actuator.moving_down = 0
            vacuum.squeeze_actuator.hold_down = 0
            vacuum.squeeze_actuator.moving_up = 1
            vacuum.squeeze_actuator.hold_up = 1

        # assign submessages
        msg.brush = brush
        msg.vacuum = vacuum

        msg.water_pump = 0
        msg.detergent_pump = 0

        # ---------------- FAULT STATUS ----------------
        fault = A2FaultStatus()

        fault.a2_fault_status = 0

        # Brush faults
        fault.brush = BrushFaults()

        fault.brush.actuator_digital_fault = 1
        fault.brush.drive_brush_current_digital_fault = 1
        fault.brush.overcurrent_analog_fault = 0
        fault.brush.temperature_fault = 0
        fault.brush.undercurrent_analog_fault = 0

        # Vacuum faults
        fault.vacuum = VacuumFaults()

        fault.vacuum.squeeze_actuator_digital_fault = 0
        fault.vacuum.drive_brush_current_digital_fault = 0
        fault.vacuum.overcurrent_analog_fault = 0
        fault.vacuum.undercurrent_analog_fault = 0

        # other faults
        fault.water_pump_digital_fault = 0
        fault.detergent_pump_digital_fault = 0
        fault.brush_vacuum_motor_driver_digital_fault = 0
        fault.water_and_detergent_pump_flow_fault = 0

        # publish messages
        self.status_pub.publish(msg)
        self.fault_pub.publish(fault)


def main(args=None):

    rclpy.init(args=args)

    node = A2DummyNode()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()