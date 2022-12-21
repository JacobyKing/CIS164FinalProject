/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#include "slot.h"

//Slot object constructor
Slot::Slot()
{
    //Setting the Slot object to the first QPixmap position
    slotPosition = 0;
    setPixmap(chipPosition);
    //Initializing and connecting the slotPositionTimer to the updatePixmap() slot
    slotPositionTimer = new QTimer();
    connect(slotPositionTimer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
}

//Slot, used to update the Pixmap of the object
void Slot::updatePixmap()
{
    //If the slotPosition equals zero, that means it is currently at chipPosition, therefor change it to coinPosition and adjust the slotPosition
    if(slotPosition == 0){
        setPixmap(coinPosition);
        slotPosition = 1;
    }
    //If the slotPosition equals one, that means it is currently at coinPosition, therefor change it to dicePosition and adjust the slotPosition
    else if(slotPosition == 1){
        setPixmap(dicePosition);
        slotPosition = 2;
    }
    //If the slotPosition equals 2, that means it is currently at dicePosition, therefor change it to chipPosition and adjust the slotPosition
    else if(slotPosition == 2){
        setPixmap(chipPosition);
        slotPosition = 0;
    }
}

//Called for each Slot when the slot machine is spun, starts slotPositionTimer
void Slot::startSlot()
{
    slotPositionTimer->start(85);
}

//Called for each Slot when the slot machine is spun after a delay, stops slotPositionTimer
void Slot::stopSlot()
{
    slotPositionTimer->stop();
}

//Called when there is a win, updates the Pixmap
void Slot::win()
{
    setPixmap(winPosition);
}
