#include "Robot.h"
#include "shape.h"

//constructeurs
Robot::Robot()
{
    //ctor
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
circle Robot::get_shape()
{
    return m_circle;
}

/**ROBOT SPATIAL**/
Robot_S::Robot_S()
{
    //default ctor
}
Robot_S::Robot_S(s_robotS_infos infos): m_nbUpdate(infos.m_nb_update),
                                        m_nbNr(infos.m_nbNr),
                                        m_nbNs(infos.m_nbNs),
                                        m_nbNd(infos.m_nbNd),
                                        m_nbRr(infos.m_nbRr),
                                        m_nbRs(infos.m_nbRs)
{
    m_circle.m_center = infos.m_pos;
    m_circle.m_radius = r_spatial;
     //ctor
}

Robot_S::~Robot_S()
{
    //dtor
}
int Robot_S::get_nb_update()
{
    return m_nbUpdate;
}

/**REPARATEURS**/

Robot_R::Robot_R()
{
    //ctor
}
Robot_R::Robot_R(s_robotR_infos infos)
{
    m_circle.m_center = infos.m_pos;
    m_circle.m_radius = r_reparateur;
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

Robot_N::Robot_N(s_robotN_infos infos): m_angle(infos.m_a),
                                        m_coord_type(infos.m_c_n),
                                        m_k_update_panne(infos.m_k_update_panne)
{
    m_circle.m_center = infos.m_pos;
    m_circle.m_radius = r_neutraliseur;
}

Robot_N::~Robot_N()
{
    //dtor
}
int Robot_N::get_k_update_panne()
{
    return m_k_update_panne;
}
