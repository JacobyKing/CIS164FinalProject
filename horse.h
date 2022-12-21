/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#ifndef HORSE_H
#define HORSE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Horse : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Horse(QPixmap firstPosition, QPixmap secondPosition, int speed);
public slots:
    void move();

    void updatePixmap();

    void startTimers();
signals:
    void finishRace();
private:
    QPixmap firstPosition;
    QPixmap secondPosition;
    int speed;
    QTimer * horseImageTimer;
    QTimer * horseMovementTimer;
    bool horseImagePosition;
};

#endif // HORSE_H
