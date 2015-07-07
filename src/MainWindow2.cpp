#include "MainWindow2.h"
#include "MainWindow.h"
#include <QEvent>
#include <QList>
#include <QApplication>
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QRgb>
#include <QtSvg/QSvgRenderer>
#include "Callbacks.h"
#include "FModePlayer.h"
#include "TextNodes.h"
#include "ActionItem.h"
#define TEST_LOG 1

/* the marker color for the mole game*/
#define MY_RED      255//234//255//
#define MY_GREEN    0 //209 //0//
#define MY_BLUE     0//78// 0//
/* COLORS FOR BOUNDS */
#define MY_RED_T 0
#define MY_GREEN_T 255
#define MY_BLUE_T 0
/* START COLOR OF TRAIN */
#define TRAIN_RED 255
#define TRAIN_GREEN 0
#define TRAIN_BLUE 0
#include <QDesktopWidget>


bool MainWindow2::gameOver = false;

QList<ActionRectItem*> MainWindow2::actionItems;
/* implement for ActionElliseItem */


static inline void dummy1(QGraphicsSceneMouseEvent* me, QGraphicsItem* ari) {

    qDebug() << "dummy1()";
}
static inline void dummy2(QPainter* qp,
                                 const QStyleOptionGraphicsItem* qsi,
                                 QWidget* wd, QGraphicsItem* ari) {


}


static inline void customOnMouse(QGraphicsSceneMouseEvent* me,
                                 QGraphicsItem* ari) {
    ((ActionItem*)ari)
            ->getRectItem()
            ->setBrush(QBrush(QColor(255,255,0,255)));
    qDebug() << "Called custom on mouse";
}
/* TODO - finish ---------------------------------------------------- */
static inline void onMousePlaySound(QGraphicsSceneMouseEvent* me,
                                 QGraphicsItem* ari) {
    /* ActionEllipseItem logic goes here for the
     * for the game with the mole */

#ifdef TEST_LOG

    ActionEllipseItem* tmpI = ((ActionEllipseItem*)ari);
    QList<ActionEllipseItem*>* tPar = tmpI->getParents();

    if ( tmpI->toString() == "ActionEllipseItem9") {
        ((ActionEllipseItem*)ari)->getGameLogic()->checkConditions();
    }

    if ( tmpI->toString() != "ActionEllipseItem0" &&
         tmpI->toString() != "ActionEllipseItem8") {
        if ( tPar->size()==0  ) {
            /* play some error sound */
            qDebug() << "Parent is NULL";
            qDebug() << tmpI->toString();
            return;
        }
        int j=0;
        qDebug() << tmpI->toString();
        bool ret=false;
        for (; j < tPar->size();j++ ) {
            if ( tPar->at(j)->getClicked() ) ret=true;
        }
        if ( !ret ) return;


    }

#endif
    if ( ! ((ActionEllipseItem*)ari)->getClicked() ) {
        qDebug() << "Item`s toString():" <<
                    ((ActionEllipseItem*)ari)->toString();
        ((ActionEllipseItem*)ari)->reportToGameLogic(
                    ((ActionEllipseItem*)ari)->getGameLogic(),
                    (ActionEllipseItem*)ari);
        QColor* cl;
       /*
        if ( ((ActionEllipseItem*)ari)->getGameLogic()
             ->isWinner((ActionEllipseItem*)ari)) {
            cl = new QColor(255,255,0,255);
        } else {
            cl = new QColor(255,0,0,255);
        }
        */
        cl = new QColor(255,255,0,255);
        ((QGraphicsEllipseItem*)ari)->setBrush(QBrush(*cl));
        QPixmap pix(100, 50);
        QPainter painter(&pix);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::blue);
        QFont font = painter.font();
        font.setPointSize(12);
        painter.setFont(font);
        QString sss = TextNodes::getNextDigit2();
        QGraphicsTextItem* txt = ((ActionEllipseItem*)ari)->getScene()->
                addText(sss, font);
        ((ActionEllipseItem*)ari)->setCharacterFromString(sss);
        txt->setPos(
                    QPointF(
                        ((ActionEllipseItem*)ari)->getX()-(((ActionEllipseItem*)ari)->getWidth()/4),
                        ((ActionEllipseItem*)ari)->getY()-(((ActionEllipseItem*)ari)->getHeight()/4) ));
        ((ActionEllipseItem*)ari)->setClicked(true);
        if ( ((ActionEllipseItem*)ari)->getGameLogic() == NULL ) {
            qDebug() << "No game logic entered";
        } else {
            ((ActionEllipseItem*)ari)->reportToGameLogic(
                        ((ActionEllipseItem*)ari)->getGameLogic(),
                        (ActionEllipseItem*) ari);
        }//endif
        if ( ((ActionEllipseItem*)ari)->getPlayer() == NULL ) {
            qDebug() << "No sound to play";
        } else {
            ((ActionEllipseItem*)ari)->getPlayer()->playSound(false,3);
        }//endif
    } else {
        /* do nothing */
        /*27.12.2014 - tested -OK
         * TODO implement the winning condition */
    }//endif

}
/************************************************************************/
static inline void customOnPaint(QPainter* qp,
                                 const QStyleOptionGraphicsItem* qsi,
                                 QWidget* wd, QGraphicsItem* ari) {

    QBrush Brush(Qt::green);
    ((QGraphicsRectItem*)ari)->setBrush(QBrush(Qt::red));
    ((QGraphicsRectItem*)ari)->setRect(
                ((QGraphicsRectItem*)ari)->boundingRect()
                );
    qp->fillRect(((QGraphicsRectItem*)ari)->boundingRect()
            , Brush);
}


