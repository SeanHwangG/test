# ROS

![ROS](images/20210218_234217.png)
![ROS : Matser, Node](images/20210218_234226.png)

> Example

* roscore: run master node
* rosrun `n`: run package `n` (turtlesim turtle_teleop_key)
* catkin_make: build

* cd ~/catkin_ws/src
* catkin_create_pkg my_package std_msgs roscpp: create new ROS package

* workspace: user directory that will used to create the user ROS packages
  * you have to add setup.bash in the ~/.bashrc file
  * ROS workspace is built using catkin_make command
  * ROS workspace contains three main folders: source, devel, build

* package
  * catkin_create_pkg `p` std_msgs roscpp
  * cd .
  * catkin_make

* publisher: name for the topic to publish
  * type of the message
  * frequency of the topic publication

* Subscriber: name for the topic to listen to
  * type of the messages to be received

## Catkin

> Term

* dry packages: packages that use the deprecated rosbuild build system
* Wet packages: packages that have been updated for use with catkin
* package.xml: define a license of your package in package.xml
  * contains two dependencies: build a package, execute a package

```cpp
find_package(catkin REQUIRED COMPONENTS cpp_common geometry_msgs)
find_package(Log4cxx QUIET)
generate_messages(DEPENDENCIES geometry_msgs)
catkin_package(
  CATKIN_DEPENDS cpp_common geometry_msgs
  DEPENDS Log4cxx
)
add_library(example_lib src/example.cpp)
target_link_libraries(example_lib ${catkin_LIBRARIES} ${LOG4CXX_LIBRARIES})
add_dependencies(example_lib geometry_msgs_gencpp)
```

```py
# setup.py
from distutils.core import setup

setup(
  ...
  requires=['rospy'],
  )
```

## ROS Message

* rosmsg list
* rosmsg show `n` `t`: show `t` variable in `n` package

## ROS Node

![Nodes](images/20210628_212136.png)

* Each node in ROS should be responsible for a single, module purpose
* Each node can send and receive data to other nodes via topics, actions, or parameters
* [+] Fault tolerance as crashes are isloated, reduced code complexity, hidden implementation
* [ex] controlling, motors, laser range-finder

> Term

* graph resource name: uniquely identifies them into rest of system, shouldn't have executables with same name in a package
  * valid names: ([a-Z-/][0-9a-za-Z_/]*)
* Package Resource Names: used in ROS with filesystem-level to simplify process of referring to files, data types on disk

> Example

* __name:  name of the node
* __log: location of the log file
* __ip: substitute for ROS_IP
* __hostname: substitutes for ROS_HOSTNAME
* __master: ROS_MASTER_URL
* __ns: ROS_NAMESPACE

* rosnode
  * list: list all the running nodes
  * info `n`: give details of the node

{% tabs %}
{% tab title='cpp' %}

* ros
  * init();
    * argc, argv, "my_node_name"
    * init_options

  ```cpp
  #include <ros/ros.h>
  #include <signal.h>

  /* 1. shut down */
  // Test for shutdown
  while (ros::ok()) {
    ...
  }

  // signal handler
  void mySigintHandler(int sig) {
    // Do some custom action. [ex] publish a stop message to some other nodes
    // All the default sigint handler does is call shutdown()
    ros::shutdown();
  }

  int main(int argc, char** argv) {
    ros::init(argc, argv, "my_node_name", ros::init_options::NoSigintHandler);
    ros::NodeHandle nh;

    // Override the default ros sigint handler, must be set after first NodeHandle is created
    signal(SIGINT, mySigintHandler);

    ros::spin();
    return 0;
  }
  ```

{% endtab %}
{% endtabs %}

## ROS Topic

* vital element of the ROS graph that act as a bus for nodes to exchange messages
* publisher-subscriber model allow nodes to subscribe to data streams and get continual updates
* Can be one-to-one, one-to-many, and many-to-many

{% tabs %}
{% tab title='ros' %}

* rostopic
  * bw: display bandwidth used by topic
  * echo `n`: echo all changes in topic (rostopic echo turtle1/cmd_vel)
  * hz: reports the rate at which data is published.
  * list: list all the topics
  * pub: `topic` `msg_type` `args` ([ex] -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2,0,0]' '[0,0,1]')
    * -1: only publish one message then exit
    * -r: steady stream of topic
  * type: topic type ([ex] /turtle1/command_velocity | rosmsg show: See detail)

{% endtab %}
{% endtabs %}

## ROS Service

* Based on a call-and-response model
* One time communication: Only provide data when are specifically called by a client
* [ex] Request robot to perform a specific action, find path from point A to B, spawn one robot in simulator

> Example

* ros service
  * list: return a list of all services currently active in the system
    * -t: show types
  * type `service`
    * [ex] Empty: service call sends no data when making a request and receives no data when receiving a response

## ROS Action

![Action](images/20210628_212858.png)

* communication types intended for long running tasks built on topics and services
* consist of three parts: a goal, feedback, and a result
* functionality is similar to services, except actions are preemptable, can cancel them while executing

{% tabs %}
{% tab title='shell' %}

* ros2
  * list: all actions in ROS graph
    * -t: show types
  * send_goal `action_name` `action_type` `values`

{% endtab %}
{% endtabs %}
