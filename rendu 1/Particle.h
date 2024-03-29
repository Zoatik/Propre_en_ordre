/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: Particle.h               *
*********************************/


#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "constantes.h"

class Particle
{
    public:
        //ctor-dtor
        Particle();
        Particle(double x, double y, double size);
        Particle(square s);
        virtual ~Particle();

        //méthodes
        void draw(int xc, int yc, double ratio);
        void set_particle(square s);
        square get_shape();
        bool separate(std::vector<Particle> &list);

    private:
        square m_square;
};

#endif // PARTICLE_H
