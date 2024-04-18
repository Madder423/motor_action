#include "example_action.h"
void example::motor_act(const int pos)
{
    board_ptr->PosCtrl(motor_id, pos);
}