#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity
{
public:
    Player();
    virtual void update() override;

    bool m_thrust;
};

#endif // PLAYER_H
