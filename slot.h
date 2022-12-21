/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#ifndef SLOT_H
#define SLOT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Slot : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Slot();
public slots:
    void updatePixmap();

    void startSlot();

    void stopSlot();

    void win();
signals:
private:
    QPixmap chipPosition = QPixmap(":/Images/slot-machine-chip.png");
    QPixmap coinPosition = QPixmap(":/Images/slot-machine-coin.png");
    QPixmap dicePosition = QPixmap(":/Images/slot-machine-dice.png");
    QPixmap winPosition = QPixmap(":/Images/slot-machine-win.png");
    int slotPosition;
    QTimer * slotPositionTimer;
};

#endif // SLOT_H
