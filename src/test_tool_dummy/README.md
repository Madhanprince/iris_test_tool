test_tool_dummy

This package provides a simple Python node that offers a dummy `a2_control/a2_command` service and publishes `/a2_status` and `/a2_faults` so you can test the `A2_service` UI.

Run:

```bash
# from workspace root
colcon build --packages-select test_tool_dummy
# in a new terminal
. install/setup.bash
ros2 run test_tool_dummy a2_dummy
```

The service logic:
- `brush_command == 0` -> sets `brush_status=1` (active)
- `brush_command != 0` -> `brush_status=0`
- `vacuum_command == 1` -> `vacuum_status=1` (active)
- otherwise `vacuum_status=0`

The node publishes an `A2FunctionalStatus` and `A2FaultStatus` every second and immediately after each service call.

Launch with `ros2 launch`:

```bash
# after building and sourcing the workspace
ros2 launch test_tool_dummy a2_dummy_launch.py
```

To test together with your UI node (example):

```bash
# in one terminal
. install/setup.bash
ros2 launch test_tool_dummy a2_dummy_launch.py

# in another terminal
. install/setup.bash
ros2 run test_tool test_tool_node
```