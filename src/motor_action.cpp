#include "motor_action_node.h"
#include "R1_action.h"

int main(int argc,char **argv)
{
    rclcpp::init(argc, argv);
    std::cout<<"test"<<std::endl;
    auto node = std::make_shared<motor_action_node>("OtherMotors");
    std::shared_ptr<Can> can_handle = std::make_shared<Can>("can0");
    can_handle->can_start();
    node->add_action(std::make_shared<R1_action>(node,can_handle));
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}