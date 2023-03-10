#include "shape.h"
#include <math.h>

Circle::Circle(s_2d center, double radius)
{

}

Circle::~Circle()
{

}

Square::Square(s_2d center, double size)
{

}

Square::~Square()
{

}

bool circle_square_collision(s_2d circle_center, double r1, s_2d sqare_center, double d1)
{  
    s_2d vector(abs(circle_center.m_x-sqare_center.m_x)-d1/2, abs(circle_center.m_y-sqare_center.m_y)-d1/2);
    double L(norm(vector));
    if( abs(circle_center.m_x-sqare_center.m_x)<d1/2+r1+epsil_zero and
        abs(circle_center.m_y-sqare_center.m_y)<d1/2+r1+epsil_zero)
    {
        if( (abs(circle_center.m_x-sqare_center.m_x)>d1/2 and
            abs(circle_center.m_y-sqare_center.m_y)>d1/2) and
            L > r1+epsil_zero)
        {
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
}

bool circles_collision(s_2d center_1, double r1, s_2d center_2, double r2)
{
    if(distance(center_1, center_2)< (r1 + r2) + epsil_zero)
    {
        return 1;
    }
    return 0;
}

bool squares_collision(s_2d center_1, double d1, s_2d center_2, double d2)
{
    if( abs(center_1.m_x-center_2.m_x)< d1/2 + d2/2 + epsil_zero and 
        abs(center_1.m_y-center_2.m_y)< d1/2 + d2/2 + epsil_zero)
    {
        return 1;
    }
    return 0;
}

double distance(s_2d point_1, s_2d point_2)
{
    return pow(pow(point_1.m_x-point_2.m_x,2)+pow(point_1.m_y-point_2.m_x,2), 0.5);
}

double norm(s_2d point)
{
    return pow(pow(point.m_x,2)+pow(point.m_y,2), 0.5);
}