

# 编译
```bash
# 没有安装ros环境的话可以使用以下命令进入ros1 docker
./ros_docker

# 编译
catkin_make
```


# 运行
```bash
source ./devel/setup.bash

# 运行
roslaunch  sun_test test.xml

# 查看日志
rosrun rqt_console rqt_console
```