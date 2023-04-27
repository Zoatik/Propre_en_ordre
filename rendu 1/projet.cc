/************\HEADER/*************
* AUTHORS: - Hall Axel           *
*          - Michel Lucas        *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.0                   *
* FILE: projet.cc                *
*********************************/

#include <iostream>
#include <gtkmm/application.h>
#include "Simulation.h"
#include "gui.h"


using namespace std;



int main(int argc, char *argv[])
{
    /**Vérification**/

    string file_path = argv[1];
    Simulation world;
    bool read_success = world.read_file(file_path);//vérifications des infos et création du monde
    auto app = Gtk::Application::create();
    
    return app->make_window_and_run<GuiWindow>(1, argv, &world);
      
}


