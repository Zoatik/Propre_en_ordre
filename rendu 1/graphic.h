#ifndef GRAPHIC_H
#define GRAPHIC_H

/***************************************
/nom du fichier : graphic.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include <cairomm/context.h>

struct Color
{
    Color(){}
    Color(double r, double g, double b): 
            m_r(r),m_g(g),m_b(b){}
     double m_r;
     double m_g; 
     double m_b;
};

 Color white(1., 1., 1.);
 Color black(0.1, 0.1, 0.1);
 Color grey(0.3, 0.3, 0.3);
 Color green(0., 0.7, 0.);
 Color red(0.7, 0., 0.);
 Color orange(0.7, 0.3, 0.);
 Color purple(0.5, 0., 0.7);
 Color cyan(0., 0.7, 0.7);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

void draw_border(double ratio, int size);
void gtkmm_line(double x1, double y1, double x2, double y2, double thickness, Color color);
void gtkmm_square(double x1, double y1, double size, double thickness, Color color1);
void gtkmm_square(double x1, double y1, double size, double thickness, Color color1, Color color2);
void gtkmm_circle(double x1, double y1, double radius, double thickness, Color color1);
void gtkmm_circle(double x1, double y1, double radius, double thickness, Color color1, Color color2);

#endif //GRAPHIC_H