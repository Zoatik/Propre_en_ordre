/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
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
}

Particle::Particle(square s)
{
    m_square.m_center = s.m_center;
    m_square.m_size = s.m_size;
}

Particle::~Particle()
{
    //dtor
}


void Particle::set_particle(square s)
{
    m_square = s;
}

void Particle::draw(int xc, int yc, double ratio)
{
    s_2d center(xc+m_square.m_center.m_x*ratio, yc-m_square.m_center.m_y*ratio);
    double size(m_square.m_size*ratio);
    double thickness(0.3*ratio);
    draw_square(center, size, thickness, true, red, grey);
}

//méthodes
square Particle::get_shape()
{
    return m_square;
}

bool Particle::separate(std::vector<Particle> &list)
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
        list.push_back(new1);
        list.push_back(new2);
        list.push_back(new3);
        list.push_back(new4);
        return 1;
    }
    return 0;
}
