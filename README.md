

# 编译
```bash
./ros_docker

catkin_make
```


# 运行
```bash
source ./devel/setup.bash

roscore

rosrun sun_test pub

rosrun sun_test sub

roslaunch  sun_test test.xml
```