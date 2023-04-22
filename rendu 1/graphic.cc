#include "graphic.h"
#include <math.h>

/***************************************
/nom du fichier : graphic.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

void draw_robotN(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius, double angle)
{
    cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
    cr->stroke();
    cr->move_to(x, y);
    cr->line_to(x+cos(angle)*radius, y+sin(angle)*radius);
    cr->stroke();
}

void draw_robotS(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius)
{
    cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
    cr->stroke();
}

void draw_robotR(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius)
{
    cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
    cr->stroke();
}

void draw_particle(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double size)
{

    cr->move_to(x-size/2, y-size/2);
    cr->line_to(x+size/2,y-size/2);
    cr->line_to(x+size/2,y+size/2);
    cr->line_to(x-size/2,y+size/2);
    cr->line_to(x-size/2,y-size/2);
    cr->close_path()
    cr->stroke();
}