/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 3.4                   *
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
        void set_is_target(bool is_target);
        square get_shape() const;
        square get_risk_zone() const;
        bool get_is_target();
        bool separate(std::vector<std::unique_ptr<Particle>> &list);

    private:
        square m_square;
        square m_risk_zone;
        bool m_is_target = false;
};

#endif // PARTICLE_H
