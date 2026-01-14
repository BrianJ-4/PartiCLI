#include "../include/engine.h"

Engine::Engine(const int length, const int height) {
    cols = length;
    rows = height;
    current.resize(rows * cols);
    next.resize(rows * cols);
}

void Engine::update() {
    // First copy grid into next and mark all particles as not moved
    next = current;
    for (auto& p : next)
        p.moved = false;

    // Calculate movement and update position for all cells
    for (int y = rows - 1; y >= 0; --y) {
        for (int x = 0; x < cols; ++x) {
            moveParticle(x, y);
        }
    }
    current.swap(next);
}

void Engine::moveParticle(int x, int y) {
    Particle& p = next[get1DPosition(y, x)];
    // Skip moved and air particles
    if (p.moved || p.type == AIR)
        return;

    if (p.type == SAND) {
        // New y coordinate particle will fall into
        const int ny = y + 1;
        if (ny < rows) {
            // Position under particle
            const int dst = get1DPosition(ny, x);
            ParticleType dstType = next[dst].type;
            // Swap positions if air
            if (dstType == AIR) {
                // Swap particles
                Particle falling = p;
                falling.moved = true;
                next[get1DPosition(y, x)] = {dstType, true};
                next[dst] = falling;
                return;
            }
        }
    }
    // If it didn't move, mark it as processed this tick
    p.moved = true;
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
