#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    /**Vérification**/
    string file_path = argv[1];
    File infos_file;
    infos_file.read_file(file_path);
    Simulation world;
    std::cout << "generating";
    world.generate(infos_file);
    std::cout<<"generated";
    //Robot_N r;
    //r.set_pos(1.,2.);

    return 0;
}


