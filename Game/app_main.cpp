#include "Game.h"

int main(int argc, char** argv) {
    
    GlutApp* mainGame = new Game(argc, argv, 1366, 762, "The Way of the Mandalore");

    mainGame->run();

}
