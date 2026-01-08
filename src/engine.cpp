#include "../include/engine.h"

Engine::Engine(const int length, const int height) {
    cols = length;
    rows = height;
    current.resize(rows * cols);
    next.resize(rows * cols);
}

void Engine::update() {

}

void Engine::spawn_particle(const int x, const int y, const ParticleType type) {
    // Boundary check
    if (x < 0 || x >= cols || y < 0 || y >= rows || current[get1DPosition(y, x)].type != AIR)
        return;
    const Particle new_particle = {type, false};
    current[get1DPosition(y, x)] = new_particle;
}

// Call with get1DPosition(y, x);
int Engine::get1DPosition(const int row, const int col) const {
    return row * cols + col;
}
