#ifndef SIMULATION_H
#define SIMULATION_H
#include "Robot.h"
#include "Particle.h"

class Simulation
{
    public:
        Simulation();
        void update();
        void generate(File file_infos);
    protected:
    private:
        int m_nbP;
        Robot m_robotS;
        std::vector<Robot_N> m_robotN_vect;
        std::vector<Robot_R> m_robotR_vect;
        std::vector<Particle> m_particles_vect;
};

#endif // SIMULATION_H
