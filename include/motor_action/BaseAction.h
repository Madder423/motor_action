#pragma once
#include<iostream>
#include "rclcpp/rclcpp.hpp"

class BaseAction{
protected:
    std::string name;  //名称
    std::shared_ptr<rclcpp::Node> node; //调用者指针
    BaseAction(std::string _name,std::shared_ptr<rclcpp::Node> _node):name(_name),node(_node){};
    ~BaseAction(){};
public:
    virtual void motor_act(const int) = 0;        //电机行为
    std::string get_name(){return this->name;}
};
