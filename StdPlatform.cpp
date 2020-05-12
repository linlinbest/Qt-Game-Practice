#include "StdPlatform.h"
#include "Game.h"

extern Game * game;

StdPlatform::StdPlatform(QGraphicsItem * parent): QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/std_platform.png"));
}

