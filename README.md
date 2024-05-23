# Pose-Sensor-with-N-Optical-Mice
Design of an optical pose sensor based on sensor fusion of N optical mice sensors (FCT3065-XY model from Bluetooth mice) to estimate the pose and real time odometry of an autonomous differential drive robot. Communication protocol with the sensors via bit banging in Arduino [[1]], design of data processing code in Python and display interface using a URDF node model in ROS2 for a final visualization in RViz2. 
## Connections and geometry 
Each sensor must be connected as indicated:
* VDD to 3.3 V of Arduino
* SSIO (data pin) and SCLK to (clock pin) to PWM pairs or communication pins
* all GND must be connected between them

Additionally, in this work the location of the sensors is triangular but their orientations are all the same as the robot´s coordinate frame. This is important to determine and change the distance D between the 2 sensors located over the rotation axis and the distance L from this axis to sensor #3. 


## Requirements
* Arduino IDE
* Ubuntu Linux
* Python 3.12.2
* ROS 2 Humble

## Instructions to run ROS 2 node
## Outstanding issues 

## References
[1]: https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
1. https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
