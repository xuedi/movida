#include <iostream>

#include "config.h"
#include "status.h"
#include "movida.h"



// singeltons
config *config::globInstance = 0;
status *status::globInstance = 0;



using namespace std;

int main() {

    // MOST important load the config data!!
    if(!config::instance()->load("data/config/main.conf")) {
        cout << "Error loading config file" << endl;
        return 1;
    }



    // create game engine
    movida *gameEngine = new movida;

    // init
    gameEngine->init();
    gameEngine->run(); //TODO: restart with different resolution

    // cleanup
    delete gameEngine;

    // exit
    return 0;
}
