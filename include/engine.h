#ifndef PARTICLI_ENGINE_H
#define PARTICLI_ENGINE_H
#include <vector>
#include "constants.h"

class Engine {
    public:
    // Constructor
    Engine(int length, int height);

    // Run one tick of simulation logic
    void update();

    // Create a particle of type at specified position
    void spawn_particle(int x, int y, ParticleType type);

    // Send out grid
    const std::vector<Particle>& getGrid() {
        return current;
    }

    private:
    int rows;
    int cols;
    std::vector<Particle> current;
    std::vector<Particle> next;

    // Convert 2D coordinates to position in 1D vector
    int get1DPosition(int row, int col) const;

};

#endif //PARTICLI_ENGINE_H