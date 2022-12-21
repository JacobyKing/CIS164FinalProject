/* Jacoby King
 * 11/08/2022
 * CIS164 Final Project
 */
#include "widget.h"
#include "ui_widget.h"

//Helper functions

//Method to delay the program but not events. Used for delaying the stops between the slots
void delay(int time)
{
    if(time == 0){
        time = (rand() % 3) + 1;
    }
    QTime endTime = QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < endTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//Function used for the random_shuffle method used to shuffle the vector
int randomFunc(int j){
    return rand() % j;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    scene = new QGraphicsScene(this);
    //Setting srand so we can get random
    srand(unsigned(time(0)));
    //Setting sceneRect for size of graphicsViews
    scene->setSceneRect(-729.5, -304, 1459, 608);
}

Widget::~Widget()
{
    delete ui;
}

//StartPage button to gameSelectionPage
void Widget::on_toPage2Button1_clicked()
{
    setGameSelectionPage();
}

//GameSelectionPage button to horseRacing
void Widget::on_toHorseRacingButton2_clicked()
{
    setHorseRacingPage();
}

//GameSelectionPage to slotMachine
void Widget::on_toSlotsButton2_clicked()
{
    setSlotPage();
}

//GameSelectionPage to endPage
void Widget::on_quitButton2_clicked()
{
    //If the played has played one of the mini games, they may go to the endPage
    if(gamePlayed){
        setEndPage();
    }
    //If the player has not played a mini game yet, display a message saying as much in red
    else{
        ui->gameResultLabel2->setText("User Must Bet No Less Than One Time Before Quitting");
        ui->gameResultLabel2->setStyleSheet("color : rgb(255, 0, 0);");
    }

}

//HorseRacingPage button, start race
void Widget::on_raceButton3_clicked()
{
    //If the button has not been clicked yet
    if(!gameStarted){
        //Setting gameStarted to true so that this cannot be run again with a new horse selection or bet until the page is reloaded
        gameStarted = true;
        //Getting bet info from user input
        selectedHorse = ui->horseSelectionBox3->currentText();
        betAmount = ui->betSelectionBox3->value();
        //Starting movement and position timers for Horse objects
        blackHorse->startTimers();
        whiteHorse->startTimers();
        blueHorse->startTimers();
        yellowHorse->startTimers();
    }
}

//SlotMachinePage button, spin Slots
void Widget::on_spinButton4_clicked()
{
    //If button has not been clicked yet
    if(!gameStarted){
        //Setting gameStarted to true so that this cannot be run again with a new bet until the page is reloaded
        gameStarted = true;
        //Getting bet info from user input
        betAmount = ui->betSelectionBox4->value();
        //Starting position timer for Slot objects
        firstSlot->startSlot();
        secondSlot->startSlot();
        thirdSlot->startSlot();
        //Setting a delay of anywhere from 1-3 seconds before stopping the first slot
        delay(0);
        firstSlot->stopSlot();
        //Setting a delay of anywhere from 1-3 seconds before stopping the second slot
        delay(0);
        secondSlot->stopSlot();
        //Setting a delay of anywhere from 1-3 seconds before stopping the third slot
        delay(0);
        thirdSlot->stopSlot();
        //Getting spin result and changing the cashAmount accordingly and display on gameSelectionPage
        if((firstSlot->pixmap() == secondSlot->pixmap()) && (secondSlot->pixmap() == thirdSlot->pixmap())){
            cashAmount += betAmount * 5;
            displayWon("Slots", 5);
            //Displaying the 'winPosition' Pixmap
            firstSlot->win();
            secondSlot->win();
            thirdSlot->win();
        }
        //If the user did not win, change cashAmount accordingly and display on gameSelectionPage
        else{
            cashAmount -= betAmount;
            displayLost("Slots");

        }
        //Showing the user the result of the spin for 1 second before going back to the selection page
        delay(1);
        //If the player still has money
        if(cashAmount > 0){
            //Going back to the selection page
            setGameSelectionPage();
        }
        else{
            //Going to the end page, since the player has no money
            setEndPage();
        }
        //Deleting the Slot objects from the scene
        delete firstSlot;
        delete secondSlot;
        delete thirdSlot;
        //Setting gamePlayed to true so the program knows that the player has played at least one game, they may now use the quit button
        if(!gamePlayed){
            gamePlayed = true;
        }
    }
}

//EndPage button, exits the program
void Widget::on_endButton5_clicked()
{
    exit(0);
}

//Slot, to be triggered when the selected horse reaches the end
void Widget::raceEnd()
{
    //Finding the Horse that had the fastest speed in the vector and comparing that to the user selectedHorse. Changing cashAmount accordingly and displaying results on gameSelectionPage
    if(selectedHorse == "Black"){
        if(uniqueSpeeds[0] == 18){
            cashAmount += betAmount * 2;
            displayWon("Horse Racing", 2);
        }
        else{
            cashAmount -= betAmount;
            displayLost("Horse Racing");
        }
    }
    else if(selectedHorse == "White"){
        if(uniqueSpeeds[1] == 18){
            cashAmount += betAmount * 2;
            displayWon("Horse Racing", 2);
        }
        else{
            cashAmount -= betAmount;
            displayLost("Horse Racing");
        }
    }
    else if(selectedHorse == "Blue"){
        if(uniqueSpeeds[2] == 18){
            cashAmount += betAmount * 2;
            displayWon("Horse Racing", 2);
        }
        else{
            cashAmount -= betAmount;
            displayLost("Horse Racing");
        }
    }
    else if(selectedHorse == "Yellow"){
        if(uniqueSpeeds[3] == 18){
            cashAmount += betAmount * 2;
            displayWon("Horse Racing", 2);
        }
        else{
            cashAmount -= betAmount;
            displayLost("Horse Racing");
        }
    }
    //If the player still has money
    if(cashAmount > 0){
        //Going back to the selection page
        setGameSelectionPage();
    }
    else{
        //Going to the end page, since the player has no money
        setEndPage();
    }
    //Deleting the Horse objects from the scene
    delete blackHorse;
    delete whiteHorse;
    delete blueHorse;
    delete yellowHorse;
    //Setting gamePlayed to true so the program knows that the player has played at least one game, they may now use the quit button
    if(!gamePlayed){
        gamePlayed = true;
    }
}

//Helper methods of the Widget class

//Sets gameSelectionPage
void Widget::setGameSelectionPage()
{
    //Setting the current widget to the gameSelectionPage with an updated cashAmount
    ui->stackedWidget->setCurrentWidget(ui->gameSelectionPage);
    ui->currentStandingLabel2->setText("Current Standing: $" + QLocale(QLocale::English).toString(cashAmount));
    //Resets the gameStarted variable so a new game can be loaded and started
    gameStarted = false;
}

//Sets horseRacingPage
void Widget::setHorseRacingPage()
{
    //Setting the current widget to the horseRacingPage with an updated betSelectionBox maximum
    ui->stackedWidget->setCurrentWidget(ui->horseRacingPage);
    ui->betSelectionBox3->setMaximum(cashAmount);
    //Shuffling the contents of the uniqueSpeeds vector, so each Horse object has a random and unique speed
    random_shuffle(uniqueSpeeds.begin(), uniqueSpeeds.end(), randomFunc);
    //Initializing each Horse and their QPixmaps, speeds, and positions before adding them to the scene
    blackHorse = new Horse(QPixmap(":/Images/black_horse_first_position.png"), QPixmap(":/Images/black_horse_second_position.png"), uniqueSpeeds[0]);
    blackHorse->setPos(-729, -325);
    scene->addItem(blackHorse);
    whiteHorse = new Horse(QPixmap(":/Images/white_horse_first_position.png"), QPixmap(":/Images/white_horse_second_position.png"), uniqueSpeeds[1]);
    whiteHorse->setPos(-729, -175);
    scene->addItem(whiteHorse);
    blueHorse = new Horse(QPixmap(":/Images/blue_horse_first_position.png"), QPixmap(":/Images/blue_horse_second_position.png"), uniqueSpeeds[2]);
    blueHorse->setPos(-729, -25);
    scene->addItem(blueHorse);
    yellowHorse = new Horse(QPixmap(":/Images/yellow_horse_first_position.png"), QPixmap(":/Images/yellow_horse_second_position.png"), uniqueSpeeds[3]);
    yellowHorse->setPos(-729, 125);
    scene->addItem(yellowHorse);
    //Connecting raceEnd slot to the slowest Horse object
    if(uniqueSpeeds[0] == 15){
        connect(blackHorse, &Horse::finishRace, this, &Widget::raceEnd);
    }
    else if(uniqueSpeeds[1] == 15){
        connect(whiteHorse, &Horse::finishRace, this, &Widget::raceEnd);
    }
    else if(uniqueSpeeds[2] == 15){
        connect(blueHorse, &Horse::finishRace, this, &Widget::raceEnd);
    }
    else if(uniqueSpeeds[3] == 15){
        connect(yellowHorse, &Horse::finishRace, this, &Widget::raceEnd);
    }
    //Setting the scene of the horseRaceView to our scene with the Horse objects
    ui->horseRaceView3->setScene(scene);
}

//Sets slotPage
void Widget::setSlotPage()
{
    //Setting the current widget to the slotMachinePage with an updated betSelectionBox maximum
    ui->stackedWidget->setCurrentWidget(ui->slotMachinePage);
    ui->betSelectionBox4->setMaximum(cashAmount);
    //Initializing each Slot objects and their positions before adding them to the scene
    firstSlot = new Slot();
    firstSlot->setPos(-550, -185);
    scene->addItem(firstSlot);
    secondSlot = new Slot();
    secondSlot->setPos(-165, -185);
    scene->addItem(secondSlot);
    thirdSlot = new Slot();
    thirdSlot->setPos(220, -185);
    scene->addItem(thirdSlot);
    //Setting the scene of the slotMachineView to our scene with the Slot objects
    ui->slotMachineView4->setScene(scene);
}

//Sets endPage
void Widget::setEndPage()
{
    //Setting the current widget to the endPage
    ui->stackedWidget->setCurrentWidget(ui->endPage);
    //If the player ends the game with less money than started with, set labels accordingly
    if(cashAmount < START_AMOUNT){
        ui->endLabel5->setText("Too Bad!");
        ui->finalCashScoreLabel5->setText("$" + QLocale(QLocale::English).toString(cashAmount));
        ui->finalProfitLabel5->setText("Final Loss Amount:");
        ui->finalProfitScoreLabel5->setText("- $" + QLocale(QLocale::English).toString(-(cashAmount - START_AMOUNT)));
    }
    //Else, set labels accordingly
    else{
        ui->endLabel5->setText("Congrats!");
        ui->finalCashScoreLabel5->setText("$" + QLocale(QLocale::English).toString(cashAmount));
        ui->finalProfitLabel5->setText("Final Profit Amount:");
        ui->finalProfitScoreLabel5->setText("$" + QLocale(QLocale::English).toString((cashAmount - START_AMOUNT)));
    }
}

//Sets the label on gameSelectPage if previous game won
void Widget::displayWon(QString game, int multiplyer)
{
    //Displaying to the user that they won on the gameSelectionPage
    ui->gameResultLabel2->setText("Congrats! You Won $" + QLocale(QLocale::English).toString((betAmount * multiplyer)) + " From " + game + ".");
    ui->gameResultLabel2->setStyleSheet("color : rgb(0, 255, 0);");
}

//Sets the label on gameSelectPage if previous game lost
void Widget::displayLost(QString game)
{
    //Displaying to the user that they lost on the gameSelectionPage
    ui->gameResultLabel2->setText("Too Bad! You Lost $" + QLocale(QLocale::English).toString(betAmount) + " From " + game + ".");
    ui->gameResultLabel2->setStyleSheet("color : rgb(255, 0, 0);");
}
