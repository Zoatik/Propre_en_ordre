#include "graphic.h"
#include <math.h>

/***************************************
/nom du fichier : graphic.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

void draw_border(const Cairo::RefPtr<Cairo::Context>& cr, int size)
{
    cr->set_source_rgb(0.1, 0.1, 0.1);
    cr->move_to(0,0);
    cr->line_to(0,size);
    cr->line_to(size,size);
    cr->line_to(size,0);
    cr->line_to(0,0);
    cr->stroke();
}

void draw_robotN(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius, double angle)
{
    cr->set_source_rgb(0.1, 0.1, 0.1);

	cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
    cr->stroke();
	cr->move_to(x,y);
	cr->arc(x, y, 
            0.5, 
            0.0, 2.0 * M_PI);
    cr->fill_preserve();
    cr->stroke();

	cr->set_source_rgb(0.0, 0.7, 0.0);
    cr->save();
	cr->move_to(x, y);
    cr->line_to(x+cos(angle)*radius, y-sin(angle)*radius);
    cr->restore();
	cr->stroke();
}

void draw_robotS(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius)
{
    cr->save();
    cr->set_source_rgb(0.0, 0.4, 0.4);
	cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
	cr->stroke();
	cr->move_to(x,y);
	cr->arc(x, y, 
            0.5, 
            0.0, 2.0 * M_PI);
	cr->fill_preserve();
    cr->restore();
    cr->stroke();
}

void draw_robotR(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double radius)
{
    cr->set_source_rgb(0.1, 0.1, 0.1);
	cr->save();
	
	cr->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
	cr->close_path();
	cr->set_source_rgb(0.0, 0.8, 0.0);
  	cr->fill_preserve();
	cr->restore();
	cr->stroke();

}

void draw_particle(const Cairo::RefPtr<Cairo::Context>& cr,
                int x, int y, double size)
{
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->save();
 	cr->move_to(x-size/2, y-size/2);
    cr->line_to(x+size/2,y-size/2);
    cr->line_to(x+size/2,y+size/2);
    cr->line_to(x-size/2,y+size/2);
    cr->line_to(x-size/2,y-size/2);
    cr->close_path();
	cr->set_source_rgb(0.7, 0.7, 0.7);
  	cr->fill_preserve();
	cr->restore();
    cr->stroke();
}