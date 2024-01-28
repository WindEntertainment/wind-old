#include "game.h"

#include <earth/earth.h>

int main(int argc, char** argv) {
    earth::Application().build("./asset/");
    return chaos::Game().main();
}