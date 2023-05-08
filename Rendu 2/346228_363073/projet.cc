/************|HEADER|*************
* AUTHORS: - Hall Axel (50%)     *
*          - Michel Lucas (50%)  *
* SCIPERS: - 346228              *
*          - 363073              *
* VERSION: 2.6                   *
* FILE: projet.cc                *
*********************************/

#include <gtkmm/application.h>
#include "Simulation.h"
#include "gui.h"


using namespace std;



int main(int argc, char *argv[])
{
    string file_path("");
    if(argc>1)
        file_path = argv[1];
    Simulation world;
    //vérifications des infos et création du monde
    bool read_success = world.read_file(file_path);
    auto app = Gtk::Application::create();
    
    return app->make_window_and_run<GuiWindow>(1, argv, read_success, &world);
      
}


