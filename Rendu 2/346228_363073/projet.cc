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
    bool read_success(false);
    Simulation world;
    if(argc > 1)//test file donné
        read_success = world.read_file(argv[1]);
        
    auto app = Gtk::Application::create();
    
    return app->make_window_and_run<GuiWindow>(1, argv, read_success, &world);
}


