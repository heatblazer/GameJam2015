#include <QApplication>
#include "FModePlayer.h"
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtCore>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include "MainWindow.h"
#include "Callbacks.h"
#include "ActionItem.h"
#include "ZooGame.h"
//#define DEBUG_MOUSEPRESSEVENT

/*************************************************************************
 *Added 24.12.2014
 *This class will act as base for down and upcasts to avoid usage of
 * dupcodes of ActionRectItem and ActionEllipseItem.
 * TODO is a test.
 *
 *
 * ************************************************************************/

using namespace zoogame ;


////////////////////////////////////////
void ActionItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragEnter(event, this);
}

void ActionItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragLeave(event, this);
}

void ActionItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragMove(event, this);
}

void ActionItem::dropEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDrop(event, this);
}


ActionItem::~ActionItem() {
    qDebug() << "~ACTION ITEMMMMMMMMM";
    delete functors;
    delete player;
    delete zoo;
}


void ActionItem::onTimerFinished()
{
    functors->doSomething(this);
}

ActionItem::ActionItem() {
    }

void ActionItem::doCollision()
{
    //do something with the collision
    qDebug() << this->toString() << "collided";
}

void ActionItem::setMyRotate()
{
    angle++;
    setRotation(angle);
}

void ActionItem::advance(int phase)
{
    functors->onAdvance(phase, this);
    if ( childs.size() > 0 ) {
        for(int i=0; i < childs.size();i++)
            childs.at(i)->getFunctors()->onAdvance(phase,childs.at(i));
    }
}

ActionItem* ActionItem::getSelf() {
    return this;
}

void ActionItem::addChild(ActionItem *a)
{
    childs.append(a);
}

void ActionItem::setTimerToDisplay(QString &s)
{
    this->timerToDisplay = s;
}

QString ActionItem::getTimerToDisplay() {
    return this->timerToDisplay;
}

void ActionItem::setTimeRemain(int t) {
    this->timeRemain = t;
}

int ActionItem::getTimeRemain() {
    return this->timeRemain;
}

ActionItem::ActionItem(int x, int y, int w, int h,
                               QString name, int id,
                               QGraphicsScene* sc,
                               FMPlayer *pl,
                               QString res,
                               Callbacks* cbs)
    :xcoord(x), ycoord(y), width(w), height(h),
      name(name), privateId(id), player(pl),
      speed(5), scene(sc), pixmapRes(res),
      functors(cbs) /*great success :D */

{


    if ( !res.isEmpty()) {
        pixmap = new QPixmap(res);
    } else {

    }
    timer = new QTimer;
    oldx = oldy = 0;
}

void ActionItem::reportToGameLogic() {
    qDebug() << "[ActionItem] Sending report...";
    zoo->getReportFrom(this);
}

void ActionItem::getReportFromGameLogic(ZooGame *sender)
{
    qDebug() << "[ActionItem] I got report from " << sender;
}


void ActionItem::setMyPixmap(QString s) {
    if ( pixmap ) delete pixmap; /* prevent memory leaks */
    if ( s.isEmpty() ) return;
    else {
        try {
            pixmap = new QPixmap(s);
        } catch (...) {

        }
    }
}

QString ActionItem::getPixmapRes() {
    return pixmapRes;
}

void ActionItem::setClickable(bool tf) {
    if ( tf ) {
        this->setAcceptedMouseButtons(0);
    } else {
        this->setAcceptedMouseButtons(Qt::LeftButton);
    }
}

void ActionItem::setMyTimer(int i) {
    timer->setInterval(i);

}

void ActionItem::startMyTimer() {
    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimerFinished()) );
    timer->start();
}

void ActionItem::stopMyTimer() {
    timer->stop();
}

void ActionItem::setName(QString s)
{
    this->name = s;
}

QTimer *ActionItem::getMyTimer() const
{
    return timer;
}

void ActionItem::setCell(zoogame::Cell* an)
{

    cell = an;
}

zoogame::Cell* ActionItem::getCell()
{
    return cell;
}

QGraphicsRectItem* ActionItem::getRectItem() {
    rect = new QGraphicsRectItem;
    rect->setRect(xcoord,ycoord,width,height);
    rect->setBrush(QBrush(*pixmap));
    return rect;
}

QGraphicsEllipseItem* ActionItem::getEllipseItem() {
    ellipse = new QGraphicsEllipseItem;
    ellipse->setRect(xcoord,ycoord,width,height);
    return ellipse;
}

QGraphicsItem* ActionItem::getGraphicsItem() {

    return item;
}

QString& ActionItem::toString() {
    return name;
}


int ActionItem::getId() {
    return privateId;
}



void ActionItem::setNewCallbacks(Callbacks *cb)
{
    if ( functors ) delete functors;
    functors =  cb;
}


void ActionItem::setXY(int x, int y)
{
    xcoord = x; ycoord = y;
    setPos(xcoord, ycoord);
}

void ActionItem::setMapXY(int x, int y)
{
    mapxy[0]=x; mapxy[1]= y;
}

int *ActionItem::getMapXY()
{
    return mapxy;
}


void ActionItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

#ifdef DEBUG_MOUSEPRESSEVENT
    qDebug() << "Clicked:" << this->toString()
             << this->getX() << " x " << this->getY()
             << this->boundingRect();

    qDebug() << "MainWindow free xoords" <<
                MainWindow::freeCoords[0]
             << MainWindow::freeCoords[1];
#endif
    functors->onMouse((QGraphicsSceneMouseEvent*)event,
                      (ActionItem*)this);
}

void ActionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
/*[1] done paint()
 paint now can be programmed from outside
and be different for each object instances
see MainWindow.cpp at customOnPaint() static
inline function
*/
    functors->onPaint(painter, option, widget, (QGraphicsItem*)this);
    if ( childs.size() > 0 ) {
        for(int i=0; i < childs.size();i++)
            childs.at(i)->getFunctors()->onPaint(painter,
                                                 option,
                                                 widget,
                                                 childs.at(i));
    }
}

QRectF ActionItem::boundingRect() const
{
    /* bug fixed - return always the current
     * xy and WxH
     * */
    return QRectF(xcoord,ycoord,width,height);

}

QGraphicsScene* ActionItem::getScene() {
    return scene;
}

int ActionItem::getX() const {
    return xcoord;
}

int ActionItem::getY() const {
    return ycoord;
}

int ActionItem::getWidth() const {
    return width;
}

int ActionItem::getHeight()const {
    return height;
}

void ActionItem::setLocation(QPointF l) {
    mylocation = l;
}

qreal ActionItem::getAngle() const {
    return angle;
}

QPointF ActionItem::getLocation() const
{
    return mylocation;
}

void ActionItem::setX(int x)
{
    xcoord = x;
}

void ActionItem::setY(int y) {
    ycoord = y;
}

void ActionItem::setHeight(int h) {
    height = h;
}

void ActionItem::setWidth(int w) {
    width = w;
}


qreal ActionItem::getSpeed() const {
    return speed;
}

void ActionItem::setSpeed(qreal s) {
    speed = s;
}

void ActionItem::setAngle(qreal a) {
    angle = a;
}

FMPlayer *ActionItem::getPlayer()
{
    return player;
}

ZooGame *ActionItem::getZooGameRef()
{
    return zoo;
}

bool ActionItem::getClicked()
{
    return clicked;
}

void ActionItem::setClicked(bool b)
{
    clicked = b;
}

Callbacks* ActionItem::getFunctors() {
    return functors;
}

QPixmap* ActionItem::getMyPixmap()
{
    return pixmap;
}



