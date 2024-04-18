#pragma once
#include "BaseAction.h"
#include "bupt_can/bupt_can.h"

enum command
{
    SHOOT, 
    HANDGRIP, 
    HANDRELEASE
};

class R1_action : public BaseAction{
private:
    std::shared_ptr<Can> can; //can智能指针
    int motor_id;   
public:
    R1_action(const std::shared_ptr<rclcpp::Node> _node, const std::shared_ptr<Can> _can):
    BaseAction("R1_action", _node), can(_can){}
    virtual void motor_act(const int cmd) override;
};

