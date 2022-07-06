#include "entity.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

Entity::Entity()
{
    m_life = true;
}

void Entity::settings(Animation &a, int x, int y, float angle, int radius)
{
    m_anim = a;
    m_x=x;
    m_y=y;
    m_angle = angle;
    m_R = radius;
}

void Entity::update()
{

}

void Entity::draw(QGraphicsScene *scene)
{
    m_anim.m_sprite.setPos(m_x, m_y);
    m_anim.m_sprite.setRotation(m_angle + 90);
    if(m_anim.m_sprite.scene() == nullptr)
    {
        scene->addItem(&m_anim.m_sprite);
    }


    QGraphicsEllipseItem circle(0, 0, m_R, m_R);
    circle.setBrush(QColor(255,0,0,170));
    circle.setPen(QColor(255,0,0,170));
    circle.setPos(m_x, m_y);
    circle.setTransformOriginPoint(m_R, m_R);
    if(circle.scene() == nullptr)
    {
        scene->addItem(&circle);
    }
}

Entity::~Entity()
{

}
