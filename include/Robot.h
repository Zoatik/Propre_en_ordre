#ifndef ROBOT_H
#define ROBOT_H

#include "File.h"


class Robot
{
    public:
        Robot();
        Robot(double x, double y);
        virtual ~Robot();

        void set_pos(double x, double y);

    protected:
        double m_pos_x;
        double m_pos_y;
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
        Robot_N(s_robotN_infos robot_infos);
        virtual ~Robot_N();

    protected:

    private:
        double m_angle;
        int m_coord_type;
        int m_k_update_panne;

};



#endif // ROBOT_H
