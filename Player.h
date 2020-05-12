#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>


class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:


    Player(QGraphicsItem * parent=nullptr);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void setVelocity(double vel);

signals:
    void needNewPlatform();

public slots:

    void fall();
    void action();
    void generatePlatform();

private:
    double velocity;
    int agility;
    //QGraphicsItem* last_platform;
    QGraphicsItem* curr_platform;
    double highest_platform_height;
    //double last_platform_height;
    bool key_right_pressed;
    bool key_left_pressed;
    bool key_up_pressed;
    bool need_new_platform;

};

#endif // PLAYER_H
