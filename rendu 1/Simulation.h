#ifndef SIMULATION_H
#define SIMULATION_H
/***************************************
/nom du fichier : Simulation.h
/auteurs        : - Axel Hall - 346228
/		  		  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include "Robot.h"
#include "Particle.h"
#include "message.h"



class Simulation
{
    public:
        //ctor-dtor
        Simulation();
        virtual ~Simulation();

        //méthodes
        void update();
        bool generate(File file_infos);
        Robot_S get_robotS();
        std::vector<Robot_N> get_robotN_vect();
        std::vector<Robot_R> get_robotR_vect();
        std::vector<Particle> get_particles_vect();
        

    private:
        //checks et générations des objets
        bool generate_particles(File file_infos);
        bool generate_robotS(File file_infos);
        bool generate_robotR(File file_infos);
        bool generate_robotN(File file_infos);
        //affichage des messages d'erreurs
        void show_invalid_k_update(Robot_N curr_robotN);
        void show_neutralizers_superposition(Robot_N curr_robotN, int j);
        void show_repairer_neutralizer_superposition(Robot_N curr_robotN, int j);
        void show_particle_robot_superposition(Robot_N curr_robotN, int j);

        //attributs
        int m_nbP;
        Robot_S m_robotS;
        std::vector<Robot_N> m_robotN_vect;
        std::vector<Robot_R> m_robotR_vect;
        std::vector<Particle> m_particles_vect;
};

#endif // SIMULATION_H
