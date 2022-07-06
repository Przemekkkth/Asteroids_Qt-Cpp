#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <QRect>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Animation
{
public:
    float m_frame, m_speed;
    QGraphicsPixmapItem m_sprite;
    std::vector<QRect> m_frames;
    QPixmap m_texture;

    Animation();

    Animation (QPixmap &t, int x, int y, int w, int h, int count, float speed);

    void update();

    bool isEnd();

    Animation& operator=(const Animation& a);
};

#endif // ANIMATION_H
