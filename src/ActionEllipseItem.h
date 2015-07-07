#ifndef ACTIONELLIPSEITEM_H
#define ACTIONELLIPSEITEM_H
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QtCore>
#include <QtCore/QList>
#include "GameOfNumbers.h"
#include "GameObserver.h"

/* user may retrieve this item
 * with getSelf() method
 * and call toString()
 * user must not be able to access ActionItem
*/

/* ActionItem:
 * set composition insetead inheritance of QGraphicsRectItem */
class MainWindow;
class MainWindow2;
class FMPlayer;
class Callbacks;

class ActionEllipseItem:QGraphicsEllipseItem {
    friend class MainWindow; /* this is needed, look at [note1] */
    friend class MainWindow2;
private:
    QList<ActionEllipseItem*>* children;
    QList<ActionEllipseItem*>* parent;
public: void addChild(ActionEllipseItem* ai);
public: void addParent(ActionEllipseItem* pa);
public: QList<ActionEllipseItem*>* getParents();
public: QList<ActionEllipseItem*>* getChildren();
public: bool hasParents();
public: bool hasChildren();
public: ActionEllipseItem* getChildAt(int);
public: ActionEllipseItem* getParentAt(int);
public: ActionEllipseItem* getParentByName(QString);
public: ActionEllipseItem* getChildByName(QString);

public: void reportParentChildrenStatus();
private:

    Callbacks* functors;
    FMPlayer* player;
    int value;
    int xcoord;
    int ycoord;
    int width;
    int height;
    bool clicked;
    int __privateId;
    QString __name;
    QGraphicsScene *scene;
    GameOfNumbers* gameLogicRef;
    /* [note1] The constructors must be private. Users must not interact
        with  life/death of the objects */
   public:
    ActionEllipseItem(int x, int y, int w, int h, bool istra, QString name, int id, MainWindow* pw,
                      QGraphicsScene* sc, GameOfNumbers* ref,
                      FMPlayer*, Callbacks* cbs);
    ActionEllipseItem();
    ~ActionEllipseItem();
private:
//    ~ActionItem();
    MainWindow* parentW;
    void setVal(int);
    QString s;
    QString character;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) ;
    void dropEvent(QGraphicsSceneDragDropEvent *event);
public:
    void setCharacterFromString(QString& s);
    QString getCharacter();
    QGraphicsScene* getScene();
    bool getClicked();
    void setClicked(bool);
    void reportToGameLogic(GameOfNumbers*, ActionEllipseItem* );
    GameOfNumbers* getGameLogic();
    bool isTheRightAnswer;
    QString& toString();
    ActionEllipseItem* getSelf();
    void drawEllipseItem();
    Callbacks* getFunctors();
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setWidth(int w);
    void setHeight(int h);
    FMPlayer* getPlayer();

};

#endif // ACTIONELLIPSEITEM_H
