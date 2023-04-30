/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: graphic.h                *
*********************************/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <cairomm/context.h>

struct Color
{
    constexpr Color(double r, double g, double b): 
            m_r(r),m_g(g),m_b(b){}
    double m_r;
    double m_g;
    double m_b;
};

static constexpr Color white(1., 1., 1.);
static constexpr Color black(0.1, 0.1, 0.1);
static constexpr Color grey(0.6, 0.6, 0.6);
static constexpr Color green(0., 0.7, 0.);
static constexpr Color red(0.7, 0., 0.);
static constexpr Color orange(0.7, 0.3, 0.);
static constexpr Color purple(0.5, 0., 0.7);
static constexpr Color cyan(0., 0.7, 0.7);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

void draw_border(double ratio, int size);
void gtkmm_point(double x, double y, double radius, Color color);
void gtkmm_line(double x1, double y1, double x2,
                double y2, double thickness, Color color);
void gtkmm_square(double x1, double y1, double size,//seulement contour
                  double thickness, Color color1);
void gtkmm_square(double x1, double y1, double size,//contour + intérieur
                  double thickness, Color color1, Color color2);
void gtkmm_circle(double x1, double y1, double radius,//seulement contour
                  double thickness, Color color1);
void gtkmm_circle(double x1, double y1, double radius,//contour + intérieur
                  double thickness, Color color1, Color color2);

#endif //GRAPHIC_H