#ifndef ROBOT_H
#define ROBOT_H

#include "File.h"


class Robot
{
    public:
        Robot();
        virtual ~Robot();

        void set_pos(s_2d pos);
        circle get_shape();

    protected:
        circle m_circle;
    private:


};

/** ROBOT SPATIAL**/
class Robot_S : public Robot
{
    public:
        Robot_S();
        Robot_S(s_robotS_infos);
        virtual ~Robot_S();
        int get_nb_update();

    protected:

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
        Robot_R();
        Robot_R(s_robotR_infos infos);
        virtual ~Robot_R();

    protected:

    private:
};



/**NEUTRALISEUR**/
class Robot_N : public Robot
{
    public:
        Robot_N();
        Robot_N(s_robotN_infos infos);
        int get_k_update_panne();
        virtual ~Robot_N();

    protected:

    private:
        double m_angle;
        int m_coord_type;
        int m_k_update_panne;

};



#endif // ROBOT_H
