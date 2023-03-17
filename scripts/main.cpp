#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    /**Vérification**/
    string file_path = argv[1];
    File infos_file;
    infos_file.read_file(file_path);//récupération des infos
    Simulation world;
    world.generate(infos_file);//vérifications des infos et création du monde
    return 0;
}


