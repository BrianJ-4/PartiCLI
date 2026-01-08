#include "../include/engine.h"

Engine::Engine(const int length, const int height) {
    cols = length;
    rows = height;
    current.resize(rows * cols);
    next.resize(rows * cols);
}

void Engine::update() {

}

void Engine::spawn_particle(int x, int y, int type) {

}

// Call with get1DPosition(y, x);
int Engine::get1DPosition(const int row, const int col) const {
    return row * cols + col;
}
