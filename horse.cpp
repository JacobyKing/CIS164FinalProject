/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#include "horse.h"

//Horse object constructor, takes in the different QPixmaps and speed since the Horses have different colors and speeds
Horse::Horse(QPixmap firstPosition, QPixmap secondPosition, int speed)
{
    //Setting the Horse object to the first QPixmap position
    horseImagePosition = 0;
    setPixmap(firstPosition);
    //Setting attributes
    this->speed = speed;
    this->firstPosition = firstPosition;
    this->secondPosition = secondPosition;
    //Initializing and connecting the horseImageTimer to the updatePixmap() slot
    horseImageTimer = new QTimer();
    connect(horseImageTimer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
    //Initializing and connecting the horseMovementTimer to the move() slot
    horseMovementTimer = new QTimer();
    connect(horseMovementTimer, SIGNAL(timeout()), this, SLOT(move()));
}

//Slot, used to update the position of the Horse on the QGraphicsView scene everytime the horseMovementTimer iterates
void Horse::move()
{
    //If the Horse is not at the edge of the view
    if(x() < 540){
        //Change x position by the current x pos + speed
        setPos(x() + speed, y());
    }
    else{
        //If the Horse is at the edge of the view, stop movement and image timers
        horseImageTimer->stop();
        horseMovementTimer->stop();
        //Emits a signal to the widget when whichever Horse it is connected to (the slowest) reaches the end
        emit finishRace();
    }
}

//Slot, used to update the Pixmap of the object
void Horse::updatePixmap()
{
    //If the horseImagePosition is true, that means it is in the secondPosition, therefor change it to the firstPosition and make horseImagePosition false
    if(horseImagePosition){
        setPixmap(firstPosition);
        horseImagePosition = 0;
    }
    //If the horseImagePosition is false, that means it is in the firstPosition, therefor change it to the secondPosition and make horseImagePosition true
    else{
        setPixmap(secondPosition);
        horseImagePosition = 1;
    }
}

//Called for each Horse object when the race begins, starts slot connected Horse timers
void Horse::startTimers()
{
    //Animates Horse object
    horseImageTimer->start(180);
    //Moves Horse object
    horseMovementTimer->start(100);
}
