#pragma once
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "BaseAction.h"
#include "bupt_interfaces/srv/motor_action.hpp"
#include <vector>
#include <algorithm>

class motor_action_node : public rclcpp::Node {
public:
    motor_action_node(std::string name) : Node(name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        // 创建服务
        action_srv =
        this->create_service<bupt_interfaces::srv::MotorAction>(
        "motor_action",
        std::bind(&motor_action_node::handle_motorAction, this,
                  std::placeholders::_1, std::placeholders::_2));
  }
    void add_action(std::shared_ptr<BaseAction> _action){this->actions.push_back(_action);}//增加传感器
private:
    rclcpp::Service<bupt_interfaces::srv::MotorAction>::SharedPtr action_srv;   //声明服务
    // ros2 service call /ControlState bupt_interfaces/srv/ControlState "{sensor_name: DT_35, open: 1}"
    std::vector<std::shared_ptr<BaseAction>> actions;
    void handle_motorAction(
        const std::shared_ptr<bupt_interfaces::srv::MotorAction::Request> request,
        std::shared_ptr<bupt_interfaces::srv::MotorAction::Response> respense){
        RCLCPP_INFO(this->get_logger(),"收到请求");
        auto action = find_if(this->actions.begin(),this->actions.end(),[&request](std::shared_ptr<BaseAction> &action)
        {
            return action->get_name()==request->action_name;
        });
        if(action==actions.end()){
            std::cout<<"没有对应电机"<<std::endl;
            respense->message = "没有对应电机";
        }
        else
        {
            (*action)->motor_act(request->act);
            respense->message = "启动动作";
        }
    }
};
