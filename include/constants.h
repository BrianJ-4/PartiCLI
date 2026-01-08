#ifndef PARTICLI_CONSTANTS_H
#define PARTICLI_CONSTANTS_H

enum ParticleType {
    AIR = 0,
    SAND,
    WATER,
};

struct Particle {
    ParticleType type;
    bool moved;
};

#endif //PARTICLI_CONSTANTS_H