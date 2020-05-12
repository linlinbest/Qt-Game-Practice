#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "StdPlatForm.h"

const int TIME_INTERVAL = 20;//ms
const int SCENE_HEIGHT = 650;
const int SCENE_WIDTH = 450;
const double GRAVITY = 1500.0;
const double JUMP = -750.0;

class Game: public QGraphicsView {
public:
    QGraphicsScene* scene;
    Player* player;
    StdPlatform* std_platform;
    QTimer* timer;
    unsigned int score;

    Game(unsigned int seed);
    void mousePressEvent(QMouseEvent *event);

};

#endif // GAME_H
