#ifndef ROBOT_H
#define ROBOT_H

#include "File.h"


class Robot
{
    public:
        Robot();
        Robot(s_2d pos);
        virtual ~Robot();

        void set_pos(s_2d pos);
        void create(s_robotS_infos infos);
    protected:
        s_2d m_pos;
    private:


};

/**REPARATEURS**/
class Robot_R : public Robot
{
    public:
        Robot_R();
        virtual ~Robot_R();

    protected:

    private:
};



/**NEUTRALISEUR**/
class Robot_N : public Robot
{
    public:
        Robot_N();
        //Robot_N(s_robotN_infos robot_infos);
        virtual ~Robot_N();

    protected:

    private:
        double m_angle;
        int m_coord_type;
        int m_k_update_panne;

};



#endif // ROBOT_H
