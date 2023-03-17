#ifndef PARTICLE_H
#define PARTICLE_H

#include "File.h"

class Particle
{
    public:
        //ctor-dtor
        Particle();
        Particle(s_particle_infos infos);
        virtual ~Particle();

        //méthodes
        square get_shape();

    private:
        square m_square;
};

#endif // PARTICLE_H
