#include "R1_action.h"

union{
    uint8_t u8[8];
    float fl[2];
    uint32_t in[2];
} payload;

void R1_action::motor_act(const int cmd)
{
    int can_id=0;
    switch (cmd)
    {
    case SHOOT:
        can_id = 0xA0;
        payload.fl[0] = 0;
        payload.in[1] = 20;
        break;
    case HANDGRIP:
        can_id = 0xA1;
        break;
    case HANDRELEASE:
        can_id = 0xA2;
        break;
    default:
        break;
    }
    std::array<uint8_t, 8> data;
    std::copy(std::begin(payload.u8), std::end(payload.u8), data.begin());
    can->send_can(can_id,Can::CAN_ID_STD,8,data);
}