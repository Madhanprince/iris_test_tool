import rclpy
from rclpy.node import Node

from iris_interfaces.srv import A2Command
from iris_interfaces.msg import A2FunctionalStatus, A2FaultStatus, BrushStatus, VacuumStatus, ActuatorStatus

class A2DummyNode(Node):
    def __init__(self):
        super().__init__('a2_dummy')
        self.srv = self.create_service(A2Command, 'a2_control/a2_command', self.handle_a2_command)
        self.status_pub = self.create_publisher(A2FunctionalStatus, '/a2_status', 10)
        self.fault_pub = self.create_publisher(A2FaultStatus, '/a2_faults', 10)

        # periodic status publisher so UI sees current state even without requests
        self.timer = self.create_timer(1.0, self.publish_status)

        # internal state
        self.brush_status = 0
        self.vacuum_status = 0
        self.get_logger().info('A2 dummy server started')

    def handle_a2_command(self, request, response):
        # Simple logic: brush_command==0 -> brush ON, vacuum_command==1 -> vacuum ON
        if hasattr(request, 'brush_command'):
            if request.brush_command == 0:
                self.brush_status = 1
            else:
                self.brush_status = 0
        if hasattr(request, 'vacuum_command'):
            if request.vacuum_command == 1:
                self.vacuum_status = 1
            else:
                self.vacuum_status = 0

        response.brush_status = int(self.brush_status)
        response.vacuum_status = int(self.vacuum_status)

        # immediately publish a status reflecting the new state
        self.publish_status()
        return response

    def publish_status(self):
        msg = A2FunctionalStatus()
        # brush submessage
        brush = BrushStatus()
        brush.brush_motor_command = 0 if self.brush_status else 1
        brush.brush_motor_status = int(self.brush_status)
        brush.brush_actuator = ActuatorStatus()
        brush.brush_actuator.moving_down = 0
        brush.brush_actuator.hold_down = 0
        brush.brush_actuator.moving_up = 0
        brush.brush_actuator.hold_up = 0

        vacuum = VacuumStatus()
        vacuum.vacuum_motor_command = int(self.vacuum_status)
        vacuum.vacuum_motor_status = int(self.vacuum_status)
        vacuum.squeeze_actuator = ActuatorStatus()
        vacuum.squeeze_actuator.moving_down = 0
        vacuum.squeeze_actuator.hold_down = 0
        vacuum.squeeze_actuator.moving_up = 0
        vacuum.squeeze_actuator.hold_up = 0

        msg.brush = brush
        msg.vacuum = vacuum
        msg.water_pump = 0
        msg.detergent_pump = 0

        fault = A2FaultStatus()
        fault.a2_fault_status = 0
        # construct submessages with safe defaults
        from iris_interfaces.msg import BrushFaults, VacuumFaults
        fault.brush = BrushFaults()
        fault.brush.actuator_digital_fault = 0
        fault.brush.drive_brush_current_digital_fault = 0
        fault.brush.overcurrent_analog_fault = 0
        fault.brush.temperature_fault = 0
        fault.brush.undercurrent_analog_fault = 0

        fault.vacuum = VacuumFaults()
        fault.vacuum.squeeze_actuator_digital_fault = 0
        fault.vacuum.drive_brush_current_digital_fault = 0
        fault.vacuum.overcurrent_analog_fault = 0
        fault.vacuum.undercurrent_analog_fault = 0

        fault.water_pump_digital_fault = 0
        fault.detergent_pump_digital_fault = 0
        fault.brush_vacuum_motor_driver_digital_fault = 0
        fault.water_and_detergent_pump_flow_fault = 0

        # publish
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