static inline void moveButterfly(QPainter* qp,
                                 const QStyleOptionGraphicsItem* qsi,
                                 QWidget* wd, QGraphicsItem* ari) {

    static int frames = 0;
    QRectF rec = ari->boundingRect();
    QBrush Brush(Qt::white);
    QPixmap peperuda1(":/resources/images/p1.png");
    QPixmap peperuda2(":/resources/images/p2.png");
    QImage f1 = peperuda1.toImage();
    QImage f2 = peperuda2.toImage();
    if ( frames++ % 2 == 0 ) {
        qp->drawImage(((ActionRectItem*)ari)->getX(),
                      ((ActionRectItem*)ari)->getY(),
                      f1);
    } else {
        qp->drawImage(((ActionRectItem*)ari)->getX(),
                      ((ActionRectItem*)ari)->getY(),
                      f2);
    }
}

static inline void customOnAdvance(int i, QGraphicsItem* ari) {
    if ( !i ) return;

    ((QGraphicsRectItem*)ari)->setPos(
                ((QGraphicsRectItem*)ari)
                ->mapToParent(10, (((ActionRectItem*)ari)->getSpeed())));
    ((ActionRectItem*)ari)->setAngle(
                ((ActionRectItem*)ari)->getAngle());
    ((QGraphicsRectItem*)ari)->setRotation(90);
}


/****************************************************************************/
static inline void dummy3(int i, QGraphicsItem* ari) {
    static int interlooper=0;
    interlooper++;
    /* if winning condition is OK */
    if ( interlooper > 100 ) {
        ((ActionRectItem*)ari)->getFunctors()->onAdvance
                = customOnAdvance;
    }
}



static inline void* doer(void*, ...) {
    qDebug() << "Be a DOER, don`t be a DONTER";
}

/**************************************************************************/
static inline void moveButterflyWCollision(QPainter* qp,
                                 const QStyleOptionGraphicsItem* qsi,
                                 QWidget* wd, QGraphicsItem* ari) {

    QPixmap peperuda1(":/resources/images/p1.png");
    QPixmap peperuda2(":/resources/images/p2.png");
    QImage f1 = peperuda1.toImage();
    QImage f2 = peperuda2.toImage();

    if ( qrand() % 2 == 0 ) {
        qp->drawImage(((ActionRectItem*)ari)->getX(),
                      ((ActionRectItem*)ari)->getY(),
                      f1);
    } else {
        qp->drawImage(((ActionRectItem*)ari)->getX(),
                      ((ActionRectItem*)ari)->getY(),
                      f2);
    }

    if ( ((ActionRectItem*)ari)->getScene()->collidingItems(
             (QGraphicsItem*) ari).isEmpty()) {
        if ( qrand() %2 == 0 ) ((ActionRectItem*)ari)->getFunctors()->onAdvance = customOnAdvance;
        if ( qrand() %2 == 1 ) ((ActionRectItem*)ari)->getFunctors()->onAdvance = customOnAdvance;
    }
     //eidnif
} //end moveButterflyWCollision()

/* MainWIndow functions ------------------------------------------------ */
/*************************************************************************
 * TODO add description
 *
 *
 *
 * ************************************************************************/

void MainWindow2::addItemToScene(QGraphicsItem *i) {
    this->myScene->addItem(i);
}

MainWindow2::MainWindow2() { }
static inline void selectMole(int w, int h, QApplication* qapp, MainWindow* ref) {

}

MainWindow2::MainWindow2(QWidget* pw, int w, int h, QApplication* qapp, int selectGame):
width(w), height(h), myQapp(qapp), parentWindow(pw) {
    myScene = new QGraphicsScene;
    myView = new QGraphicsView(myScene);
    myView->setMaximumWidth(width);
    myView->setMaximumHeight(height);
    myScene->setBackgroundBrush(QBrush(Qt::white));
    myScene->setSceneRect(QRectF(0,0,width-(width/40),
                                 height-(height/40)) );

    ActionRectItem* ai = new ActionRectItem(0,0,60,60,0,0, "Item", 1,
                                    myScene, NULL,new Callbacks(
                                       dummy3,
                                        dummy1,
                                        customOnPaint, doer));
            /*new ActionRectItem(100, 100, 100, 100,
                                                    "Screen", 1, NULL,
                                                    myScene,
                                                    new Callbacks(dummy3,
                                                                  dummy1,
                                                                  dummy2,
                                                                  doer));
*/
    ActionEllipseItem *ai1 = new ActionEllipseItem(
                0,100, 100,100,false,"ActionEllipseItem",1,NULL, myScene,
                                         NULL, NULL,
                                         new Callbacks(
                                             dummy3, onMousePlaySound,dummy2, doer));
    ai1->drawEllipseItem();
    ai->drawRectItem();

    myScene->addItem(ai);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()),
            myScene, SLOT(advance()));

    myView->show();

}

QList<ActionRectItem*> MainWindow2::getActionItemsList(){
    return actionItems;
}


QGraphicsView* MainWindow2::getView() {
    return myView;
}

ActionRectItem *MainWindow2::getItemByName(QString s)
{
    int i=0;
    while ( i < actionItems.size()) {
        if ( actionItems.at(i)->toString() == s ) {
            qDebug() << "Item " << s << " found";
            return actionItems.at(i);
        }
        i++;
    }
    return NULL;
}



MainWindow2::~MainWindow2() {
    qDebug() << "Destroyed MainWindow instacne";
}

void MainWindow2::showDebug() {
    qDebug() << myScene->width() <<
                " x " <<
                myScene->height();
}


