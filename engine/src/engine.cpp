#include <iostream>

#include "interface/display.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        clog << "Wrong number of arguments provided! Required 1" << endl;
        return -1;
    }

    run(argc, argv);

    return 0;
}
