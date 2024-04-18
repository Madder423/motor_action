#pragma once
#include "BaseAction.h"
#include "bupt_can/bupt_can.h"
#include "motor_lib/dji_board.h"

class example : public BaseAction{
private:
    std::shared_ptr<Can> _can; //can智能指针
    std::shared_ptr<DJIBoard> board_ptr; //大疆板
    int motor_id;   
public:
    example(const std::shared_ptr<rclcpp::Node> _node,std::shared_ptr<DJIBoard> board,int _motor_id):
    BaseAction("example_action", _node),board_ptr(board),motor_id(_motor_id)
    {
        board->MotorOn(motor_id);
        board->PosCfg(motor_id,100);
    }
    virtual void motor_act(const int) override;
};

