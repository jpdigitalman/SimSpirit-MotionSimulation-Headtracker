# SimSpirit ViewTracer™

The SimSpirit ViewTracer™ is a crucial component of the SimSpirit Motion Simulator platform, offering precise head movement tracing using Image Recognition AI or fixed IMU for an immersive and realistic simulation experience. This README provides an overview of the ViewTracer™ module, including its features, integration instructions, and additional information on supported IMUs.
![Image SimSpirit PCB Layout](https://github.com/jpdigitalman/SimSpirit-MotionSimulation-Headtracker/blob/main/PCB_Layout/HT3.png?raw=true)
## Features

- **BNO086 or LSM6DS3 IMU**: The ViewTracer™ supports two options for the inertial measurement unit (IMU). The user can choose between the BNO086 and LSM6DS3 IMU, depending on their chosen schematics and PCB assembly.
- **BNO086 Stability**: The BNO086 IMU, known for its stability, provides reliable and accurate tracking of head movements, including yaw, pitch, and roll.
- **LSM6DS3 Sensitivity**: The LSM6DS3 IMU offers high precision and sensitivity, ensuring precise and responsive tracking of head orientation.
- **Automatic Calibration**: The ViewTracer™ simplifies calibration by implementing an automatic calibration process. Simply press the calibration button once, and the calibration will be performed automatically.
- **ESPnow Communication**: To pair the ViewTracer™ with the SimSpirit mainboard, the ESPnow protocol is utilized. Pairing requires the use of the mainboard's MAC address to establish a connection.

## Getting Started

To integrate the SimSpirit ViewTracer™ into your SimSpirit Motion Simulator setup, follow these steps:

1. **Hardware Setup**: Connect the ViewTracer™ module according to the provided schematics.
2. **Software Configuration**: Using PlatformIO, install the necessary software libraries and dependencies specific to the chosen IMU on your development environment.
3. **Mainboard Integration**: Use the ESPnow protocol to pair the ViewTracer™ with the SimSpirit mainboard. Ensure you have the MAC address of the mainboard for the pairing process.
4. **Automatic Calibration**: Simply press the calibration button on the ViewTracer™ module once to initiate the automatic calibration process. The module will handle the calibration automatically.
5. **Integration with SimSpirit**: Conect the ViewTracer™ to the Mainboard for real-time tracking of head movements and pitch-roll synchronization with the simulation. 
6. **Testing and Fine-Tuning**: Test the ViewTracer™ module in various simulation scenarios to ensure accurate tracking and make any necessary adjustments for optimal performance.

## License

SimSpirit ViewTracer™ is released under the [MIT License](https://opensource.org/licenses/MIT). You are free to use, modify, and distribute the ViewTracer™ module in accordance with the terms and conditions stated in the license.

## Support

For any questions, issues, or support regarding the SimSpirit ViewTracer™ module, please open an issue on the [GitHub repository](https://github.com/jpdigitalman/SimSpirit-Motion-Simulator-Platform)

---

*Note: This README provides a general overview and guide for the SimSpirit ViewTracer™ module. For detailed instructions, troubleshooting, and updates, please refer to the project's GitHub repository.*
