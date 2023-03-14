#include "simulation.h"
#include <iostream>

void Simulation::update()
{

}

void Simulation::generate(int nbP, s_robotS_infos robotS_infos, 
                                std::vector<s_robotN_infos> robotN_infos_vect, 
                                std::vector<s_robotR_infos> robotR_infos_vect, 
                                std::vector<s_particle_infos> particles_infos_vect)
{
    
    m_nbP = nbP;
    Robot_S m_robot_S(robotS_infos);
    if(check_position(m_robot_S.m_circle))
    {
        std::cout<< "Dans la carte";
    }
       
}

