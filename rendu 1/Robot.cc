/***************************************
/nom du fichier : Robot.cpp
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include "Robot.h"


//constructeurs
Robot::Robot()
{
    //default ctor
}
Robot::Robot(circle cercle): m_circle(cercle)
{
	//ctor
}

//destructeur
Robot::~Robot()
{
    //dtor
}

//méthodes
void Robot::set_pos(s_2d pos)
{
	m_circle.m_center = pos;
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

Robot_S::Robot_S(s_robotS_infos infos): Robot(circle(infos.m_pos, r_spatial)),
										m_nbUpdate(infos.m_nb_update),
                                        m_nbNr(infos.m_nbNr),
                                        m_nbNs(infos.m_nbNs),
                                        m_nbNd(infos.m_nbNd),
                                        m_nbRr(infos.m_nbRr),
                                        m_nbRs(infos.m_nbRs)
{
   //ctor
}

Robot_S::~Robot_S()
{
    //dtor
}

//méthodes
int Robot_S::get_nb_update()
{
    return m_nbUpdate;
}

/**REPARATEURS**/
Robot_R::Robot_R()
{
    //default ctor
}

Robot_R::Robot_R(s_robotR_infos infos):Robot(circle(infos.m_pos, r_reparateur))
{
    //ctor
}

Robot_R::~Robot_R()
{
    //dtor
}

/**NEUTRALISEURS**/
Robot_N::Robot_N()
{
    //default ctor
}

Robot_N::Robot_N(s_robotN_infos infos): Robot(circle(infos.m_pos, r_neutraliseur)),
										m_angle(infos.m_a),
                                        m_coord_type(infos.m_c_n),
                                        m_k_update_panne(infos.m_k_update_panne)
{
    //ctor
}

Robot_N::~Robot_N()
{
    //dtor
}

//méthodes
int Robot_N::get_k_update_panne()
{
    return m_k_update_panne;
}

double Robot_N::get_angle()
{
    return m_angle;
}
