/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: Robot.h                  *
*********************************/


#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include "constantes.h"


class Robot
{
    public:
        //ctor-dtor
        Robot();
        Robot(circle cercle);
        virtual ~Robot();

        //virtual
        virtual std::string get_type() = 0;
        //méthodes
        void set_pos(s_2d pos);
        circle get_shape();//retourne le struct circle du robot
        int test = 0;
        
    protected:
        circle m_circle;
};

/** ROBOT SPATIAL**/
class Robot_S : public Robot
{
    public:
        //ctor-dtor
        Robot_S();
        Robot_S(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                int nbNd, int nbRr, int nbRs);
        virtual ~Robot_S();

        //virtual
        virtual std::string get_type();

        //méthodes
        void set(s_2d pos, int nbUpdate, int nbNr, int nbNs,
                 int nbNd, int nbRr, int nbRs);
        void set_nbNp(int count);
        void draw(int xc, int yc, double ratio);
        int get_nb_update();
        int get_nbNr();
        int get_nbNs();
        int get_nbNd();
        int get_nbNp();
        int get_nbRr();
        int get_nbRs();
        void update();

    private:
        int m_nbUpdate;
        int m_nbNr;
        int m_nbNs;
        int m_nbNd;
        int m_nbRr;
        int m_nbRs;
        int m_nbNp;
        const std::string m_type = "S";
};

/**REPARATEURS**/
class Robot_R : public Robot
{
    public:
        //ctor-dtor
        Robot_R();
        Robot_R(s_2d pos);
        virtual ~Robot_R();
        //virtual
        virtual std::string get_type();
        //methods
        void set(s_2d pos);
        void draw(int xc, int yc, double ratio);

    private:
        const std::string m_type = "R";
};

/**NEUTRALISEUR**/
class Robot_N : public Robot
{
    public:
        //ctor-dtor
        Robot_N();
        Robot_N(s_2d pos, double angle, int coord_type, 
                bool panne, int k_update_panne);
        virtual ~Robot_N();

        //virtual
        virtual std::string get_type();

        //méthodes
        void set(s_2d pos, double angle, int coord_type,
                 bool panne, int k_update_panne);
        void draw(int xc, int yc, double ratio);
        int get_k_update_panne();
        double get_angle();
        bool get_panne();
        int get_c_n();

    private:
        double m_angle;
        int m_coord_type;
        bool m_panne;
        int m_k_update_panne;
        const std::string m_type = "N";
};



#endif // ROBOT_H
