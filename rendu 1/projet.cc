/***************************************
/nom du fichier : main.cpp
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include <iostream>
#include "Simulation.h"
#include "gui.h"
#include <gtkmm/application.h>

using namespace std;

int main(int argc, char *argv[])
{
    /**Vérification**/
    string file_path = argv[1];
    File infos_file;
    infos_file.read_file(file_path);//récupération des infos
    auto app = Gtk::Application::create();
    Simulation world;
    world.generate(infos_file);//vérifications des infos et création du monde
    return app->make_window_and_run<Window>(argc, argv);
    
}


