#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "game.h"
#include "animation.h"
#include "entity.h"

class Player;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();
private:
    void loadPixmap();
    Game m_game;
    QPixmap m_bgPixmap, m_fireBluePixmap, m_fireRedPixmap, m_rockPixmap, m_rockSmallPixmap, m_spaceShipPixmap,
        m_spaceShipGoPixmap, m_explosionAPixmap, m_explosionBPixmap, m_explosionCPixmap;
    float m_deltaTime, m_loopTime, m_loopSpeed;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    bool m_spacePressed, m_leftPressed, m_rightPressed, m_upPressed;

    Animation m_sExplosion;
    Animation m_sExplosionB;
    Animation m_sRock;
    Animation m_sRock_small;
    Animation m_sBullet;
    Animation m_sPlayer;
    Animation m_sPlayer_go;
    Animation m_sExplosion_ship;

    std::list<Entity*> entities;

    Player *m_p;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
