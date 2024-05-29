# Pose-Sensor-with-N-Optical-Mice
Design of an optical pose sensor based on sensor fusion of N optical mice sensors (FCT3065-XY model from Bluetooth mice) to estimate the pose and real time odometry of an autonomous differential drive robot. Communication protocol with the sensors via bit banging in Arduino [[1]], design of data processing code in Python and display interface using a URDF node model in ROS2 for a final visualization in RViz2. 

Autors: Laura Patiño Restrepo, Physics Engineering undergraduate student at EAFIT University, Colombia, lpatinor@eafit.edu.co
& Davinson Castaño Cano, professor at EAFIT University, Colombia, dcasta25@eafit.edu.co
        
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
* ROS 2 Humble with turtlesim package

## Instructions to run Arduino and Python-ROS 2 node
1. After your connections and geometry are fixed, start by running the Arduino code for 2 or 3 sensors and make sure you are obtaining readings from all of them and that they are being delivered in real time simultaneously. Then, close the Serial Monitor but do not close the Arduino program.

2. Execute Windows PowerShell as administrator and make sure your Arduino MEGA or microcontroller is connected by writing the command `usbipd list` and watch the port busid #-# were is being read, then to connect the device to WSL Ubuntu run `usbipd bind --busid=1-1` followed by `usbipd attach --wsl --busid=1-1`.
 
3. If using Visual Studio Code for the Python block, open the remote window for WSL Ubuntu (search for more documentation and tutorials about this after installing Ubuntu Linux and ROS 2 if needed) and open the folder of the `workspace.zip` (make sure this folder is previously in your home folder from Ubuntu). Let´s review the files in this folder briefly:

* In `workspace` you will find a `src` folder which will be the main editable. Other folders called `build`, `install` and `log` will be created automatically once you run the whole program.
* In `src` you will also find a folder called `sensor` which contains other automatically generated files, the editable `setup.py`, the `test_launch.py` file which allows to execute various nodes simultaneously and were you will need to edit the arguments for your 'static_transform_publisher' nodes depending on your specific configuration and mouse locations and initial orientations. And finally another `sensor` folder with all the other editable files: `odom_puplish.py`, `pose_publisher.py` and `tf_static.py`.
* `pose_publisher.py` is the main data processing node including the mathematical model to calculate de pose (make the changes in distances D and number of sensors for your configuration again).
* `odom_puplish.py`and `tf_static.py` will use the message of the pose (after transforming the angle to quatrnion form) to publish the change of pose incrementally or to 'draw' the trajectory and the static transformations or geometric links between sensors respectively.

4. Once you make all the adjustments to these codes, proceed to run the complete program. Start by opening a terminal and checking you are in the correct path by typing `cd workspace/` (if you do not have ROS 2 automatically icialized on terminal, type `source /opt/ros/humble/setup.bash`), then check the Arduino direction and connection with `lsusb` and `ls /dev/ttyA*` and make changes if necessary in the line `self.arduino = serial.Serial('/dev/ttyACM0', Baud Rate)`. To compile use `colcon build` followed by `source install/setup.bash`and `ros2 launch sensor test_launch.py` to open RViz 2 visualization tool.
   
5. Finally, open the file in RViz by selecting 'Recent Configs' and selecting the path of your workspace folder. You will automatically see the interface with the robot and mice simulation with coordinate frames that will move accordingly to your real robot's movement as long as everything is okay and the terminal does not report any error. To end the process, go back to the terminal and press `CTRL + C`. Make sure to delete or save and move the generated .txt files elsewhere from the workspace folder before making another measurement test or else, they will overwrite.

   
## Outstanding issues 

## References
[1]: https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
1. https://github.com/VineetSukhthanker/FCT3065-XY_MouseSensor
