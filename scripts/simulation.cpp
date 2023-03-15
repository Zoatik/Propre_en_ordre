#include "simulation.h"
#include <iostream>

Simulation::Simulation()
{
    //ctor
}

void Simulation::update()
{

}

void Simulation::generate(File file_infos)
{
    m_nbP = file_infos.get_nbP();
    Robot_S m_robot_S = Robot_S(file_infos.get_robotS_infos());
    if(check_position(m_robot_S.m_circle))
    {
        std::cout<< "Dans la carte";
    }

}

