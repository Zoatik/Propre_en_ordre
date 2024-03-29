/***************************************
/nom du fichier : Particle.cpp
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include "Particle.h"


/**PARTICULES**/
Particle::Particle()
{
    //default ctor
}

Particle::Particle(s_particle_infos infos)
{
    m_square.m_center = infos.m_pos;
    m_square.m_size = infos.m_d;
}

Particle::~Particle()
{
    //dtor
}

//méthodes
square Particle::get_shape()
{
    return m_square;
}
