#include "ZooGame.h"
#include "ActionItem.h"
#include <qdebug.h>


using namespace zoogame;


Swap::Swap() { }
Swap::~Swap() { }

Animal::Animal() { }
Animal::~Animal() { }

Cell::Cell() { }
Cell::~Cell() {
    delete animal;
}

Cell::Cell(QString cn, QString an, int p, Cell* l, Cell* r) :
    animalName(an), cellName(cn), position(p), isFree(false), left(l), right(r) /* by default all are occupied
                                                                 set the Swap to be free in
                                                                 game construction */
{
    qDebug()<<  "Created cell.." << cellName;
}


ZooGame::ZooGame()
{

}

ZooGame::ZooGame(MainWindow *mw) : mainWindowRef(mw)
{
    qDebug() << "Created Zoo game";

}

ZooGame::~ZooGame()
{

}

void ZooGame::getReportFrom(ActionItem *ai)
{
    qDebug() << "[ZooGame says:] I got report from " << ((ActionItem*)ai)->toString();
}

void ZooGame::sendReportTo(ActionItem *ai)
{

}

void ZooGame::checkReport(ActionItem *ai)
{
    qDebug() << "[ZooGame says:] Cell: " <<
                 ai->getCell()->cellName <<
                 "Animal: " << ai->getCell()->animalName
              << "Position: " << ai->getCell()->position;

}

bool ZooGame::isWinner(ActionItem *ai)
{
    return this->winningCondition;
}

void ZooGame::setCell(QString n, QString cell, int pos, int index)
{

}


void ZooGame::checkWinningCondition()
{

}

void ZooGame::moveToSwap(Cell* c) {
    qDebug() << c->animalName << " went to swap zone...";

}

bool ZooGame::canMoveToSwap(Cell* c) {

}

bool ZooGame::canMoveToCell(Cell* c) {
    return true;
}

void ZooGame::openCell(Cell *c)
{


}

Cell *ZooGame::getOpenedCell()
{

}

void ZooGame::setCellsRelation()
{

}
