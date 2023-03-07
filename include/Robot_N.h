#ifndef ROBOT_N_H
#define ROBOT_N_H

#include <Robot.h>


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

#endif // ROBOT_N_H
