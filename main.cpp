#include <iostream>
#include "File.h"

using namespace std;

int main(int argc, char *argv[])
{
    /**Vérification**/
    string file_path = argv[1];
    File infos_file;
    infos_file.read_file(file_path);
    //Robot_N r;
    //r.set_pos(1.,2.);

    return 0;
}


