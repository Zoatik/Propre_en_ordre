#ifndef ROBOT_H
#define ROBOT_H
/***************************************
/nom du fichier : Robot.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include "File.h"



class Robot
{
    public:
        //ctor-dtor
        Robot();
        Robot(circle cercle);
        virtual ~Robot();

        //méthodes
        void set_pos(s_2d pos);
        circle get_shape();//retourne le struct circle du robot

    protected:
        circle m_circle;
};

/** ROBOT SPATIAL**/
class Robot_S : public Robot
{
    public:
        //ctor-dtor
        Robot_S();
        Robot_S(s_robotS_infos);
        virtual ~Robot_S();

        //méthodes
        int get_nb_update();

    private:
        int m_nbUpdate;
        int m_nbNr;
        int m_nbNs;
        int m_nbNd;
        int m_nbRr;
        int m_nbRs;
};

/**REPARATEURS**/
class Robot_R : public Robot
{
    public:
        //ctor-dtor
        Robot_R();
        Robot_R(s_robotR_infos infos);
        virtual ~Robot_R();
};

/**NEUTRALISEUR**/
class Robot_N : public Robot
{
    public:
        //ctor-dtor
        Robot_N();
        Robot_N(s_robotN_infos infos);
        virtual ~Robot_N();

        //méthodes
        int get_k_update_panne();

    private:
        double m_angle;
        int m_coord_type;
        int m_k_update_panne;
};



#endif // ROBOT_H
