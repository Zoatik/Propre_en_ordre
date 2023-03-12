#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "constantes.h"

struct s_robotS_infos
{
    s_robotS_infos(){}
    s_robotS_infos(s_2d pos, int nb_update, int nbNr, int nbNs,
                   int nbNd, int nbRr, int nbRs):
                   m_pos(pos), m_nb_update(nb_update), m_nbNr(nbNr), m_nbNs(nbNs),
                   m_nbNd(nbNd), m_nbRr(nbRr), m_nbRs(nbRs){}

    s_2d m_pos;
    int m_nb_update;
    int m_nbNr;
    int m_nbNs;
    int m_nbNd;
    int m_nbRr;
    int m_nbRs;
};

struct s_robotN_infos
{
    s_robotN_infos(s_2d pos, double a, int c_n, bool panne, int k_update_panne):
                    m_pos(pos), m_a(a), m_c_n(c_n), m_panne(panne), m_k_update_panne(k_update_panne){}
    s_2d m_pos;
    double m_a;
    int m_c_n;
    bool m_panne;
    int m_k_update_panne;
};

struct s_robotR_infos
{
    //s_robotR_infos(){}
    s_robotR_infos(s_2d pos):m_pos(pos){}
    s_2d m_pos;
};

struct s_particle_infos
{
    s_particle_infos(){}
    s_particle_infos(s_2d pos, double d):m_pos(pos),m_d(d){}
    s_2d m_pos;
    double m_d;
};

struct s_sim_infos
{
    int m_nbP;

};

/**FILE's CLASS**/
class File
{
    public:
        File();
        virtual ~File();
        bool read_file(std::string file_path);//lit un fichier "test".txt

    protected:

    private:
        int m_nbP;
        s_robotS_infos m_robotS;
        std::vector<s_robotN_infos> m_robotN_vect;
        std::vector<s_robotR_infos> m_robotR_vect;
        std::vector<s_particle_infos> m_particle_vect;

        /*lecture et assignation des propriétes des particules/robots*/
        void sep_file_infos(std::vector<std::string> lines);
        void read_particles_prop(std::string spec, std::vector<std::string> lines, unsigned int& i);
        void read_robotS_prop(std::vector<std::string> lines, unsigned int& i);
        void read_robotR_prop(std::vector<std::string> lines, unsigned int& i);
        void read_robotN_prop(std::vector<std::string> lines, unsigned int& i);
        ///DEBUG
        void show_infos();



};





#endif // FILE_H
