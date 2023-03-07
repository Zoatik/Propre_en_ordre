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



#endif // ROBOT_H
