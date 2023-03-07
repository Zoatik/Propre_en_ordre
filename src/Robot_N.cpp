#include "Robot_N.h"

Robot_N::Robot_N()
{
    //ctor
}

Robot_N::Robot_N(s_robotN_infos robot_infos): Robot(robot_infos.m_x, robot_infos.m_y),
                                        m_angle(robot_infos.m_a),
                                        m_coord_type(robot_infos.m_c_n),
                                        m_k_update_panne(robot_infos.m_k_update_panne)
{

}

Robot_N::~Robot_N()
{
    //dtor
}
