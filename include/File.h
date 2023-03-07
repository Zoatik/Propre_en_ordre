#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct s_robotS_infos
{
    s_robotS_infos(){}
    s_robotS_infos(double x, double y, int nb_update, int nbNr, int nbNs,
                   int nbNd, int nbRr, int nbRs):
                   m_x(x), m_y(y), m_nb_update(nb_update), m_nbNr(nbNr), m_nbNs(nbNs),
                   m_nbNd(nbNd), m_nbRr(nbRr), m_nbRs(nbRs){}

    double m_x;
    double m_y;
    int m_nb_update;
    int m_nbNr;
    int m_nbNs;
    int m_nbNd;
    int m_nbRr;
    int m_nbRs;
};

struct s_robotN_infos
{
    s_robotN_infos(double x, double y, double a, int c_n, bool panne, int k_update_panne):
                    m_x(x), m_y(y), m_a(a), m_c_n(c_n), m_panne(panne), m_k_update_panne(k_update_panne){}
    double m_x;
    double m_y;
    double m_a;
    int m_c_n;
    bool m_panne;
    int m_k_update_panne;
};

struct s_robotR_infos
{
    //s_robotR_infos(){}
    s_robotR_infos(double x,double y):m_x(x), m_y(y){}
    double m_x;
    double m_y;
};

struct s_particle_infos
{
    s_particle_infos(){}
    s_particle_infos(double x,double y,double d):m_x(x),m_y(y),m_d(d){}
    double m_x;
    double m_y;
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
        bool read_file(std::string file_path);

    protected:

    private:
        s_robotS_infos s_robotS;
        std::vector<s_robotN_infos> s_robotN_vect;
        std::vector<s_robotR_infos> s_robotR_vect;
        std::vector<s_particle_infos> s_particle_vect;
        ///DEBUG
        void show_infos();



};





#endif // FILE_H
