/***************************************
/nom du fichier : main.cpp
/auteurs        : - Axel Hall - 346228
/				  - Lucas Michel - 363073
/version        : 1.1
****************************************/

#include <iostream>
#include <gtkmm/application.h>
#include "Simulation.h"
#include "gui.h"


using namespace std;

int main(int argc, char *argv[])
{
    /**Vérification**/
    
    std::string file_path = argv[1];
    File infos_file;
    infos_file.read_file(file_path);//récupération des infos
    Simulation world;
    world.generate(infos_file);//vérifications des infos et création du monde
    auto app = Gtk::Application::create();
    
    return app->make_window_and_run<GuiWindow>(1, argv, world);
    
    
}


