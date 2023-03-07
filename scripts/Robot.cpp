#include "Robot.h"
#include "shape.h"

//constructeurs
Robot::Robot()
{
    //ctor
}
Robot::Robot(s_2d pos): m_pos(pos)
{

}
//destructeur
Robot::~Robot()
{
    //dtor
}

//méthodes
void Robot::set_pos(s_2d pos)
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

/**NEUTRALISEUR**/
Robot_N::Robot_N()
{
    //ctor
}

/*Robot_N::Robot_N(s_robotN_infos robot_infos): Robot(robot_infos.m_pos),
                                        m_angle(robot_infos.m_a),
                                        m_coord_type(robot_infos.m_c_n),
                                        m_k_update_panne(robot_infos.m_k_update_panne)
{

}*/

Robot_N::~Robot_N()
{
    //dtor
}
