#include "shape.h"


/**METHODES SUR LES POINTS/VECTEURS**/
double difference(s_2d point_1, s_2d point_2)
{
    return pow(pow(point_1.m_x-point_2.m_x,2)+pow(point_1.m_y-point_2.m_x,2), 0.5);
}

double norm(s_2d point)
{
    return pow(pow(point.m_x,2)+pow(point.m_y,2), 0.5);
}

bool check_position()
{
    return 0;
}

/**TESTS DE COLLISIONS**/
bool collision(circle c1, square s1)
{  
    s_2d vect_2d(abs(c1.m_center.m_x-s1.m_center.m_x)-s1.m_size/2, abs(c1.m_center.m_y-s1.m_center.m_y)-s1.m_size/2);
    double L(norm(vect_2d));
    if( abs(c1.m_center.m_x-s1.m_center.m_x)<s1.m_size/2+c1.m_radius+epsil_zero and
        abs(c1.m_center.m_y-s1.m_center.m_y)<s1.m_size/2+c1.m_radius+epsil_zero)
    {
        if( (abs(c1.m_center.m_x-s1.m_center.m_x)>s1.m_size/2 and
            abs(c1.m_center.m_y-s1.m_center.m_y)>s1.m_size/2) and
            L > c1.m_radius+epsil_zero)
        {
            return false;
        }else{
            return true;
        }
    }
    return false;
}

bool collision(circle c1, circle c2)
{
    if(difference(c1.m_center, c2.m_center)< (c1.m_radius + c2.m_radius) + epsil_zero)
    {
        return true;
    }
    return false;
}

bool collision(square s1, square s2)
{
    if( abs(s1.m_center.m_x-s2.m_center.m_x)< s1.m_size/2 + s2.m_size/2 + epsil_zero and 
        abs(s1.m_center.m_y-s2.m_center.m_y)< s1.m_size/2 + s2.m_size/2 + epsil_zero)
    {
        return true;
    }
    return false;
}

