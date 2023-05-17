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

bool Robot_N::get_in_collision()
{
    return m_in_collision;
}

int Robot_N::get_c_n()
{
    return m_coord_type;
}

bool Robot_N::final_alignment()
{
    s_2d inter_target;
    double targ_size = m_target->get_shape().m_size/2;
    double targ_x = m_target->get_shape().m_center.m_x;
    double targ_y = m_target->get_shape().m_center.m_y;
    double x = m_circle.m_center.m_x;
    double y = m_circle.m_center.m_y;
    if(x < targ_x + targ_size && x > targ_x - targ_size)
        return move_to_point(s_2d(x,targ_y));
    else if(y < targ_y + targ_size && y > targ_y - targ_size)
        return move_to_point(s_2d(targ_x,y));
    else
    {
        if(x < targ_x && y < targ_y)
                return move_to_point(s_2d(targ_x - targ_size-m_circle.m_radius-epsil_zero,
                                    targ_y - targ_size));
        else if(x < targ_x && y > targ_y)
            return move_to_point(s_2d(targ_x - targ_size-m_circle.m_radius-epsil_zero,
                                targ_y + targ_size));
        else if(x > targ_x && y < targ_y)
            return move_to_point(s_2d(targ_x + targ_size+m_circle.m_radius+epsil_zero,
                                targ_y - targ_size));
        else if(x > targ_x && y > targ_y)
            return move_to_point(s_2d(targ_x + targ_size+m_circle.m_radius+epsil_zero,
                                targ_y + targ_size));
    }
}

bool Robot_N::alignment(s_2d point)
{
    s_2d seg = point - m_circle.m_center;//segment entre point et robot
    double point_orientation = atan2(seg.m_y,seg.m_x);
    if(point_orientation < 0)
        point_orientation = 2*M_PI+point_orientation;
    double a = vrot_max*delta_t;
    if(m_angle - point_orientation > 0)
    {
        if(m_angle - point_orientation < point_orientation + 2*M_PI-m_angle)
            a*= -1;
    }
    else
    {
        if(m_angle + 2*M_PI-point_orientation < point_orientation - m_angle)
            a*= -1;
    }
    if(abs(m_angle-point_orientation)>epsil_alignement)
    {
        if(abs(m_angle-point_orientation)<a)
        {
            a = m_angle - point_orientation;  
        } 
        rotate(a);
        return false;
    }
    else
        return true;
}

bool Robot_N::destroy_target()
{
    m_in_collision = false;
    return true;
}

void Robot_N::rotate(double a)
{
    m_angle += a;
    if(m_angle>2*M_PI)
        m_angle = m_angle-2*M_PI;
    if(m_angle < 0)
        m_angle = 2*M_PI+m_angle;
}

void Robot_N::translate()
{
    m_circle.m_center = m_circle.m_center+(vtran_max*delta_t)*
                                s_2d(cos(m_angle),sin(m_angle));

}

std::string Robot_N::get_type()
{
    return m_type;
}

bool Robot_N::move_to_target()
{
    if(m_target == nullptr || m_panne == true)
        return false;
    double targ_size = m_target->get_shape().m_size/2;
    double targ_x = m_target->get_shape().m_center.m_x;
    double targ_y = m_target->get_shape().m_center.m_y;
    double x = m_circle.m_center.m_x;
    double y = m_circle.m_center.m_y;
    if (m_coord_type == 0)//1er type mvt
    {
        if(!m_in_collision)
        {
            if(alignment(m_target->get_shape().m_center))
                translate();
        }
        else
            return final_alignment();
    }
    if(m_coord_type == 1)//2ème type mvt
    {
        if(!m_in_collision)
        {    
            //std::cout<<"safe point : "<<m_inter_point.m_x<<" , "<<m_inter_point.m_y<<std::endl;
            if(collision(m_circle, m_target->get_risk_zone()))
                m_inter_point = find_safe_point(false);//check pas déjà zone à risque
            if(move_to_point(m_inter_point))
            {
                std::cout<<"arrivé en : "<<m_inter_point.m_x<<" , "<<m_inter_point.m_y<<std::endl;
                m_inter_point = find_safe_point(false);
                std::cout<<"nouvelle cible en : "<<m_inter_point.m_x<<" , "<<m_inter_point.m_y<<std::endl;
                std::cout<<m_in_collision<<std::endl;

            }
            else
                std::cout<<"en déplacement"<<std::endl;
        }
        else
            return final_alignment();
    }

    return false;
}

