/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: Simulation.h             *
*********************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <memory>
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
        void update_movement();//update tous les déplacements (robots N et R)
        void draw();
        void next_step();
        void clear();
        void remove_particle(Particle* ptr);
        void store_robot(Robot* ptr);
        void destroy_robot(Robot* ptr);
        void decide_deployment();
        bool can_deploy(std::string type);
        void deploy_new_robot(std::string type, s_2d dest);
        void assign_target(bool override = false);
        void assign_robotR_targets();

        //getter
        Robot_S& get_robotS();
        std::vector<std::unique_ptr<Particle>>& get_particles_vect();
        std::vector<std::unique_ptr<Robot>>& get_robots_ptr_vect();
        int get_nbP();
        int get_updates();
        int get_nb_N();
        int get_nb_R();

        //lecture de fichiers
        bool read_file(std::string file_path);//lit un fichier "test".txt
        bool write_file(std::string file_path);
        
    private:
        //lecture des fichiers
        bool sep_file_infos(std::vector<std::string> lines);//sépare les infos
        bool read_particles_prop(std::string spec, std::vector<std::string> lines,
                                 unsigned int& i);
        bool read_robotS_prop(std::vector<std::string> lines, unsigned int& i);
        bool read_robotR_prop(std::vector<std::string> lines, unsigned int& i);
        bool read_robotN_prop(std::vector<std::string> lines, unsigned int& i);
        //checks et générations des objets
        bool check_robot(std::unique_ptr<Robot>& robot);
        bool check_particles(Particle part);
        bool check_robotS(Robot_S robotS);
        bool check_robotR(Robot_R robotR);
        bool check_robotN(Robot_N robotN);
        void set_nbNp();
        //affichage des messages d'erreurs
        void show_invalid_k_update(Robot_N curr_robotN);
        void show_neutralizers_superposition(Robot_N curr_robotN, int j);
        void show_repairer_neutralizer_superposition(Robot_N curr_robotN, int j);
        void show_particle_robot_superposition(std::unique_ptr<Robot>& robot, int j);   
        //déplacement
        int find_nearest_robot(square s_part);//retourne l'index du robot
                                           //(-1 si aucun robot)
        std::vector<int> get_untargeted_parts_index();
        void tri_size(std::vector<std::unique_ptr<Particle>>& part_vect);
        void set_robots_state(Particle const &part);//mets en panne si risk_zone

        //attributs
        int m_nbP;
        std::vector<std::unique_ptr<Robot>> m_robots;
        std::vector<std::unique_ptr<Particle>> m_particles_vect;  
        
        // attributs désintégration particules
        std::bernoulli_distribution m_bernoulli;
};

#endif // SIMULATION_H
