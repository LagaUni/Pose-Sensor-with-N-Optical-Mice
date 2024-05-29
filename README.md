# Pose-Sensor-with-N-Optical-Mice
Design of an optical pose sensor based on sensor fusion of N optical mice sensors (FCT3065-XY model from Bluetooth mice) to estimate the pose and real time odometry of an autonomous differential drive robot. Communication protocol with the sensors via bit banging in Arduino [[1]], design of data processing code in Python and display interface using a URDF node model in ROS2 for a final visualization in RViz2. 
## Connections and geometry 
Each sensor must be connected as indicated:
* VDD to 3.3 V of Arduino
* SSIO (data pin) and SCLK to (clock pin) to PWM pairs or communication pins
* all GND must be connected between them

Additionally, in this work the location of the sensors is triangular but their orientations are all the same as the robot´s coordinate frame. This is important to determine and change the distance D between the 2 sensors located over the rotation axis and the distance L from this axis to sensor #3. The position given from the sensors data is in mm. 


## Requirements
* Arduino IDE
* Ubuntu Linux
* Python 3.12.2
* ROS 2 Humble

## Instructions to run Arduino and ROS 2 node
After your connections and geometry are fixed, start by running the Arduino code for 2 or 3 sensors and make sure you are obtaining readings from all of them and that they are being delivered in real time simultaneously. Then, close the Serial Monitor but do not close the Arduino program.
Execute Windows PowerShell as administrator and make sure your Arduino MEGA or microcontroller is connected by writing the command `usbipd list` and watch the port busid #-# were is being read, then to connect the device to Ubuntu run `usbipd bind --busid=1-1` followed by `usbipd attach --wsl --busid=1-1`.
If using Visual Studio Code for the Python block, open the remote window for WSL Ubuntu (search for more documentation and tutorials about this after installing Ubuntu Linux and ROS 2 if needed) and open the file of the workspace.zip. 

## Outstanding issues 

## References
[1]: https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
1. https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
