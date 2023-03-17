#include "shape.h"
#include "constantes.h"


/**METHODES SUR LES POINTS-VECTEURS**/
double distance(s_2d point_1, s_2d point_2)
{
    return norm(point_1-point_2);
}

double norm(s_2d point)
{
    return pow(pow(point.m_x,2)+pow(point.m_y,2), 0.5);
}

///operators overload s_2d
s_2d operator+(s_2d vect1, s_2d vect2)
{
    return s_2d(vect1.m_x + vect2.m_x, vect1.m_y + vect2.m_y);

}

s_2d operator-(s_2d vect1, s_2d vect2)
{
    return s_2d(vect1.m_x - vect2.m_x, vect1.m_y - vect2.m_y);
}

/**TESTS DE POSITION**/
bool check_position(circle c1)
{
    return (c1.m_center.m_x+c1.m_radius)<dmax and
           (c1.m_center.m_y+c1.m_radius)<dmax and
           (c1.m_center.m_x-c1.m_radius)> -dmax and
           (c1.m_center.m_y-c1.m_radius)> -dmax;
}

bool check_position(square s1)
{
    return (s1.m_center.m_x+s1.m_size/2)<dmax and
           (s1.m_center.m_y+s1.m_size/2)<dmax and
           (s1.m_center.m_x-s1.m_size/2)> -dmax and
           (s1.m_center.m_y-s1.m_size/2)> -dmax;
}

/**TESTS DE COLLISIONS**/
bool collision(circle c1, square s1, bool init)//init = true : phase d'initialisation
{
    s_2d vect_2d(fabs(c1.m_center.m_x-s1.m_center.m_x)-s1.m_size/2,
                 fabs(c1.m_center.m_y-s1.m_center.m_y)-s1.m_size/2);
    double L(norm(vect_2d));

    if(fabs(c1.m_center.m_x-s1.m_center.m_x)<
       s1.m_size/2+c1.m_radius+int(!init)*epsil_zero and
       fabs(c1.m_center.m_y-s1.m_center.m_y)<
       s1.m_size/2+c1.m_radius+int(!init)*epsil_zero)
    {
        return !(fabs(c1.m_center.m_x-s1.m_center.m_x)>s1.m_size/2 and
                 fabs(c1.m_center.m_y-s1.m_center.m_y)>s1.m_size/2 and
                 L > c1.m_radius+int(!init)*epsil_zero);
    }
    return false;
}

bool collision(circle c1, circle c2, bool init)
{
    return (distance(c1.m_center, c2.m_center) <
           (c1.m_radius + c2.m_radius) + int(!init)*epsil_zero);
}

bool collision(square s1, square s2, bool init)
{
    return (fabs(s1.m_center.m_x-s2.m_center.m_x) <
            s1.m_size/2 + s2.m_size/2 + int(!init)*epsil_zero and
            fabs(s1.m_center.m_y-s2.m_center.m_y) <
            s1.m_size/2 + s2.m_size/2 + int(!init)*epsil_zero);
}

