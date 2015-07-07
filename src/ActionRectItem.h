#ifndef ACTIONRECTITEM_H
#define ACTIONRECTITEM_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtCore>
#include <QTimer>
//#include "Callbacks.h"
/*TODO - better document classes
 * and objects.. */

/* ActionItem:
 * set composition insetead inheritance of QGraphicsRectItem
*/
class FMPlayer;
class MainWindow;
class MainWindow2;
class Callbacks;
class ActionRectItem:QObject,QGraphicsRectItem {


   friend class MainWindow; /* this is needed, look at [note1] */
   friend class MainWindow2;
   Q_OBJECT
private:
/* Callbacks myst be opaque pointer
 * add or remove more functions
 * or variables to Callbacks in the future */
    Callbacks* functors; 
    FMPlayer* player;
    QString s;
    QPointF mylocation;
    QTimer* timer;
    QList<QImage*> images;
    QPixmap pixmap;
    int __privateId;
    qreal angle;
    qreal speed;
    QString __name;
    QGraphicsScene* scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    int xcoord; int ycoord; int width; int height;
    /* [note1] The constructors must be private. Users must not interact
        with  life/death of the objects */
    ActionRectItem(int x, int y, int w, int h, qreal a, qreal s,
                   QString name, int id,
                   QGraphicsScene* sc, FMPlayer* ,
                   Callbacks*);
    ActionRectItem();
    ~ActionRectItem();
    MainWindow* parent;
signals: void onClickedSignal();
public slots:
    void setMyRotate(void);
    void paintOnClick();
protected:
    /*overriden*/
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
/* new added 07.01.2015 */
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

public:
    void* doSth(void*,...);
    void doCollision();
    QGraphicsScene* getScene();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private: QPainter* pnt;
private: const QStyleOptionGraphicsItem* opt;
private: QWidget* qwdgt;
public:
    FMPlayer* getPlayer();
    void startMyTimer(int);
    void setNewCallbacks(Callbacks* cb);
    QRectF boundingRect() const;
    void addImagesToAnimation(QImage& im);
    QString& toString();
    ActionRectItem* getSelf();
    Callbacks* getFunctors();
	/* the class must have
	getters and setters methods
	since they will be accessed from
	outside */
 //   void drawRectItem();
    void drawRectItem();
    int getX()const;
    int getY()const;
	int getWidth() const;
	int getHeight() const; 
    qreal getSpeed() const;
    qreal getAngle() const;
    QPointF getLocation() const;
    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);
    void setLocation(QPointF);
    void setSpeed(qreal);
    void setAngle(qreal);
};

#endif // ACTIONITEM_H
