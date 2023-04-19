#ifndef GUI_H
#define GUI_H

/***************************************
/nom du fichier : gui.h
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include "graphic.h"
#include <gtkmm/box.h>
#include <gtkmm/button.h>

class Gui:
{
    public:
        Gui()
        ~Gui()
        void add_gui_on_window(Gtk::Vbox);
    protected:
    private:
        Gtk::Box main_box;
        Gtk::Button test_button("Salut");
}



#endif //GUI_H