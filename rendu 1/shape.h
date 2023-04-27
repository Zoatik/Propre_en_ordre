/************\HEADER/*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: shape.h                  *
*********************************/

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <math.h>
#include "graphic.h"


constexpr double epsil_zero(0.125);

/**S_2D**/
struct s_2d
{
    //ctor
    s_2d(){}
    s_2d(double x, double y): m_x(x), m_y(y){}

    //att
    double m_x = 0.;
    double m_y = 0.;
};

s_2d operator+(s_2d vect1, s_2d vect2);
s_2d operator-(s_2d vect1, s_2d vect2);

/**CIRCLE**/
struct circle
{
    //ctor
    circle(){}
    circle(s_2d center, double radius): m_center(center), m_radius(radius){}

    //att
    s_2d m_center;
    double m_radius;
};

/**SQUARE**/
struct square
{
    //ctor
    square(){}
    square(s_2d center, double size): m_center(center), m_size(size){}

    //att
    s_2d m_center;
    double m_size;

};

/**FONCTIONS**/
//fonctions vectorielles
double distance(s_2d point_1, s_2d point_2);
double norm(s_2d point);

/*Vérifications positions/collisions*/
bool check_position(circle c1, double dmax);//return false si outside
bool check_position(square s1, double dmax);
bool collision(circle c1, square s1, bool init);//init = true : phase d'initialisation
bool collision(circle c1, circle c2, bool init);
bool collision(square s1, square s2, bool init);
void draw_info_robotS(const Cairo::RefPtr<Cairo::Context>& cr,
                    int xc, int yc, double ratio, circle circle);
void draw_info_robotN(const Cairo::RefPtr<Cairo::Context>& cr, 
                        int xc, int yc, double ratio, circle circle, double angle);
void draw_info_robotR(const Cairo::RefPtr<Cairo::Context>& cr, 
                        int xc, int yc, double ratio, circle circle);
void draw_info_particle(const Cairo::RefPtr<Cairo::Context>& cr, 
                        int xc, int yc, double ratio, square square);

#endif // SHAPE_H_INCLUDED