bool Robot_N::move_to_point(s_2d point)
{
    if(m_in_collision)
        return true;
    if(alignment(point))
    {
        std::cout<<"aligné"<<std::endl;
        if(m_circle.m_center.close_to(point, vtran_max*delta_t))
        {
            m_circle.m_center = point;
        }
        else
        {
            std::cout<<"avance"<<std::endl;
            m_circle.m_center = m_circle.m_center+(vtran_max*delta_t)*
                                s_2d(cos(m_angle),sin(m_angle));
        }
    }
    return m_circle.m_center == point;
}

s_2d Robot_N::find_safe_point(bool outside)
{
    s_2d seg = m_target->get_shape().m_center - m_circle.m_center;
    double targ_size = m_target->get_shape().m_size/2;
    double targ_x = m_target->get_shape().m_center.m_x;
    double targ_y = m_target->get_shape().m_center.m_y;
    double targ_risk_size = m_target->get_risk_zone().m_size/2;
    if(!outside)
        targ_risk_size = targ_size;
    double x = m_circle.m_center.m_x;
    double y = m_circle.m_center.m_y;
    if(x <= targ_x + targ_size && x >= targ_x - targ_size)
        return s_2d(x,targ_y);
    else if(y <= targ_y + targ_size && y >= targ_y - targ_size)
        return s_2d(targ_x,y);
    else
    {
        if(x <= targ_x && y <= targ_y)//bas gauche
        {
            if(abs(seg.m_x) < abs(seg.m_y))
                return s_2d(targ_x - targ_size,
                            targ_y - targ_risk_size-m_circle.m_radius-epsil_zero);
            else
                return s_2d(targ_x - targ_risk_size-m_circle.m_radius-epsil_zero,
                                    targ_y - targ_size);
        }
        else if(x <= targ_x && y >= targ_y)//haut gauche
        {
            if(abs(seg.m_x) < abs(seg.m_y))
                return s_2d(targ_x - targ_size,
                                targ_y + targ_risk_size+m_circle.m_radius+epsil_zero);
            else
                return s_2d(targ_x - targ_risk_size-m_circle.m_radius-epsil_zero,
                                targ_y + targ_size);
        }
        else if(x >= targ_x && y <= targ_y)//bas droite
        {
            if(abs(seg.m_x) < abs(seg.m_y))
                return s_2d(targ_x + targ_size,
                                targ_y-targ_risk_size-m_circle.m_radius-epsil_zero);
            else
                return s_2d(targ_x + targ_risk_size+m_circle.m_radius+epsil_zero,
                                targ_y - targ_size);
        }
        else//haut droite
        {
            if(abs(seg.m_x) < abs(seg.m_y))
            {
                return s_2d(targ_x + targ_size,
                                targ_y+targ_risk_size+m_circle.m_radius+epsil_zero);
            }
            else
                return s_2d(targ_x + targ_risk_size+m_circle.m_radius+epsil_zero,
                                targ_y + targ_size);
        }
    }
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

void Robot_N::set_target(Particle* target)
{
    target->set_is_target(true);
    if(m_target)
        m_target->set_is_target(false);
    m_target = target;
}

void Robot_N::delete_target()
{
    if(m_target)//on contrôle que pas déjà nullptr
    {
        m_target->set_is_target(false);
        m_target = nullptr;
        m_in_collision = false;
    }
}

void Robot_N::set_panne(bool panne)
{
    if(panne)
        delete_target();
    m_panne = panne;
}

void Robot_N::set_in_collision(bool in_collision)
{
    m_in_collision = in_collision;
}

void Robot_N::set_inter_point(s_2d safe_point)
{
    m_inter_point = safe_point;
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