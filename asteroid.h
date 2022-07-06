#ifndef ASTEROID_H
#define ASTEROID_H
#include "entity.h"

class Asteroid : public Entity
{
public:
    Asteroid();
    virtual void update() override;
};

#endif // ASTEROID_H
