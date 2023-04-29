/************|HEADER|*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: graphic.cc               *
*********************************/

#include "graphic.h"
#include <cairomm/context.h>

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);


void graphic_set_context( const Cairo::RefPtr<Cairo::Context>& cr)
{
ptcr = &cr;
}

void draw_border(double ratio, int size)
{
    (*ptcr)->set_line_width(1.0*ratio);
    (*ptcr)->set_source_rgb(0.3, 0.3, 0.3);
    (*ptcr)->move_to(0,0);
    (*ptcr)->line_to(0,size);
    (*ptcr)->line_to(size,size);
    (*ptcr)->line_to(size,0);
    (*ptcr)->line_to(0,0);
    (*ptcr)->stroke();
}

void gtkmm_line(double x1, double y1, double x2, double y2, double thickness, Color color)
{
    (*ptcr)->set_line_width(thickness);
    (*ptcr)->set_source_rgb(color.m_r, color.m_g, color.m_b);
    (*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}
void gtkmm_square(double x, double y, double size, double thickness, Color color1)
{
    (*ptcr)->set_line_width(thickness);
    (*ptcr)->set_source_rgb(color1.m_r, color1.m_g, color1.m_b);
    (*ptcr)->move_to(x-size/2,y-size/2);
    (*ptcr)->line_to(x-size/2,y+size/2);
    (*ptcr)->line_to(x+size/2,y+size/2);
    (*ptcr)->line_to(x+size/2,y-size/2);
    (*ptcr)->line_to(x-size/2,y-size/2);
    (*ptcr)->stroke();
}
void gtkmm_square(double x, double y, double size, double thickness, Color color1, Color color2)
{
    (*ptcr)->set_line_width(thickness);
    (*ptcr)->set_source_rgb(color1.m_r, color1.m_g, color1.m_b);
    (*ptcr)->save();
    (*ptcr)->move_to(x-size/2,y-size/2);
    (*ptcr)->line_to(x-size/2,y+size/2);
    (*ptcr)->line_to(x+size/2,y+size/2);
    (*ptcr)->line_to(x+size/2,y-size/2);
    (*ptcr)->line_to(x-size/2,y-size/2);
    (*ptcr)->close_path();
	(*ptcr)->set_source_rgb(color2.m_r, color2.m_g, color2.m_b);
  	(*ptcr)->fill_preserve();
	(*ptcr)->restore();
    (*ptcr)->stroke();
}
void gtkmm_circle(double x, double y, double radius, double thickness, Color color1)
{
    (*ptcr)->set_line_width(thickness);
    (*ptcr)->set_source_rgb(0.0, 0.4, 0.4);
	(*ptcr)->arc(x, y, radius, 0.0, 2.0 * M_PI);
	(*ptcr)->stroke();
}
void gtkmm_circle(double x, double y, double radius, double thickness, Color color1, Color color2)
{
    (*ptcr)->set_line_width(thickness);
    (*ptcr)->set_source_rgb(color1.m_r, color1.m_g, color1.m_b);
	(*ptcr)->save();
	(*ptcr)->arc(x, y, radius, 0.0, 2.0 * M_PI);
	(*ptcr)->close_path();
	(*ptcr)->set_source_rgb(color2.m_r, color2.m_g, color2.m_b);
  	(*ptcr)->fill_preserve();
	(*ptcr)->restore();
	(*ptcr)->stroke();
}

/*void draw_robotN(const Cairo::RefPtr<Cairo::Context>& cr,
        double ratio, int x, int y, double radius, double angle)
{
    (*ptcr)->set_line_width(1.0*ratio);
    (*ptcr)->set_source_rgb(0.1, 0.1, 0.1);

	(*ptcr)->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
    (*ptcr)->stroke();
	(*ptcr)->move_to(x,y);
	(*ptcr)->arc(x, y, 
            0.5, 
            0.0, 2.0 * M_PI);
    (*ptcr)->fill_preserve();
    (*ptcr)->stroke();

	(*ptcr)->set_source_rgb(0.0, 0.7, 0.0);
    (*ptcr)->save();
	(*ptcr)->move_to(x, y);
    (*ptcr)->line_to(x+cos(angle)*radius, y-sin(angle)*radius);
    (*ptcr)->restore();
	(*ptcr)->stroke();
}

void draw_robotS(const Cairo::RefPtr<Cairo::Context>& cr,
                double ratio, int x, int y, double radius)
{
    (*ptcr)->set_line_width(1.0*ratio);
    (*ptcr)->save();
    (*ptcr)->set_source_rgb(0.0, 0.4, 0.4);
	(*ptcr)->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
	(*ptcr)->stroke();
	(*ptcr)->move_to(x,y);
	(*ptcr)->arc(x, y, 
            0.5, 
            0.0, 2.0 * M_PI);
	(*ptcr)->fill_preserve();
    (*ptcr)->restore();
    (*ptcr)->stroke();
}

void draw_robotR(const Cairo::RefPtr<Cairo::Context>& cr,
                double ratio, int x, int y, double radius)
{
    (*ptcr)->set_line_width(1.0*ratio);
    (*ptcr)->set_source_rgb(0.1, 0.1, 0.1);
	(*ptcr)->save();
	
	(*ptcr)->arc(x, y, 
            radius, 
            0.0, 2.0 * M_PI);
	(*ptcr)->close_path();
	(*ptcr)->set_source_rgb(0.0, 0.8, 0.0);
  	(*ptcr)->fill_preserve();
	(*ptcr)->restore();
	(*ptcr)->stroke();

}

void draw_particle(const Cairo::RefPtr<Cairo::Context>& cr,
                double ratio, int x, int y, double size)
{
    (*ptcr)->set_line_width(0.2*ratio);
    (*ptcr)->set_source_rgb(0.8, 0.0, 0.0);
    (*ptcr)->save();
 	(*ptcr)->move_to(x-size/2, y-size/2);
    (*ptcr)->line_to(x+size/2,y-size/2);
    (*ptcr)->line_to(x+size/2,y+size/2);
    (*ptcr)->line_to(x-size/2,y+size/2);
    (*ptcr)->line_to(x-size/2,y-size/2);
    (*ptcr)->close_path();
	(*ptcr)->set_source_rgb(0.7, 0.7, 0.7);
  	(*ptcr)->fill_preserve();
	(*ptcr)->restore();
    (*ptcr)->stroke();
}*/