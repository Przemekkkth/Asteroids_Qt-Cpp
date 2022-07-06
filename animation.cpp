#include "animation.h"

Animation::Animation()
{

}

Animation::Animation(QPixmap &t, int x, int y, int w, int h, int count, float speed)
    : m_frame(0.f), m_speed(speed)
{
    for (int i=0;i<count;i++)
    {
        m_frames.push_back( QRect(x+i*w, y, w, h)  );
    }
    m_texture = t;

    m_sprite.setPixmap(m_texture.copy(m_frames[0]));
    m_sprite.setTransformOriginPoint(w/2, h/2);
}

void Animation::update()
{
    m_frame += m_speed;
    int n = m_frames.size();
    if ( m_frame >= n)
    {
        m_frame -= n;
    }
    if ( n>0)
    {
        m_sprite.setPixmap( m_texture.copy(m_frames[int(m_frame)]));
    }
}

bool Animation::isEnd()
{
    return m_frame + m_speed >= m_frames.size();
}

Animation &Animation::operator=(const Animation &a)
{
    if(this != &a)
    {
        m_texture = a.m_texture;
        m_frame = a.m_frame;
        m_speed = a.m_speed;
        m_frames = a.m_frames;
        m_sprite.setPixmap(a.m_sprite.pixmap());
        m_sprite.setPos(a.m_sprite.pos());
        m_sprite.setTransformOriginPoint(a.m_sprite.transformOriginPoint());
    }
    return *this;
}
