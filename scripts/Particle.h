#ifndef PARTICLE_H
#define PARTICLE_H
/***************************************
/nom du fichier : Particle.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

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
