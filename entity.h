#ifndef ENTITY_H
#define ENTITY_H
#include <QString>

#include "animation.h"

class QGraphicsScene;
class Entity
{
public:
    Entity();
    void settings(Animation &a,int x,int y,float angle=0,int radius=1);
    virtual void update();
    void draw(QGraphicsScene *scene);
    virtual ~Entity();

    float m_x, m_y, m_dx, m_dy, m_R, m_angle;
    bool m_life;
    QString m_name;
    Animation m_anim;
};

#endif // ENTITY_H
