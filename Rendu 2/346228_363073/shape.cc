/************|HEADER|*************
* AUTHORS: - Hall Axel (30%)     *
*          - Michel Lucas (70%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: shape.cc                 *
*********************************/

#include "shape.h"



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

s_2d operator*(double lambda, s_2d vect)
{
    return s_2d(vect.m_x*lambda, vect.m_y*lambda);
}

bool operator==(s_2d vect1, s_2d vect2)
{
    return vect1.m_x==vect2.m_x && vect1.m_y==vect2.m_y;
}

/**TESTS DE POSITION**/
bool check_position(circle c1, double dmax)
{
    return (c1.m_center.m_x+c1.m_radius)<dmax and
           (c1.m_center.m_y+c1.m_radius)<dmax and
           (c1.m_center.m_x-c1.m_radius)> -dmax and
           (c1.m_center.m_y-c1.m_radius)> -dmax;
}

bool check_position(square s1, double dmax)
{
    return (s1.m_center.m_x+s1.m_size/2)<dmax and
           (s1.m_center.m_y+s1.m_size/2)<dmax and
           (s1.m_center.m_x-s1.m_size/2)> -dmax and
           (s1.m_center.m_y-s1.m_size/2)> -dmax;
}

/**TESTS DE COLLISIONS**/
bool collision(circle c1, square s1, bool init)
// si init = true : phase d'initialisation
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

void draw_line(s_2d start, s_2d end, double thickness, Color color)
{
    gtkmm_line(start.m_x, start.m_y, end.m_x, end.m_y, thickness, color);
}

void draw_square(s_2d center, double size, double thickness, 
            bool filled, Color color1, Color color2)
{
    if(filled)
    {
        gtkmm_square(center.m_x, center.m_y, size, thickness, color1, color2);
    }
    else
        gtkmm_square(center.m_x, center.m_y, size, thickness, color1);
}

void draw_circle(s_2d center, double radius, double thickness, 
            bool filled, Color color1, Color color2)
{
    if(filled)
    {
        gtkmm_circle(center.m_x, center.m_y, radius, thickness, color1, color2);
    }
    else
        gtkmm_circle(center.m_x, center.m_y, radius, thickness, color1);
}
