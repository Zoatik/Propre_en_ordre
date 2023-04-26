/***************************************
/nom du fichier : Simulation.cpp
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/
#include "Simulation.h"
#include <iostream>


using namespace std;

//ctor-dtor
Simulation::Simulation()
{
    //ctor
}

Simulation::~Simulation()
{
    //dtor
}

///méthodes publiques
void Simulation::update()
{

}

///méthodes privées de génération
bool Simulation::generate(File file_infos)
{
    m_nbP = file_infos.get_nbP();

    /**checks et instanciation dans l'ordre de lecture**/
    if(!generate_particles(file_infos))//génération et checks particules
        return false;
    if(!generate_robotS(file_infos))//génération et check robot spatial
        return false;
    if(!generate_robotR(file_infos))//génération et check robots réparateurs
        return false;
    if(!generate_robotN(file_infos))//génération et check robots neutraliseurs
        return false;

    cout<<message::success();
    //exit(0);
    return true;
}
 
bool Simulation::generate_particles(File file_infos)
{
    for(unsigned int i(0); i < file_infos.get_particles_infos().size(); i++)
    {
        Particle part(file_infos.get_particles_infos()[i]);
        if(part.get_shape().m_size<d_particule_min)
        {
            cout<<message::particle_too_small(part.get_shape().m_center.m_x,
                                                   part.get_shape().m_center.m_y,
                                                   part.get_shape().m_size);
            //exit(EXIT_FAILURE);
            return false;
        }
        if (!check_position(part.get_shape(), dmax))//check position valide
        {
            cout<<message::particle_outside(part.get_shape().m_center.m_x,
                                      part.get_shape().m_center.m_y,
                                      part.get_shape().m_size);
            //exit(EXIT_FAILURE);
            return false;
        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition
        {
            if(collision(part.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                cout<<message::particle_superposition(
                                        part.get_shape().m_center.m_x,
                                        part.get_shape().m_center.m_y,
                                        m_particles_vect[j].get_shape().m_center.m_x,
                                        m_particles_vect[j].get_shape().m_center.m_y);
                //exit(EXIT_FAILURE);
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

    if(!check_position(m_robotS.get_shape(), dmax))//check position
    {
        cout<<message::spatial_robot_outside(m_robotS.get_shape().m_center.m_x,
                                                  m_robotS.get_shape().m_center.m_y);
        //exit(EXIT_FAILURE);
        return false;
    }
    for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition S-P
        {
            if(collision(m_robotS.get_shape(),m_particles_vect[j].get_shape(), true))
            {
                cout<<message::particle_robot_superposition(
                                        m_particles_vect[j].get_shape().m_center.m_x,
                                        m_particles_vect[j].get_shape().m_center.m_y,
                                        m_particles_vect[j].get_shape().m_size,
                                        m_robotS.get_shape().m_center.m_x,
                                        m_robotS.get_shape().m_center.m_y,
                                        m_robotS.get_shape().m_radius);
                //exit(EXIT_FAILURE);
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
                cout<<message::repairers_superposition(
                                            curr_robotR.get_shape().m_center.m_x,
                                            curr_robotR.get_shape().m_center.m_y,
                                            m_robotR_vect[j].get_shape().m_center.m_x,
                                            m_robotR_vect[j].get_shape().m_center.m_y);
                //exit(EXIT_FAILURE);
                return false;
            }
        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition R-P
        {
            if(collision(curr_robotR.get_shape(),m_particles_vect[j].get_shape(),true))
            {
                cout<<message::particle_robot_superposition(
                                        m_particles_vect[j].get_shape().m_center.m_x,
                                        m_particles_vect[j].get_shape().m_center.m_y,
                                        m_particles_vect[j].get_shape().m_size,
                                        curr_robotR.get_shape().m_center.m_x,
                                        curr_robotR.get_shape().m_center.m_y,
                                        curr_robotR.get_shape().m_radius);
                //exit(EXIT_FAILURE);
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
        if(curr_robotN.get_k_update_panne()>m_robotS.get_nb_update())
        {
            show_invalid_k_update(curr_robotN);
            //exit(EXIT_FAILURE);
            return false;
        }
        for(unsigned int j(0); j<m_robotN_vect.size(); j++)//check superposition N-N
        {
            if(collision(curr_robotN.get_shape(),m_robotN_vect[j].get_shape(), true))
            {
                show_neutralizers_superposition(curr_robotN, j);
                //exit(EXIT_FAILURE);
                return false;
            }
        }
        for(unsigned int j(0); j<m_robotR_vect.size(); j++)//check superposition R-N
        {
            if(collision(curr_robotN.get_shape(),m_robotR_vect[j].get_shape(), true))
            {
                show_repairer_neutralizer_superposition(curr_robotN, j);
                //exit(EXIT_FAILURE);
                return false;
            }
        }
        for(unsigned int j(0); j<m_particles_vect.size(); j++)//check superposition N-P
        {
            if(collision(curr_robotN.get_shape(),m_particles_vect[j].get_shape(),true))
            {
                show_particle_robot_superposition(curr_robotN, j);
                //exit(EXIT_FAILURE);
                return false;
            }
        }
        m_robotN_vect.push_back(curr_robotN);
    }
    return true;
}

///méthodes privées d'affichage de messages d'erreurs
///(permet d'alléger "generate_RobotN")
void Simulation::show_invalid_k_update(Robot_N curr_robotN)
{
    cout<<message::invalid_k_update(
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y,
                curr_robotN.get_k_update_panne(),
                m_robotS.get_nb_update());
}
void Simulation::show_neutralizers_superposition(Robot_N curr_robotN, int j)
{
    cout<<message::neutralizers_superposition(
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y,
                m_robotN_vect[j].get_shape().m_center.m_x,
                m_robotN_vect[j].get_shape().m_center.m_y);
}
void Simulation::show_repairer_neutralizer_superposition(Robot_N curr_robotN, int j)
{
    cout<<message::repairer_neutralizer_superposition(
                m_robotR_vect[j].get_shape().m_center.m_x,
                m_robotR_vect[j].get_shape().m_center.m_y,
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y);
}
void Simulation::show_particle_robot_superposition(Robot_N curr_robotN, int j)
{
    cout<<message::particle_robot_superposition(
                m_particles_vect[j].get_shape().m_center.m_x,
                m_particles_vect[j].get_shape().m_center.m_y,
                m_particles_vect[j].get_shape().m_size,
                curr_robotN.get_shape().m_center.m_x,
                curr_robotN.get_shape().m_center.m_y,
                curr_robotN.get_shape().m_radius);
}

Robot_S Simulation::get_robotS()
{
    return m_robotS;
}
vector<Robot_N> Simulation::get_robotN_vect()
{
    return m_robotN_vect;
}
vector<Robot_R> Simulation::get_robotR_vect()
{
    return m_robotR_vect;
}
vector<Particle> Simulation::get_particles_vect()
{
    return m_particles_vect;
}

void Simulation::next_step()
{
    m_nbP += 1;
}
