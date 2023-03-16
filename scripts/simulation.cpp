#include "simulation.h"
#include <iostream>

Simulation::Simulation()
{
    //ctor
}

void Simulation::update()
{

}

bool Simulation::generate(File file_infos)
{
    m_nbP = file_infos.get_nbP();
    //file_infos.show_infos();
    /**checks et instanciation dans l'ordre de lecture**/
    if(!generate_particles(file_infos))//génération et checks particules
        return false;
    if(!generate_robotS(file_infos))//génération et check robot spatial
        return false;
    if(!generate_robotR(file_infos))//génération et check robots réparateurs
        return false;
    if(!generate_robotN(file_infos))//génération et check robots neutraliseurs
        return false;

    //checks robots réparateurs
    std::cout<<message::success();
    return true;
}

bool Simulation::generate_particles(File file_infos)
{
    for(unsigned int i(0); i < file_infos.get_particles_infos().size(); i++)
    {

        Particle part(file_infos.get_particles_infos()[i]);
        if(part.get_shape().m_size<d_particule_min)
        {
            std::cout<<message::particle_too_small(part.get_shape().m_center.m_x,
                                                   part.get_shape().m_center.m_y,
                                                   part.get_shape().m_size);
            return false;
        }
        if (!check_position(part.get_shape()))//check position valide
        {
            std::cout<<message::particle_outside(part.get_shape().m_center.m_x,
                                      part.get_shape().m_center.m_y,
                                      part.get_shape().m_size);
            return false;
        }
        if (part.get_shape().m_size < d_particule_min)//check taille min
        {
            message::particle_too_small(part.get_shape().m_center.m_x,
                                        part.get_shape().m_center.m_y,
                                        part.get_shape().m_size);
            return false;
        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition
        {
            if(collision(part.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                std::cout<<message::particle_superposition(part.get_shape().m_center.m_x,
                                                part.get_shape().m_center.m_y,
                                                m_particles_vect[j].get_shape().m_center.m_x,
                                                m_particles_vect[j].get_shape().m_center.m_y);
                return false;
            }
        }
        m_particles_vect.push_back(part);
    }
    return true;
}

bool Simulation::generate_robotS(File file_infos)
{
    m_robotS = Robot_S(file_infos.get_robotS_infos());

    if(!check_position(m_robotS.get_shape()))//check position
    {
        std::cout<<message::spatial_robot_outside(m_robotS.get_shape().m_center.m_x,
                                                  m_robotS.get_shape().m_center.m_y);
        return false;
    }
    for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition S-P
        {
            if(collision(m_robotS.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                std::cout<<message::particle_robot_superposition(m_particles_vect[j].get_shape().m_center.m_x,
                                                m_particles_vect[j].get_shape().m_center.m_y,
                                                m_particles_vect[j].get_shape().m_size,
                                                m_robotS.get_shape().m_center.m_x,
                                                m_robotS.get_shape().m_center.m_y,
                                                m_robotS.get_shape().m_radius);
                return false;
            }

        }
    return true;
}

bool Simulation::generate_robotR(File file_infos)
{
    for(unsigned int i(0); i<file_infos.get_robotR_infos().size(); i++)
    {
        Robot_R curr_robotR(file_infos.get_robotR_infos()[i]);
        for(unsigned int j(0); j<m_robotR_vect.size(); j++)//check superposition
        {
            if(collision(curr_robotR.get_shape(),m_robotR_vect[j].get_shape(), true))
            {
                std::cout<<message::repairers_superposition(curr_robotR.get_shape().m_center.m_x,
                                                curr_robotR.get_shape().m_center.m_y,
                                                m_robotR_vect[j].get_shape().m_center.m_x,
                                                m_robotR_vect[j].get_shape().m_center.m_y);
                return false;
            }

        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition R-P
        {
            if(collision(curr_robotR.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                std::cout<<message::particle_robot_superposition(m_particles_vect[j].get_shape().m_center.m_x,
                                                m_particles_vect[j].get_shape().m_center.m_y,
                                                m_particles_vect[j].get_shape().m_size,
                                                curr_robotR.get_shape().m_center.m_x,
                                                curr_robotR.get_shape().m_center.m_y,
                                                curr_robotR.get_shape().m_radius);
                return false;
            }

        }
        m_robotR_vect.push_back(curr_robotR);
    }
    return true;
}

bool Simulation::generate_robotN(File file_infos)
{
    for(unsigned int i(0); i<file_infos.get_robotN_infos().size(); i++)
    {
        Robot_N curr_robotN(file_infos.get_robotN_infos()[i]);
        //std::cout<<curr_robotN.get_k_update_panne()<<">?"<<m_robotS.get_nb_update()<<std::endl;
        if(curr_robotN.get_k_update_panne()>m_robotS.get_nb_update())
        {
            std::cout<<message::invalid_k_update(curr_robotN.get_shape().m_center.m_x,
                                                 curr_robotN.get_shape().m_center.m_y,
                                                 curr_robotN.get_k_update_panne(),
                                                 m_robotS.get_nb_update());
            return false;
        }
        for(unsigned int j(0); j<m_robotN_vect.size(); j++)//check superposition
        {
            if(collision(curr_robotN.get_shape(),m_robotN_vect[j].get_shape(), true))
            {
                std::cout<<message::neutralizers_superposition(curr_robotN.get_shape().m_center.m_x,
                                                curr_robotN.get_shape().m_center.m_y,
                                                m_robotN_vect[j].get_shape().m_center.m_x,
                                                m_robotN_vect[j].get_shape().m_center.m_y);
                return false;
            }
        }
        for(unsigned int j(0); j<m_robotR_vect.size(); j++)//check superposition R-N
        {
            if(collision(curr_robotN.get_shape(),m_robotR_vect[j].get_shape(), true))
            {
                std::cout<<message::repairer_neutralizer_superposition(m_robotR_vect[j].get_shape().m_center.m_x,
                                                                       m_robotR_vect[j].get_shape().m_center.m_y,
                                                                       curr_robotN.get_shape().m_center.m_x,
                                                                       curr_robotN.get_shape().m_center.m_y);
                return false;
            }
        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition N-P
        {
            if(collision(curr_robotN.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                std::cout<<message::particle_robot_superposition(m_particles_vect[j].get_shape().m_center.m_x,
                                                m_particles_vect[j].get_shape().m_center.m_y,
                                                m_particles_vect[j].get_shape().m_size,
                                                curr_robotN.get_shape().m_center.m_x,
                                                curr_robotN.get_shape().m_center.m_y,
                                                curr_robotN.get_shape().m_radius);
                return false;
            }
        }
        m_robotN_vect.push_back(curr_robotN);
    }
    return true;
}

