1. See Readme.txt to set up your computer environment(Qt4.8.7+ros-jade)

2.install ros-jade-mavlink_2015.7.7-0trusty_amd64.deb

3. Copy and compile packages in your catkin_ws/src you'd better compile Package "mavros" first and then add Package "station" and compile again. 

4. Folder Start contains shells to mavros launchfiles station. To start station, plugin in your xbee and excute "./start.sh" in terminal.
Note: you must change mode for .sh first time you use. Type "sudo chmod 700 YOUR_TARGET_SHELL".
Note: you must use "cd" to enter the "Start" folder before you type "./start.sh". Do not use "./Start/start.sh"
