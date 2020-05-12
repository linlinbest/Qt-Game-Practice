#include <QKeyEvent>
#include <QTimer>
#include "Player.h"
#include "Game.h"

#include <QDebug>

extern Game * game; // there is an external global object called game
//it's used to get timer1 and timer2 so that the velovity can be calculated.

Player::Player(QGraphicsItem * parent): QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/player_right.png"));
    velocity = 0.0;
    key_right_pressed = false;
    key_left_pressed = false;
    key_up_pressed = false;
    need_new_platform = true;

    highest_platform_height = SCENE_HEIGHT-100;
    curr_platform = nullptr;
    agility = 5;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        key_up_pressed = true;
        setPixmap(QPixmap(":/images/player_up.png"));
    }
    if (event->key() == Qt::Key_Left){
        key_left_pressed = true;
        if (!key_up_pressed) setPixmap(QPixmap(":/images/player_left.png"));
    }
    if (event->key() == Qt::Key_Right){
        key_right_pressed = true;
        if (!key_up_pressed) setPixmap(QPixmap(":/images/player_right.png"));
    }
    if (event->key() == Qt::Key_Space) {
        setVelocity(JUMP);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left){
        key_left_pressed = false;
    }
    if (event->key() == Qt::Key_Right){
        key_right_pressed = false;
    }
    if (event->key() == Qt::Key_Up){
        key_up_pressed = false;
    }

}

//physics applied on a player
void Player::fall() {
    setPos(x(),y()+velocity*TIME_INTERVAL/1000);
    velocity += GRAVITY*TIME_INTERVAL/1000;
    //qDebug() << velocity;

    //TODO: jump only when the player touches the top of the platform

    if (velocity >= 0.0) {
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(StdPlatform)) {
                setVelocity(JUMP);
                curr_platform = colliding_items[i];
                break;
            }
        }
    }




    QList<QGraphicsItem *> all_items = game->scene->items();
    if (curr_platform!=nullptr && curr_platform->y()+20<SCENE_HEIGHT-100) {
        highest_platform_height += 20;
        for (int i = 0, n = all_items.size(); i < n; ++i){
            all_items[i]->moveBy(0,20);
            if (all_items[i]->y() > SCENE_HEIGHT) delete all_items[i];

            //qDebug() << (all_items[i]->y()) << "," << y() << new_platform_height;
        }
    }


    if (curr_platform!=nullptr&& curr_platform->y()<=highest_platform_height) {
        generatePlatform();
    }



}

void Player::action() {
    if (key_left_pressed){
        setPos(x()-agility,y());
    }
    if (key_right_pressed){
        setPos(x()+agility,y());
    }
    if (key_up_pressed){
        setPos(x(),y()-agility);
    }
}

void Player::generatePlatform() {
    StdPlatform* new_platform = new StdPlatform();

    int rand_x = rand() % (SCENE_WIDTH-80); //80(px) is the width of the platform

    //not % 150, need to calculate the maximum range the player can reach
    int rand_h;
    while ((rand_h=rand()%150) < 80); //max 150px, min 80px
    highest_platform_height = highest_platform_height - rand_h;
    new_platform->setPos(rand_x,highest_platform_height);

    //qDebug() << rand_h << "," << highest_platform_height;

    game->scene->addItem(new_platform);
}



void Player::setVelocity(double vel) {
    velocity = vel;
}

