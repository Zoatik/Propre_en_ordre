#ifndef SIMULATION_H
#define SIMULATION_H
#include "Robot.h"
#include "Particle.h"

class Simulation
{
    public:
        void update();
        void generate(int nbP, s_robotS_infos robotS_infos, 
                                std::vector<s_robotN_infos> robotN_infos_vect, 
                                std::vector<s_robotR_infos> robotR_infos_vect, 
                                std::vector<s_particle_infos> particles_infos_vect);
    protected:
    private:
        int m_nbP;
        Robot m_robotS;
        std::vector<Robot_N> m_robotN_vect;
        std::vector<Robot_R> m_robotR_vect;
        std::vector<Particle> m_particles_vect;
};

#endif // SIMULATION_H