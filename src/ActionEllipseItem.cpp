#include "ActionEllipseItem.h"
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPoint>
#include <QFont>
#include <stdlib.h>

#include "MainWindow.h"
#include "Callbacks.h"
#include "FModePlayer.h"
/*************************************************************************
 * TODO add description
 *
 *
 *
 * ************************************************************************/
ActionEllipseItem::~ActionEllipseItem() {
    delete functors;
    delete player;
}

ActionEllipseItem::ActionEllipseItem() {

}

ActionEllipseItem* ActionEllipseItem::getSelf() {
    return this;
}
void ActionEllipseItem::setVal(int v) {
    value = v;
}
//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void ActionEllipseItem::addChild(ActionEllipseItem *ai)
{
    if ( ai == NULL ) children = NULL;
    else children->append(ai);
}

void ActionEllipseItem::addParent(ActionEllipseItem *pa)
{
    if ( pa == NULL )  parent = NULL;
    else parent->append(pa);
}

QList<ActionEllipseItem*> *ActionEllipseItem::getParents()
{
    return parent;
}

ActionEllipseItem* ActionEllipseItem::getChildAt(int i) {

    if ( children->at(i) == NULL ) return NULL;
    else return children->at(i);

}

ActionEllipseItem* ActionEllipseItem::getParentAt(int i){
    if ( parent->at(i) == NULL ) return NULL;
    else return parent->at(i);
}

ActionEllipseItem* ActionEllipseItem::getChildByName(QString n) {
    int i=0;
    while ( i < children->size()  ) {
        if ( children->at(i)->toString() == n ) return children->at(i);
        i++;
    }
    return NULL;
}

ActionEllipseItem* ActionEllipseItem::getParentByName(QString n) {
    int i=0;
    while ( i < parent->size()  ) {
        if ( parent->at(i)->toString() == n ) return parent->at(i);
        i++;
    }
    return NULL;
}

QList<ActionEllipseItem*>* ActionEllipseItem::getChildren()
{
    return children;
}

bool ActionEllipseItem::hasChildren() {
    int i=0;
    ActionEllipseItem* test;
    while ( i++ < children->size() ) test = children->at(i);
    if ( test == NULL ) return false;
    else return true;
}

bool ActionEllipseItem::hasParents() {
    int i=0;
    ActionEllipseItem* test;
    while ( i++ < parent->size() ) test = parent->at(i);
    if ( test == NULL ) return false;
    else return true;
}

void ActionEllipseItem::reportParentChildrenStatus()
{
    int i=0;
    if ( parent != NULL ) {
        while ( i < parent->size()) {
            qDebug()<< "Parents:" << parent->at(i)->toString();
            i++;
        }
    }
    i=0;
    while ( i < children->size()) {
        qDebug()<<"Children: " << children->at(i)->toString();
        i++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
ActionEllipseItem::ActionEllipseItem(int x, int y, int w, int h,bool istra,
                                     QString name,
                                     int id, MainWindow* pw,
                                     QGraphicsScene* sc,
                                     GameOfNumbers* ref,
                                     FMPlayer* pl,
                                     Callbacks* cbs)
    :xcoord(x),ycoord(y),width(w),height(h),
      parentW(pw),gameLogicRef(ref), __name(name), __privateId(id),
      scene(sc), clicked(false), value(0), player(pl), functors(cbs)
 {
    /* TODO implement Callbacks */
    /* TODO register reporter and reciever */
    isTheRightAnswer = false;
    __name.append(QString::number(__privateId));
    children = new QList<ActionEllipseItem*>();
    parent = new QList<ActionEllipseItem*>();
 }
void ActionEllipseItem::drawEllipseItem() {
    setRect(xcoord-(width/2), ycoord-(height/2), width, height);
    setPen(QPen(QColor(0,0,0,0)));
}

void ActionEllipseItem::setX(int x)
{
    xcoord = x;
}
void ActionEllipseItem::setY(int y) {
    ycoord = y;
}

int ActionEllipseItem::getX() {
    return xcoord;
}
int ActionEllipseItem::getY() {
    return ycoord;
}

int ActionEllipseItem::getWidth()
{
    return width;
}
int ActionEllipseItem::getHeight() {
    return height;
}
void ActionEllipseItem::setWidth(int w) {
    width = w;
}
void ActionEllipseItem::setHeight(int h) {
    height = h;
}

FMPlayer *ActionEllipseItem::getPlayer()
{
    return player;
}

QString& ActionEllipseItem::toString() {

    return __name;
}


void ActionEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    functors->onMouse(event, this);
    //logic moved to the callbacks
    //save commented code for backup
    /*
    if ( !clicked ) {
        qDebug() << "Custom ActionItem clicked\n";
        qDebug() << "Item`s toString():" << this->toString() << "\n";
        this->setBrush(QBrush(QColor(255,255,0,150)));
        QPixmap pix(100, 50);
        QPainter painter(&pix);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::blue);
        QFont font = painter.font();
        font.setPointSize(12);
        painter.setFont(font);
       // char c = TextNodes::getNextDigit();
        QGraphicsTextItem* txt = scene->
                addText(TextNodes::getNextDigit2(), font);
        txt->setPos(QPointF(xcoord-(width/4), ycoord-(height/4) ));
        clicked = true;
        reportToGameLogic(gameLogicRef, this);
    } else {
        //do nothing
    } */
}

void ActionEllipseItem::setCharacterFromString(QString& s)
{
    character = s;
}

QString ActionEllipseItem::getCharacter()
{
    return character;
}

QGraphicsScene *ActionEllipseItem::getScene()
{
    return scene;
}

bool ActionEllipseItem::getClicked()
{
    return clicked;
}

void ActionEllipseItem::setClicked(bool c)
{
    clicked = c;
}

void ActionEllipseItem::reportToGameLogic(GameOfNumbers *gl, ActionEllipseItem *ai) {
    gameLogicRef->sendReport(gameLogicRef, this);
}

GameOfNumbers* ActionEllipseItem::getGameLogic() {
    return gameLogicRef;
}

void ActionEllipseItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragEnter(event, this);
}

void ActionEllipseItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragLeave(event, this);
}

void ActionEllipseItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragMove(event, this);
}

void ActionEllipseItem::dropEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDrop(event, this);
}

