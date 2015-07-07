#ifndef ACTIONITEM_H
#define ACTIONITEM_H
#include <QGraphicsItem>
#include <QtCore>
#include "ZooGame.h"
#include "StringOv.h"

struct ZooGame;
struct QGraphicsSceneMouseEvent;
struct QPainter;
struct QStyleOptionGraphicsItem;
struct QWidget;
struct ActionRectItem;
struct QGraphicsItem;
struct MainWindow;
class QTimer;
class Callbacks;
class FMPlayer;
struct MainWindow2;



/* THis class will help avoidint the
 * many casts. */
class ActionItem :QObject,QGraphicsItem {
    friend class MainWindow;
    friend class ZooGame;

    Q_OBJECT
private:
    QList<ActionItem*> childs;
public: void addChild(ActionItem* a);
private:
    bool clicked;
    int oldx,oldy; // for Zoo game prev coords
    int mapxy[2];
    FMPlayer* player;
    QRectF myRect;
    Callbacks* functors;
    QString s;
    QPointF mylocation;
    QTimer* timer;
    QList<QImage*> images;
    QPixmap* pixmap;
    QImage  image;
    int privateId;
    qreal angle;
    qreal speed;
    QString name;
    QGraphicsScene* scene;
    QString pixmapRes;
    QGraphicsItem* item;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    QImage myImage;
    ZooGame* zoo;

    /* for Lenin */
private:
    QString timerToDisplay;
    int timeRemain;

public:
    void setTimerToDisplay(QString& );
    void setTimeRemain(int);

    QString getTimerToDisplay();
    int getTimeRemain();

private:

    int xcoord; int ycoord; int width; int height;
    /* [note1] The constructors must be private. Users must not interact
        with  life/death of the objects */
    ActionItem(int x, int y, int w, int h,
                   QString name, int id,
                   QGraphicsScene* sc,
                   FMPlayer* pl,
                   QString res,
                   Callbacks*);
    ActionItem();
    ~ActionItem();
public:
    void setStringoff(QString, int);

public slots:
    void onTimerFinished();
public slots:
    void setMyRotate();
protected:
    /*overriden*/
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) ;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) ;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) ;
    void dropEvent(QGraphicsSceneDragDropEvent *event) ;
public:

    struct MString* mystring;
    QList<struct MString> mstringList;

    void setNewCallbacks(Callbacks *cb);
    void doCollision();
    QGraphicsScene* getScene();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const ;
    void addImagesToAnimation(QImage& im);
    QString& toString();
    ActionItem* getSelf();
    Callbacks* getFunctors();
    QPixmap* getMyPixmap();
    void setMyPixmap(QString s);
    QString getPixmapRes();
    QGraphicsRectItem* getRectItem();
    QGraphicsEllipseItem* getEllipseItem();
    QGraphicsItem* getGraphicsItem();
    FMPlayer* getPlayer();


    ZooGame* getZooGameRef();
    void reportToGameLogic();
    void getReportFromGameLogic(ZooGame* sender);


    void setXY(int, int);
    void setMapXY(int x,int y);
    int* getMapXY();

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
    bool getClicked();
    void setClickable(bool);
    void setClicked(bool);
    void setMyTimer(int i);
    void startMyTimer();
    void stopMyTimer();
    void setName(QString s);
    QTimer* getMyTimer() const;
    /* UGLY :( */
    void setCell(zoogame::Cell* cl);
    zoogame::Cell* getCell() ;
    int getId();
private:
    zoogame::Cell* cell;
};

#endif // ACTIONITEM_H
