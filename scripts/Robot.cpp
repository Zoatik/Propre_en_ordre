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

//m�thodes
void Robot::set_pos(s_2d pos)
{

}

/**ROBOT SPATIAL**/
Robot_S::Robot_S(s_robotS_infos infos): 
    m_nbUpdate(infos.m_nb_update), 
    m_nbNr(infos.m_nbNr), 
    m_nbNs(infos.m_nbNs),
    m_nbNd(infos.m_nbNd),
    m_nbRr(infos.m_nbRr), 
    m_nbRs(infos.m_nbRs)
{
    set_pos(infos.m_pos);
    m_circle.m_center = m_pos;
    m_circle.m_radius = r_spatial;
     //ctor
}

Robot_S::~Robot_S()
{
    //dtor
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
