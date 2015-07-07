#include "GameOfNumbers.h"
#include "ActionEllipseItem.h"
#include <QDebug>
#include <QList>
#include <stdio.h>
#include "MainWindow.h"

/*************************************************************************
 *Description
 * Game of numbers. Player must click on the valid answers. There is
 * only one path.
 * ************************************************************************/
GameOfNumbers::GameOfNumbers() : turns(0) {
    qDebug() << "Creating game logicn\n";
}

GameOfNumbers::GameOfNumbers(MainWindow *mw)
    : mainWindowRef(mw)
{

}

void GameOfNumbers::checkConditions() {

    qDebug() << "Checking conditions...\n";
    if ( MainWindow::getItemByName("ActionEllipseItem100")->getClicked() ) {
        MainWindow::gameOver = true;
        //emit mainWindowRef->changedGameOver(); //fails with clang???
        mainWindowRef->emitChangedGameOver();
    }
    /* 0, 1, 5 also */
    /* TODO - REWORK THE LOGIC!!! */
#ifdef LOGICVER1
    if (
         (MainWindow::getItemByName("ActionEllipseItem8")->getCharacter() == "1" ||
          MainWindow::getItemByName("ActionEllipseItem0")->getCharacter() == "1")   &&
         (MainWindow::getItemByName("ActionEllipseItem2")->getCharacter() == "2" ||
          MainWindow::getItemByName("ActionEllipseItem1")->getCharacter() == "2")   &&
         (MainWindow::getItemByName("ActionEllipseItem4")->getCharacter() == "3" ||
          MainWindow::getItemByName("ActionEllipseItem5")->getCharacter() == "3" )&&
         MainWindow::getItemByName("ActionEllipseItem12")->getCharacter() == "4" &&
         MainWindow::getItemByName("ActionEllipseItem18")->getCharacter() == "5" &&
         MainWindow::getItemByName("ActionEllipseItem20")->getCharacter() == "6" &&
         MainWindow::getItemByName("ActionEllipseItem21")->getCharacter() == "7" &&
         MainWindow::getItemByName("ActionEllipseItem25")->getCharacter() == "8" &&
         MainWindow::getItemByName("ActionEllipseItem23")->getCharacter() == "9" &&
         MainWindow::getItemByName("ActionEllipseItem27")->getCharacter() == "10"&&
         MainWindow::getItemByName("ActionEllipseItem19")->getCharacter() == "11"&&
         MainWindow::getItemByName("ActionEllipseItem13")->getCharacter() == "12"&&
         MainWindow::getItemByName("ActionEllipseItem15")->getCharacter() == "13"&&
         MainWindow::getItemByName("ActionEllipseItem7")->getCharacter() ==  "14" &&
         MainWindow::getItemByName("ActionEllipseItem17")->getCharacter() == "15"&&
         MainWindow::getItemByName("ActionEllipseItem14")->getCharacter() == "16"&&
         MainWindow::getItemByName("ActionEllipseItem9")->getCharacter() ==  "17")
#else
    if ( MainWindow::getItemByName("ActionEllipseItem100")->getCharacter() == "18" ||
         MainWindow::getItemByName("ActionEllipseItem100")->getCharacter() == "20" ||
         MainWindow::getItemByName("ActionEllipseItem100")->getCharacter() == "22" )
#endif
        {
            qDebug() << "Winner";
            //now is the time for all good doers to come and aid their party
            mainWindowRef->setMoleWinner(true);
        } else {
            qDebug() << "Loser";
            mainWindowRef->setMoleWinner(false);
        }

}

void GameOfNumbers::getReport(ActionEllipseItem *it) {
    qDebug() << "Report get from: " << it->toString() << "\n";
    this->checkConditions();
}
bool GameOfNumbers::isWinner(ActionEllipseItem *el) {
    return el->isTheRightAnswer;
}

/*[TODO] observer here */
void GameOfNumbers::sendReport(GameOfNumbers *g, ActionEllipseItem *i) {
    qDebug() << "Report got from: " << i->toString() << "\n";
    /* check the report recieved */
    checkReport(i);
    checkConditions();
}

void GameOfNumbers::checkReport(ActionEllipseItem* reporter) {

}

