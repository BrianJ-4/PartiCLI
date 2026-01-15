#include "../include/engine.h"
#include <iostream>
#include <random>

std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> coinFlip(0, 1);

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

    // Sand Particle
    if (p.type == SAND) {
        // New y coordinate particle will fall into
        const int ny = y + 1;
        if (ny < rows) {
            // Position under particle
            const int dst = get1DPosition(ny, x);
            ParticleType dstType = next[dst].type;
            // Swap positions if air or water
            if (dstType == AIR || dstType == WATER) {
                // Swap particles
                Particle falling = p;
                falling.moved = true;
                next[get1DPosition(y, x)] = {dstType, true};
                next[dst] = falling;
                return;
            }
            // Piling logic if sand
            if (dstType == SAND) {
                // Randomly move down and left or down and right
                const int c = coinFlip(rng);

                for (int a = 0; a < 2; ++a) {
                    const bool left = (a == 0) ? (c == 0) : (c != 0);
                    const int nx = left ? x - 1 : x + 1;

                    if (nx < 0 || nx >= cols)
                        continue;

                    const int diag = get1DPosition(ny, nx);
                    ParticleType diagType = next[diag].type;
                    if (diagType == AIR || diagType == WATER) {
                        // Swap particles
                        Particle falling = p;
                        falling.moved = true;
                        next[get1DPosition(y, x)] = {diagType, true};
                        next[diag] = falling;
                        return;
                    }
                }
            }
        }
    }
    // Water Particle
    if (p.type == WATER) {
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
        // Cannot move down, flow left and right
        const int c = coinFlip(rng);
        for (int a = 0; a < 2; ++a) {
            const bool left = (a == 0) ? (c == 0) : (c != 0);
            const int nx = left ? x - 1 : x + 1;

            if (nx < 0 || nx >= cols)
                continue;

            const int side = get1DPosition(y, nx);
            ParticleType sideType = next[side].type;
            if (sideType == AIR) {
                // Swap particles
                Particle flowing = p;
                flowing.moved = true;
                next[get1DPosition(y, x)] = {sideType, true};
                next[side] = flowing;
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
