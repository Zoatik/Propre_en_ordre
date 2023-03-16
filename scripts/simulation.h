#ifndef SIMULATION_H
#define SIMULATION_H
#include "Robot.h"
#include "Particle.h"
#include "message.h"

class Simulation
{
    public:
        Simulation();
        void update();
        bool generate(File file_infos);
    private:
        bool generate_particles(File file_infos);
        bool generate_robotS(File file_infos);
        bool generate_robotR(File file_infos);
        bool generate_robotN(File file_infos);
        int m_nbP;
        Robot_S m_robotS;
        std::vector<Robot_N> m_robotN_vect;
        std::vector<Robot_R> m_robotR_vect;
        std::vector<Particle> m_particles_vect;
};

#endif // SIMULATION_H
