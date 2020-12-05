#include "App.h"


int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 1366, 762, "The Way of the Mandalore");

    app->run();

}
