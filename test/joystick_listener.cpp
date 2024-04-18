#include "rclcpp/rclcpp.hpp"
#include "bupt_interfaces/msg/joystick.hpp"
#include "bupt_interfaces/srv/motor_action.hpp"

class joy_listener : public rclcpp::Node
{
public:
    joy_listener(std::string name) : Node(name)
    {
        // 创建一个订阅者订阅话题
        command_subscribe_ = this->create_subscription<bupt_interfaces::msg::Joystick>("joystick", 10, std::bind(&joy_listener::command_callback, this, std::placeholders::_1));
        // 创建客户端
        client_ = this->create_client<bupt_interfaces::srv::MotorAction>("motor_action");
    }
    void send_request(const uint16_t button) {
    // 1.等待服务端上线
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
      //等待时检测rclcpp的状态
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
        return;
      }
      RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
    }
    // 2.TODO:构造请求的
    auto request =
      std::make_shared<bupt_interfaces::srv::MotorAction_Request>();
    if((button & 2) && !(last_joystick.button & 2))
    {
        request->action_name = "R1_action";
        request->act = 0;
        client_->async_send_request(
        request, std::bind(&joy_listener::result_callback_, this,
                         std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "发射");
    }
    else if((button & 256) && !(last_joystick.button & 256))
    {
        request->action_name = "R1_action";
        request->act = 1;
        client_->async_send_request(
        request, std::bind(&joy_listener::result_callback_, this,
                         std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "取");
    }
    else if((button & 512) && !(last_joystick.button & 512))
    {
        request->action_name = "R1_action";
        request->act = 2;
        client_->async_send_request(
        request, std::bind(&joy_listener::result_callback_, this,
                         std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "放");
    }
    }

private:
     // 声明一个订阅者
    rclcpp::Subscription<bupt_interfaces::msg::Joystick>::SharedPtr command_subscribe_;
     // 声明客户端
    rclcpp::Client<bupt_interfaces::srv::MotorAction>::SharedPtr client_;
    // 上次的手柄消息
    bupt_interfaces::msg::Joystick last_joystick;

  void result_callback_(
    rclcpp::Client<bupt_interfaces::srv::MotorAction>::SharedFuture
      result_future) {
    auto response = result_future.get();
    //RCLCPP_INFO(this->get_logger(), "响应结果：%s", response->message);
  }
     // 收到话题数据的回调函数
  void command_callback(const bupt_interfaces::msg::Joystick::SharedPtr msg)
  {
      //std::cout<<msg->button<<std::endl;
      send_request(msg->button);
      last_joystick = *(msg);
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  /*创建对应节点的共享指针对象*/
  auto node = std::make_shared<joy_listener>("joy_listener");
  /* 运行节点，并检测退出信号*/
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

