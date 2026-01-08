#include "../include/engine.h"

Engine::Engine(const int length, const int height) {
    rows = length;
    cols = height;
    current.resize(rows * cols);
    next.resize(rows * cols);
}

void Engine::update() {

}

void Engine::spawn_particle(int x, int y, int type) {

}