#ifndef PARTICLE_H
#define PARTICLE_H

#include "File.h"

class Particle
{
    public:
        Particle();
        Particle(s_particle_infos infos);
        square get_shape();
    private:
        square m_square;
};

#endif // PARTICLE_H