void GameOfNumbers::setParentChildrenRelation() {
    MainWindow::getItemByName("ActionEllipseItem0")->addParent(NULL);
    MainWindow::getItemByName("ActionEllipseItem8")->addParent(NULL);

    MainWindow::getItemByName("ActionEllipseItem1")->addParent(
                MainWindow::getItemByName("ActionEllipseItem0"));
    MainWindow::getItemByName("ActionEllipseItem1")->addParent(
                MainWindow::getItemByName("ActionEllipseItem5"));
    MainWindow::getItemByName("ActionEllipseItem5")->addParent(
                MainWindow::getItemByName("ActionEllipseItem1"));

    MainWindow::getItemByName("ActionEllipseItem5")->addParent(
                MainWindow::getItemByName("ActionEllipseItem12"));
    MainWindow::getItemByName("ActionEllipseItem12")->addParent(
                MainWindow::getItemByName("ActionEllipseItem5"));

    MainWindow::getItemByName("ActionEllipseItem12")->addParent(
                MainWindow::getItemByName("ActionEllipseItem4"));
    MainWindow::getItemByName("ActionEllipseItem12")->addParent(
                MainWindow::getItemByName("ActionEllipseItem18"));
    MainWindow::getItemByName("ActionEllipseItem12")->addParent(
                MainWindow::getItemByName("ActionEllipseItem16"));

    MainWindow::getItemByName("ActionEllipseItem16")->addParent(
                MainWindow::getItemByName("ActionEllipseItem12"));
    MainWindow::getItemByName("ActionEllipseItem4")->addParent(
                MainWindow::getItemByName("ActionEllipseItem12"));
    MainWindow::getItemByName("ActionEllipseItem18")->addParent(
                MainWindow::getItemByName("ActionEllipseItem12"));

    MainWindow::getItemByName("ActionEllipseItem3")->addParent(
                MainWindow::getItemByName("ActionEllipseItem4"));

    MainWindow::getItemByName("ActionEllipseItem4")->addParent(
                MainWindow::getItemByName("ActionEllipseItem2"));
    MainWindow::getItemByName("ActionEllipseItem2")->addParent(
                MainWindow::getItemByName("ActionEllipseItem4"));

    MainWindow::getItemByName("ActionEllipseItem2")->addParent(
                MainWindow::getItemByName("ActionEllipseItem8"));

    MainWindow::getItemByName("ActionEllipseItem18")->addParent(
                MainWindow::getItemByName("ActionEllipseItem10"));
    MainWindow::getItemByName("ActionEllipseItem10")->addParent(
                MainWindow::getItemByName("ActionEllipseItem18"));

    MainWindow::getItemByName("ActionEllipseItem18")->addParent(
                MainWindow::getItemByName("ActionEllipseItem20"));
    MainWindow::getItemByName("ActionEllipseItem20")->addParent(
                MainWindow::getItemByName("ActionEllipseItem18"));

    MainWindow::getItemByName("ActionEllipseItem20")->addParent(
                MainWindow::getItemByName("ActionEllipseItem21"));
    MainWindow::getItemByName("ActionEllipseItem21")->addParent(
                MainWindow::getItemByName("ActionEllipseItem20"));

    MainWindow::getItemByName("ActionEllipseItem20")->addParent(
                MainWindow::getItemByName("ActionEllipseItem14"));
    MainWindow::getItemByName("ActionEllipseItem14")->addParent(
                MainWindow::getItemByName("ActionEllipseItem20"));

    MainWindow::getItemByName("ActionEllipseItem10")->addParent(
                MainWindow::getItemByName("ActionEllipseItem6"));
    MainWindow::getItemByName("ActionEllipseItem6")->addParent(
                MainWindow::getItemByName("ActionEllipseItem10"));

    MainWindow::getItemByName("ActionEllipseItem6")->addParent(
                MainWindow::getItemByName("ActionEllipseItem9"));
    MainWindow::getItemByName("ActionEllipseItem9")->addParent(
                MainWindow::getItemByName("ActionEllipseItem6"));

    MainWindow::getItemByName("ActionEllipseItem9")->addParent(
                MainWindow::getItemByName("ActionEllipseItem14"));
    MainWindow::getItemByName("ActionEllipseItem14")->addParent(
                MainWindow::getItemByName("ActionEllipseItem9"));

    MainWindow::getItemByName("ActionEllipseItem14")->addParent(
                MainWindow::getItemByName("ActionEllipseItem20"));
    MainWindow::getItemByName("ActionEllipseItem20")->addParent(
                MainWindow::getItemByName("ActionEllipseItem14"));

    MainWindow::getItemByName("ActionEllipseItem14")->addParent(
                MainWindow::getItemByName("ActionEllipseItem17"));
    MainWindow::getItemByName("ActionEllipseItem17")->addParent(
                MainWindow::getItemByName("ActionEllipseItem14"));

    MainWindow::getItemByName("ActionEllipseItem17")->addParent(
                MainWindow::getItemByName("ActionEllipseItem7"));
    MainWindow::getItemByName("ActionEllipseItem7")->addParent(
                MainWindow::getItemByName("ActionEllipseItem17"));

    MainWindow::getItemByName("ActionEllipseItem7")->addParent(
                MainWindow::getItemByName("ActionEllipseItem15"));
    MainWindow::getItemByName("ActionEllipseItem15")->addParent(
                MainWindow::getItemByName("ActionEllipseItem7"));

    MainWindow::getItemByName("ActionEllipseItem15")->addParent(
                MainWindow::getItemByName("ActionEllipseItem13"));
    MainWindow::getItemByName("ActionEllipseItem13")->addParent(
                MainWindow::getItemByName("ActionEllipseItem15"));

    MainWindow::getItemByName("ActionEllipseItem15")->addParent(
                MainWindow::getItemByName("ActionEllipseItem23"));
    MainWindow::getItemByName("ActionEllipseItem23")->addParent(
                MainWindow::getItemByName("ActionEllipseItem15"));

    MainWindow::getItemByName("ActionEllipseItem13")->addParent(
                MainWindow::getItemByName("ActionEllipseItem19"));
    MainWindow::getItemByName("ActionEllipseItem19")->addParent(
                MainWindow::getItemByName("ActionEllipseItem13"));

    MainWindow::getItemByName("ActionEllipseItem19")->addParent(
                MainWindow::getItemByName("ActionEllipseItem23"));
    MainWindow::getItemByName("ActionEllipseItem23")->addParent(
                MainWindow::getItemByName("ActionEllipseItem19"));

    MainWindow::getItemByName("ActionEllipseItem23")->addParent(
                MainWindow::getItemByName("ActionEllipseItem27"));
    MainWindow::getItemByName("ActionEllipseItem27")->addParent(
                MainWindow::getItemByName("ActionEllipseItem23"));

    MainWindow::getItemByName("ActionEllipseItem27")->addParent(
                MainWindow::getItemByName("ActionEllipseItem30"));
    MainWindow::getItemByName("ActionEllipseItem30")->addParent(
                MainWindow::getItemByName("ActionEllipseItem27"));

    MainWindow::getItemByName("ActionEllipseItem30")->addParent(
                MainWindow::getItemByName("ActionEllipseItem28"));
    MainWindow::getItemByName("ActionEllipseItem28")->addParent(
                MainWindow::getItemByName("ActionEllipseItem30"));

    MainWindow::getItemByName("ActionEllipseItem30")->addParent(
                MainWindow::getItemByName("ActionEllipseItem29"));
    MainWindow::getItemByName("ActionEllipseItem29")->addParent(
                MainWindow::getItemByName("ActionEllipseItem30"));

    MainWindow::getItemByName("ActionEllipseItem29")->addParent(
                MainWindow::getItemByName("ActionEllipseItem24"));
    MainWindow::getItemByName("ActionEllipseItem24")->addParent(
                MainWindow::getItemByName("ActionEllipseItem29"));

    MainWindow::getItemByName("ActionEllipseItem24")->addParent(
                MainWindow::getItemByName("ActionEllipseItem28"));
    MainWindow::getItemByName("ActionEllipseItem28")->addParent(
                MainWindow::getItemByName("ActionEllipseItem24"));

    MainWindow::getItemByName("ActionEllipseItem24")->addParent(
                MainWindow::getItemByName("ActionEllipseItem22"));
    MainWindow::getItemByName("ActionEllipseItem22")->addParent(
                MainWindow::getItemByName("ActionEllipseItem24"));

    MainWindow::getItemByName("ActionEllipseItem24")->addParent(
                MainWindow::getItemByName("ActionEllipseItem25"));
    MainWindow::getItemByName("ActionEllipseItem25")->addParent(
                MainWindow::getItemByName("ActionEllipseItem24"));

    MainWindow::getItemByName("ActionEllipseItem21")->addParent(
                MainWindow::getItemByName("ActionEllipseItem22"));
    MainWindow::getItemByName("ActionEllipseItem22")->addParent(
                MainWindow::getItemByName("ActionEllipseItem21"));

    MainWindow::getItemByName("ActionEllipseItem21")->addParent(
                MainWindow::getItemByName("ActionEllipseItem25"));
    MainWindow::getItemByName("ActionEllipseItem25")->addParent(
                MainWindow::getItemByName("ActionEllipseItem21"));

    MainWindow::getItemByName("ActionEllipseItem25")->addParent(
                MainWindow::getItemByName("ActionEllipseItem23"));
    MainWindow::getItemByName("ActionEllipseItem23")->addParent(
                MainWindow::getItemByName("ActionEllipseItem25"));

    MainWindow::getItemByName("ActionEllipseItem25")->addParent(
                MainWindow::getItemByName("ActionEllipseItem26"));
    MainWindow::getItemByName("ActionEllipseItem26")->addParent(
                MainWindow::getItemByName("ActionEllipseItem25"));

    MainWindow::getItemByName("ActionEllipseItem26")->addParent(
                MainWindow::getItemByName("ActionEllipseItem28"));
    MainWindow::getItemByName("ActionEllipseItem28")->addParent(
                MainWindow::getItemByName("ActionEllipseItem26"));

    MainWindow::getItemByName("ActionEllipseItem26")->addParent(
                MainWindow::getItemByName("ActionEllipseItem30"));
    MainWindow::getItemByName("ActionEllipseItem30")->addParent(
                MainWindow::getItemByName("ActionEllipseItem26"));


    MainWindow::getItemByName("ActionEllipseItem16")->addParent(
                MainWindow::getItemByName("ActionEllipseItem11"));
    MainWindow::getItemByName("ActionEllipseItem11")->addParent(
                MainWindow::getItemByName("ActionEllipseItem16"));

    MainWindow::getItemByName("ActionEllipseItem10")->addParent(
                MainWindow::getItemByName("ActionEllipseItem11"));
    MainWindow::getItemByName("ActionEllipseItem11")->addParent(
                MainWindow::getItemByName("ActionEllipseItem10"));

    MainWindow::getItemByName("ActionEllipseItem27")->addParent(
                MainWindow::getItemByName("ActionEllipseItem19"));
    MainWindow::getItemByName("ActionEllipseItem19")->addParent(
                MainWindow::getItemByName("ActionEllipseItem27"));


    MainWindow::getItemByName("ActionEllipseItem100")->addParent(
                MainWindow::getItemByName("ActionEllipseItem9"));

}

void GameOfNumbers::createWinningNumbers(QList<ActionEllipseItem*>* listItems) {
    /* set the winning items */
    /* BLAAAGH - BUG!!!! */
    qDebug() <<"Setting winning items...\n";

    if ( MainWindow::getItemByName("ActionEllipseItem27")->getClicked() &&
         !MainWindow::getItemByName("ActionEllipseItem30")->getClicked() &&
         MainWindow::getItemByName("ActionEllipseItem23")->getClicked() )
    {
        MainWindow::getItemByName("ActionEllipseItem27")->isTheRightAnswer=true;
    }
    if ( MainWindow::getItemByName("ActionEllipseItem13")->getClicked() &&
         !MainWindow::getItemByName("ActionEllipseItem19")->getClicked() &&
         MainWindow::getItemByName("ActionEllipseItem23")->getClicked() )
    {
        MainWindow::getItemByName("ActionEllipseItem13")->isTheRightAnswer = true;

    }


}

void GameOfNumbers::increaseTurns() {
    turns++;
}
int GameOfNumbers::getTurns() {
    return turns;
}



GameOfNumbers::~GameOfNumbers(){}
