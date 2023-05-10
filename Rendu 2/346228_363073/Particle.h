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
        void draw();
        void set_particle(square s);
        square get_shape() const;
        square get_risk_zone() const;
        bool separate(std::vector<Particle> &list, std::vector<Particle> &list2);

    private:
        square m_square;
        square m_risk_zone;
};

#endif // PARTICLE_H
