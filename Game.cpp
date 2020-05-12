#include <QBrush>
#include <QMouseEvent>
#include <QTimer>
#include "Game.h"


Game::Game(unsigned int seed) {
    score = 0;
    srand(seed);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,SCENE_WIDTH,SCENE_HEIGHT); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    setScene(scene);

    setFixedSize(SCENE_WIDTH,SCENE_HEIGHT);

    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    player = new Player();
    player->setPos(SCENE_WIDTH/2,SCENE_HEIGHT-200);
    //make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    std_platform = new StdPlatform();
    std_platform->setPos(SCENE_WIDTH/2,SCENE_HEIGHT-100);
    scene->addItem(std_platform);

    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(fall()));
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(action()));
    //QObject::connect(player,SIGNAL(needNewPlatform()),player,SLOT(generatePlatform()));


    timer->start(TIME_INTERVAL);

}

void Game::mousePressEvent(QMouseEvent *event) {
    if (event->button()) player->setFocus();
}

