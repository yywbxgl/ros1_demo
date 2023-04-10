

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <visualization_msgs/msg/marker.hpp>


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("basic_shapes"), count_(0)
    {
      publisher_ = this->create_publisher<visualization_msgs::msg::Marker>("visualization_marker", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
        //   auto message = std_msgs::msg::String();
        //   message.data = "Hello, world! " + std::to_string(count_++);
        //   RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        //   publisher_->publish(message);

        visualization_msgs::msg::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "/my_frame";
        marker.header.stamp = rclcpp::Node::now();

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        marker.ns = "basic_shapes";
        marker.id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        marker.type = shape_;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::msg::Marker::ADD;

        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = 1.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;

        // marker.lifetime = rclcpp::Duration(0);

        // Publish the marker
        // while (publisher_.getNumSubscribers() < 1)
        // {
        //     if (!ros::ok())
        //     {
        //         return 0;
        //     }
        //     ROS_WARN_ONCE("Please create a subscriber to the marker");
        //     sleep(1);
        // }
        publisher_->publish(marker);

        // Cycle between different shape_s
        switch (shape_)
        {
            case visualization_msgs::msg::Marker::CUBE:
            shape_ = visualization_msgs::msg::Marker::SPHERE;
            break;
            case visualization_msgs::msg::Marker::SPHERE:
            shape_ = visualization_msgs::msg::Marker::ARROW;
            break;
            case visualization_msgs::msg::Marker::ARROW:
            shape_ = visualization_msgs::msg::Marker::CYLINDER;
            break;
            case visualization_msgs::msg::Marker::CYLINDER:
            shape_ = visualization_msgs::msg::Marker::CUBE;
            break;
        }

    }

    rclcpp::TimerBase::SharedPtr timer_;
    int32_t shape_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_;
    size_t count_;
};


int main(int argc, char * argv[])
{
  printf("-------\n");
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}

