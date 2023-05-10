/************|HEADER|*************
* AUTHORS: - Hall Axel (60%)     *
*          - Michel Lucas (40%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: Robot.cc                 *
*********************************/

#include <math.h>
#include <iostream> ///DEBUG

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
                                        m_nbRs(nbRs),
                                        m_nbNp(0)
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

void Robot_S::draw()
{
    double thickness(1.0);
    draw_circle(m_circle.m_center, m_circle.m_radius, thickness, false, cyan, white);
    gtkmm_point(m_circle.m_center.m_x, m_circle.m_center.m_y, 1, cyan);
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

bool Robot_R::move_to_target()
{
    if(m_target == nullptr)
        return false;
    
    return true;
}

void Robot_R::set(s_2d pos)
{
    m_circle.m_center = pos;
    m_circle.m_radius = r_reparateur;
}

void Robot_R::set_target(Robot_N& target)
{
    m_target = &target;
}

void Robot_R::draw()
{
    double thickness(1.0);
    draw_circle(m_circle.m_center, m_circle.m_radius, thickness, true, black, green);
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

bool Robot_N::final_alignment(double target_orientation)
{
    if(target_orientation == M_PI/4 || target_orientation == 3*M_PI/4 
        || target_orientation == 5*M_PI/4 || target_orientation == 7*M_PI/4)
    {//cas où le robot se situerait pile sur un des coins
        m_in_collision = false;
        return false;
    }
    double a = vrot_max*delta_t;
    if(target_orientation>7*M_PI/4 || target_orientation<M_PI/4) 
    {// cas spécial : l'angle entre -PI/4 et PI/4 n'est pas "continu"
        if(m_angle>2*M_PI-epsil_alignement || m_angle<epsil_alignement)
            return destroy_target();
        if(2*M_PI-m_angle<a || m_angle<a)
        {
            rotate(-m_angle);
            return destroy_target();
        }
        rotate(a);
        return true;
    }
    for(int i(1);i<4;i++)//autres cas
    {   
        if(target_orientation>-M_PI/4+M_PI/2*i && target_orientation<M_PI/4+M_PI/2*i)
        {
            if(abs(m_angle-M_PI/2*i)>epsil_alignement)
            {
                if(abs(m_angle-M_PI/2*i)<a)
                {
                    rotate(m_angle - M_PI/2*i);
                    return destroy_target();
                }
                rotate(a);
                return true;
            }else
                return destroy_target();
        }
    }
    return true;
}

bool Robot_N::destroy_target()
{
    m_in_collision = false;
    return false;
}

void Robot_N::rotate(double a)
{
    m_angle += a;
    if(m_angle>2*M_PI)
    {
        m_angle = m_angle-2*M_PI;
    }
}

void Robot_N::translate()
{
    s_2d old_pose = m_circle.m_center;
    m_circle.m_center = m_circle.m_center+(vtran_max*delta_t)*
                                s_2d(cos(m_angle),sin(m_angle));

    if(collision(m_circle,m_target->get_shape(),false)){
        m_in_collision = true;
        m_circle.m_center = old_pose;
    }
    
}

std::string Robot_N::get_type()
{
    return m_type;
}
/*Imprécis. p.ex aux frames 247,300, rotate pour se réajuster (pour t00)*/
bool Robot_N::move_to_target()
{
    if(m_target == nullptr)
        return false;
    s_2d seg = m_target->get_shape().m_center - m_circle.m_center; //segment entre le robot et la target
    double target_orientation = atan2(seg.m_y,seg.m_x);
    if (m_coord_type == 0)//1er type mvt
    {   
        if(!m_in_collision){
            double a = vrot_max*delta_t;
            if(abs(m_angle-target_orientation)>epsil_alignement)
            {
                if(abs(m_angle-target_orientation)<a)
                {
                    a = m_angle - target_orientation;  
                    std::cout<<"ok : "<<target_orientation<<std::endl;
                } 
                rotate(a);
                std::cout<<"angle "<<m_angle<<std::endl;
            }
            else
                translate();
        }else{
            return final_alignment(target_orientation);
        }
    }

    return true;
}

void Robot_N::set(s_2d pos, double angle, int coord_type,
                  bool panne, int k_update_panne)
{
    m_circle.m_center = pos;
    m_circle.m_radius = r_neutraliseur;
    m_angle = angle;
    m_coord_type = coord_type;
    m_panne = panne;
    m_k_update_panne = k_update_panne;
}

void Robot_N::set_target(Particle& target)
{
    m_target = &target;
}

void Robot_N::set_panne(bool panne)
{
    m_panne = panne;
}

void Robot_N::draw()
{
    s_2d center(m_circle.m_center.m_x,
                m_circle.m_center.m_y);
    s_2d end(center.m_x+cos(m_angle)*m_circle.m_radius,
            center.m_y+sin(m_angle)*m_circle.m_radius);
    double thickness(1.0);
    if(m_panne){
        draw_circle(center, m_circle.m_radius, thickness, false, orange, white);
    }else if(m_in_collision){
        draw_circle(center, m_circle.m_radius, thickness, false, purple, white);
    }else{
        draw_circle(center, m_circle.m_radius, thickness, false, black, white);
    }
    
    draw_line(center, end, thickness, green);
    gtkmm_point(center.m_x, center.m_y, 1, black);
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

Particle* Robot_N::get_target()
{
    return m_target;
}
