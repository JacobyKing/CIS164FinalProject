/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#ifndef WIDGET_H
#define WIDGET_H

#define START_AMOUNT 1000

#include "horse.h"
#include "slot.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

    void setGameSelectionPage();

    void setHorseRacingPage();

    void setSlotPage();

    void setEndPage();

    void displayWon(QString game, int multiplyer);

    void displayLost(QString game);
private slots:
    void on_toPage2Button1_clicked();

    void on_toHorseRacingButton2_clicked();

    void on_toSlotsButton2_clicked();

    void on_quitButton2_clicked();

    void on_raceButton3_clicked();

    void raceEnd();

    void on_spinButton4_clicked();

    void on_endButton5_clicked();
private:
    int cashAmount = START_AMOUNT;
    Horse * blackHorse;
    Horse * whiteHorse;
    Horse * blueHorse;
    Horse * yellowHorse;
    Slot * firstSlot;
    Slot * secondSlot;
    Slot * thirdSlot;
    QGraphicsScene * scene;
    bool gameStarted = false;
    bool gamePlayed = false;
    std::vector<int> uniqueSpeeds = {15, 16, 17, 18};
    QString selectedHorse;
    int betAmount;
    Ui::Widget *ui;
};
#endif // WIDGET_H
