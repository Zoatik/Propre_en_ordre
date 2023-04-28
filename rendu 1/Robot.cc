/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: Robot.cc                 *
*********************************/

#include<iostream> //debug


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

Robot_S::Robot_S(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                int nbNd, int nbRr, int nbRs): 
                                        Robot(circle(pos, r_spatial)),
										m_nbUpdate(nbUpdate),
                                        m_nbNr(nbNr),
                                        m_nbNs(nbNs),
                                        m_nbNd(nbNd),
                                        m_nbRr(nbRr),
                                        m_nbRs(nbRs)
{
   //ctor
}

Robot_S::~Robot_S()
{
    //dtor
}

std::string Robot_S::get_type()
{
    return m_type;
}

void Robot_S::set(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                  int nbNd, int nbRr, int nbRs)
{
    m_circle.m_center = pos;
    m_circle.m_radius = r_spatial;
    m_nbUpdate = nbUpdate;
    m_nbNr = nbNr;
    m_nbNs = nbNs;
    m_nbNd = nbNd;
    m_nbRr = nbRr;
    m_nbRs = nbRs;
}

void Robot_S::set_nbNp(int count)
{
    m_nbNp = count;
}

//méthodes
int Robot_S::get_nb_update()
{
    return m_nbUpdate;
}
void Robot_S::update()
{
    m_nbUpdate += 1;
}

int Robot_S::get_nbNr()
{
    return m_nbNr;
}

int Robot_S::get_nbNs()
{
    return m_nbNs;
}

int Robot_S::get_nbNd()
{
    return m_nbNd;
}

int Robot_S::get_nbNp()
{
    return m_nbNp;
}

int Robot_S::get_nbRr()
{
    return m_nbRr;
}

int Robot_S::get_nbRs()
{
    return m_nbRs;
}

/**REPARATEURS**/
Robot_R::Robot_R()
{
    //default ctor
}

Robot_R::Robot_R(s_2d pos):Robot(circle(pos, r_reparateur))
{
    //ctor
}

Robot_R::~Robot_R()
{
    //dtor
}

std::string Robot_R::get_type()
{
    return m_type;
}

void Robot_R::set(s_2d pos)
{
    m_circle.m_center = pos;
    m_circle.m_radius = r_reparateur;
}

/**NEUTRALISEURS**/
Robot_N::Robot_N()
{
    //default ctor
}

Robot_N::Robot_N(s_2d pos, double angle, int coord_type,
                 bool panne, int k_update_panne):
                                    Robot(circle(pos, r_neutraliseur)),
									m_angle(angle),
                                    m_coord_type(coord_type),
                                    m_panne(panne),
                                    m_k_update_panne(k_update_panne)
{
    //ctor
}

Robot_N::~Robot_N()
{
    //dtor
}

bool Robot_N::get_panne()
{
    return m_panne;
}

int Robot_N::get_c_n()
{
    return m_coord_type;
}

std::string Robot_N::get_type()
{
    return m_type;
}

void Robot_N::set(s_2d pos, double angle, int coord_type, bool panne, int k_update_panne)
{
    m_circle.m_center = pos;
    m_circle.m_radius = r_neutraliseur;
    m_angle = angle;
    m_coord_type = coord_type;
    m_panne = panne;
    m_k_update_panne = k_update_panne;
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
