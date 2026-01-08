#ifndef PARTICLI_ENGINE_H
#define PARTICLI_ENGINE_H
#include <vector>

class Engine {
    public:
    // Constructor
    Engine(int length, int height);

    // Run one tick of simulation logic
    void update();

    // Create a particle of type at specified position
    void spawn_particle(int x, int y, int type);

    // Send out grid
    const std::vector<int>& getGrid() {
        return current;
    }

    private:
    int rows;
    int cols;
    std::vector<int> current;
    std::vector<int> next;
};

#endif //PARTICLI_ENGINE_H