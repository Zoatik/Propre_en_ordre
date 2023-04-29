#ifndef GRAPHIC_H
#define GRAPHIC_H

/***************************************
/nom du fichier : graphic.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include <cairomm/context.h>

void draw_border(const Cairo::RefPtr<Cairo::Context>& cr, double ratio,
                int size);
void draw_robotS(const Cairo::RefPtr<Cairo::Context>& cr, double ratio,
                int x, int y, double radius);
void draw_robotN(const Cairo::RefPtr<Cairo::Context>& cr, double ratio,
                int x, int y, double radius, double angle);
void draw_robotR(const Cairo::RefPtr<Cairo::Context>& cr, double ratio,
                int x, int y, double radius);
void draw_particle(const Cairo::RefPtr<Cairo::Context>& cr, double ratio,
                int x, int y, double size);

#endif //GRAPHIC_H