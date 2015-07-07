#include "ActionRectItem.h"
#include <QDebug>
#include <QObject>
#include <QPen>
#include <QBrush>
#include "FModePlayer.h"
#include "MainWindow.h"
#include "Callbacks.h"

/*************************************************************************
 * TODO add description
 *
 *
 *
 * ************************************************************************/

/* new events for drag/drop */

void ActionRectItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragMove(event, this);
}

void ActionRectItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    functors->onDragEnter(event, this);
}

void ActionRectItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    Q_UNUSED(event);
    functors->onDragLeave(event, this);
}

void ActionRectItem::dropEvent(QGraphicsSceneDragDropEvent *event) {
    Q_UNUSED(event);
    functors->onDrop(event, this);
}


void* ActionRectItem::doSth(void *v, ...) {
    Q_UNUSED(v);
    functors->doSomething((QGraphicsRectItem*)this);
}

void ActionRectItem::addImagesToAnimation(QImage &im) {

}

ActionRectItem::~ActionRectItem() {
    delete functors;
}

ActionRectItem::ActionRectItem() {
    setRect(0,0, 40,40 ); //some defaults for testing
}

void ActionRectItem::doCollision()
{
    //do something with the collision
    qDebug() << this->toString() << "collided";
}

void ActionRectItem::setMyRotate()
{
    functors->doSomething(NULL);
}

void ActionRectItem::paintOnClick()
{

}

void ActionRectItem::advance(int phase)
{
    functors->onAdvance(phase, this);
}

ActionRectItem* ActionRectItem::getSelf() {
    return this;
}

ActionRectItem::ActionRectItem(int x, int y, int w, int h, qreal a, qreal s,
                               QString name, int id,
                               QGraphicsScene* sc, FMPlayer* fm,
                               Callbacks* cbs)
    :__name(name), __privateId(id),
      scene(sc), xcoord(x), ycoord(y), width(w), height(h),
      angle(a), speed(s), player(fm),
      functors(cbs) /*great success :D */

{
    /* add fuction for the timer */
    setRect(xcoord,ycoord,width,height);
    setRotation(angle);
    timer = new QTimer;
}

QString& ActionRectItem::toString() {
    s.append(__name);
    s.append(QString::number(this->__privateId));
    return s;
}

FMPlayer* ActionRectItem::getPlayer() {
    return player;
}

void ActionRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    qDebug() << "CLICKED" << this->toString() ;
    functors->onMouse((QGraphicsSceneMouseEvent*)event, this);
}


void ActionRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    functors->onPaint(painter, option, widget, (ActionRectItem*)this);
}

void ActionRectItem::startMyTimer(int interval)
{
    timer->start(interval);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(setMyRotate()) );
}

void ActionRectItem::setNewCallbacks(Callbacks *cb)
{
    if ( functors ) delete functors;
    functors =  cb;
}


QRectF ActionRectItem::boundingRect() const
{
    /* bug fixed - return always the current
     * xy and WxH
     * */
    return QRectF(xcoord, ycoord, width, height);
}

QGraphicsScene* ActionRectItem::getScene() {
    return scene;
}

int ActionRectItem::getX() const {
    return xcoord;
}

int ActionRectItem::getY() const {
    return ycoord;
}

int ActionRectItem::getWidth() const {
	return width;
}

int ActionRectItem::getHeight()const {
	return height;
}

void ActionRectItem::setLocation(QPointF l) {
    mylocation = l;
}

qreal ActionRectItem::getAngle() const {
    return angle;
}

QPointF ActionRectItem::getLocation() const
{
    return mylocation;
}

void ActionRectItem::setX(int x)
{
    xcoord = x;
}

void ActionRectItem::setY(int y) {
    ycoord = y;
}

void ActionRectItem::setHeight(int h) {
    height = h;
}

void ActionRectItem::setWidth(int w) {
    width = w;
}


qreal ActionRectItem::getSpeed() const {
    return speed;
}

void ActionRectItem::setSpeed(qreal s) {
    speed = s;
}

void ActionRectItem::setAngle(qreal a) {
    angle = a;
}

Callbacks* ActionRectItem::getFunctors() {
    return functors;
}

void ActionRectItem::drawRectItem() {
    setRect(xcoord, ycoord, width, height);
    setBrush(QBrush(Qt::red));
    setPen(QPen(QColor(0,255,0,100)));
}


