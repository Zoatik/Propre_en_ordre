/************|HEADER|*************
* AUTHORS: - Hall Axel (30%)     *
*          - Michel Lucas (70%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 3.4                   *
* FILE: Particle.cc              *
*********************************/

#include "Particle.h"


/**PARTICULES**/
Particle::Particle()
{
    //default ctor
}

Particle::Particle(double x, double y, double size)
{
    m_square.m_center.m_x = x;
    m_square.m_center.m_y = y;
    m_square.m_size = size;
    m_risk_zone.m_center.m_x = x;
    m_risk_zone.m_center.m_y = y;
    m_risk_zone.m_size = size*risk_factor;
}

Particle::Particle(square s)
{
    m_square.m_center = s.m_center;
    m_square.m_size = s.m_size;
    m_risk_zone.m_center = s.m_center;
    m_risk_zone.m_size = s.m_size*risk_factor;
}

Particle::~Particle()
{
    //dtor
}

void Particle::set_particle(square s)
{
    m_square = s;
}

void Particle::set_is_target(bool is_target)
{
    m_is_target = is_target;
}

void Particle::draw()
{
    double thickness(0.3);
    draw_square(m_square.m_center, m_square.m_size, thickness, true, red, grey);
}

//méthodes
square Particle::get_shape() const
{
    return m_square;
}

square Particle::get_risk_zone() const
{
    return m_risk_zone;
}

bool Particle::get_is_target()
{
    return m_is_target;
}

bool Particle::separate(std::vector<std::unique_ptr<Particle>> &list)
{
    if(m_square.m_size/2-2*epsil_zero>d_particule_min)
    {   
        double x = m_square.m_center.m_x;
        double y = m_square.m_center.m_y;
        double delta_size = m_square.m_size/4;
        Particle new1(x-delta_size, y-delta_size, m_square.m_size/2-2*epsil_zero);
        Particle new2(x+delta_size, y-delta_size, m_square.m_size/2-2*epsil_zero);
        Particle new3(x+delta_size, y+delta_size, m_square.m_size/2-2*epsil_zero);
        Particle new4(x-delta_size, y+delta_size, m_square.m_size/2-2*epsil_zero);
        list.push_back(std::make_unique<Particle>(new1));
        list.push_back(std::make_unique<Particle>(new2));
        list.push_back(std::make_unique<Particle>(new3));
        list.push_back(std::make_unique<Particle>(new4));
        return 1;
    }
    return 0;
}
