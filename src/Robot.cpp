#include "Robot.h"

//constructeurs
Robot::Robot()
{
    //ctor
}
Robot::Robot(double x, double y): m_pos_x(x), m_pos_y(y)
{

}
//destructeur
Robot::~Robot()
{
    //dtor
}

//méthodes
void Robot::set_pos(double x, double y)
{

}

/**REPARATEURS**/

Robot_R::Robot_R()
{
    //ctor
}

Robot_R::~Robot_R()
{
    //dtor
}

Robot_N::Robot_N()
{
    //ctor
}

/**NEUTRALISEUR**/
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
