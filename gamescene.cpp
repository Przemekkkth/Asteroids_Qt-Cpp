#include "gamescene.h"
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include <QDebug>
#include <QKeyEvent>
#include <list>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(20.0f),
      m_spacePressed(false), m_leftPressed(false), m_rightPressed(false), m_upPressed(false),
      m_p(new Player())
{
    loadPixmap();
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(Game::ITERATION_VALUE);
    m_elapsedTimer.start();

    //m_sExplosion = Animation(m_explosionAPixmap, 0,0,256,256, 48, 0.5);
    m_sRock = Animation(m_rockPixmap, 0,0,64,64, 16, 0.2);
    m_sRock_small = Animation(m_rockSmallPixmap, 0,0,64,64, 16, 0.2);
    m_sBullet = Animation(m_fireBluePixmap, 0,0,32,64, 16, 0.8);
    m_sPlayer = Animation(m_spaceShipPixmap, 0,0,99,75, 1, 0);
    m_sPlayer_go = Animation(m_spaceShipPixmap, 0,0,99,75, 1, 0);
    //m_sExplosion_ship = Animation(m_explosionAPixmap, 0,0,192,192, 64, 0.5);

    for(int i=0;i<15;i++)
    {
        Asteroid *a = new Asteroid();
        a->settings(m_sRock, rand()%Game::RESOLUTION.width(), rand()%Game::RESOLUTION.height(), rand()%360, 25);
        entities.push_back(a);
    }

    m_p->settings(m_sPlayer,200,200,0,20);
    entities.push_back(m_p);

    QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    addItem(bgItem);
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed )
    {
        m_loopTime -= m_loopSpeed;

        if(m_spacePressed)
        {
            Bullet *b = new Bullet();
            b->settings(m_sBullet, m_p->m_x, m_p->m_y, m_p->m_angle, 10);
            entities.push_back(b);
            m_spacePressed = false;
        }
        if(m_rightPressed)
        {
            m_p->m_angle += 3;
        }
        if(m_leftPressed)
        {
            m_p->m_angle -= 3;
        }
        if(m_upPressed)
        {
            m_p->m_thrust = true;
        }
        else
        {
            m_p->m_thrust = false;
        }

        for(auto a:entities)
            for(auto b:entities)
            {
                if (a->m_name=="asteroid" && b->m_name=="bullet")
                    if ( Game::isCollide(a,b) )
                    {
                        a->m_life = false;
                        b->m_life = false;

//                        Entity *e = new Entity();
//                        e->settings(m_sExplosion,a->m_x,a->m_y);
//                        e->m_name="explosion";
//                        entities.push_back(e);


                        for(int i=0;i<2;i++)
                        {
                            if (a->m_R==15) continue;
                            Entity *e = new Asteroid();
                            e->settings(m_sRock_small,a->m_x,a->m_y,rand()%360,15);
                            entities.push_back(e);
                        }

                    }

                if (a->m_name=="player" && b->m_name=="asteroid")
                    if ( Game::isCollide(a,b) )
                    {
                        b->m_life=false;

//                        Entity *e = new Entity();
//                        e->settings(m_sExplosion_ship,a->m_x,a->m_y);
//                        e->m_name="explosion";
//                        entities.push_back(e);

                        m_p->settings(m_sPlayer,Game::RESOLUTION.width()/2,Game::RESOLUTION.height()/2,0,20);
                        m_p->m_dx=0;
                        m_p->m_dy=0;
                    }
            }


        if (m_p->m_thrust)
        {
            m_p->m_anim = m_sPlayer_go;
        }
        else
        {
            m_p->m_anim = m_sPlayer;
        }


        for(auto e:entities)
        {
            if (e->m_name=="explosion")
            {
                if (e->m_anim.isEnd())
                {
                    e->m_life=0;
                }
            }

        }


        if (rand()%150==0)
        {
            Asteroid *a = new Asteroid();
            a->settings(m_sRock, 0,rand()%Game::RESOLUTION.height(), rand()%360, 25);
            entities.push_back(a);
        }

        for(auto i=entities.begin();i!=entities.end();)
        {
            Entity *e = *i;

            e->update();
            e->m_anim.update();

            if (e->m_life == false)
            {
                i=entities.erase(i);
                delete e;
            }
            else i++;
        }


        clear();


        for(auto i:entities)
        {
            QPixmap pixmap;
            QPoint pos;
            qreal angle;
            QSize size;
            qreal R = 0.0;
            i->draw(pixmap, pos, angle, size, R);
            QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
            pItem->setPixmap(pixmap);
            pItem->setPos(pos);
            pItem->setRotation(angle + 90);
            pItem->setTransformOriginPoint(size.width(), size.height());
            addItem(pItem);
        }

    }
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }

    if(m_fireBluePixmap.load(Game::PATH_TO_FIRE_BLUE_PIXMAP))
    {
        qDebug() << "FireBluePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FireBluePixmap is not loaded successfully";
    }

    if(m_fireRedPixmap.load(Game::PATH_TO_FIRE_RED_PIXMAP))
    {
        qDebug() << "FireRedPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FireRedPixmap is not loaded successfully";
    }

    if(m_rockPixmap.load(Game::PATH_TO_ROCK_PIXMAP))
    {
        qDebug() << "RockPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "RockPixmap is not loaded successfully";
    }

    if(m_rockSmallPixmap.load(Game::PATH_TO_ROCK_SMALL_PIXMAP))
    {
        qDebug() << "RockSmallPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "RockSmallPixmap is not loaded successfully";
    }

    if(m_spaceShipPixmap.load(Game::PATH_TO_SPACESHIP_PIXMAP))
    {
        qDebug() << "SpaceShipPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "SpaceShipPixmap is not loaded successfully";
    }

    if(m_spaceShipGoPixmap.load(Game::PATH_TO_SPACESHIP_GO_PIXMAP))
    {
        qDebug() << "SpaceShipGoPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "SpaceShipGoPixmap is not loaded successfully";
    }

    if(m_explosionAPixmap.load(Game::PATH_TO_EXPLOSION_A_PIXMAP))
    {
        qDebug() << "ExplosionAPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionAPixmap is not loaded successfully";
    }

    if(m_explosionBPixmap.load(Game::PATH_TO_EXPLOSION_B_PIXMAP))
    {
        qDebug() << "ExplosionBPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionBPixmap is not loaded successfully";
    }

    if(m_explosionCPixmap.load(Game::PATH_TO_EXPLOSION_C_PIXMAP))
    {
        qDebug() << "ExplosionCPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionCPixmap is not loaded successfully";
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

        break;
    case Qt::Key_Up:
    {
        m_upPressed = true;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightPressed = true;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftPressed = true;
    }
        break;
    }

    if( !event->isAutoRepeat() )
    {
        if( event->key() == Qt::Key_Space )
        {
            m_spacePressed = true;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    {
        m_spacePressed = false;
    }
        break;
    case Qt::Key_Up:
    {
        m_upPressed = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightPressed = false;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftPressed = false;
    }
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}
