#ifdef __gnu_linux__

extern "C" {
#include "utils.h"
}

#endif

#include <QtAlgorithms>
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QFontMetrics>
#include <QDesktopWidget>
#include <QTextItem>
#include <QStringRef>
#include <QEvent>
#include <QList>
#include <QApplication>
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QRgb>
#include <QTextOption>

#include "MainWindow.h"
#include "Callbacks.h"
#include "FModePlayer.h"
#include "TextNodes.h"

#define TEST_LOG 1

#define MY_UNUSED(Q1,Q2,Q3,Q4) {Q_UNUSED(Q1);Q_UNUSED(Q2);Q_UNUSED(Q3);Q_UNUSED(Q4);}

#include <QDesktopWidget>

bool MainWindow::gameOver = false;
MainWindow* MainWindow::MainWindowSelfRef =  0x00;

QList<ActionRectItem*> MainWindow::actionItems2;
QList<ActionItem*> MainWindow::actionItems3;
QList<ActionItem*> MainWindow::tmpList;
QList<struct MString> MainWindow::mstringList;
QString MainWindow::screenString;

ActionItem* MainWindow::itemMap[20][20]={{0},{0}};
int MainWindow::freeCoords[2] = {250,250};


static inline void nullPaint2(QPainter* qp, const QStyleOptionGraphicsItem* qsi,
                              QWidget* wd, QGraphicsItem* ari) {


}

static inline void nullPaint(QPainter* qp, const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari)
{
    MY_UNUSED(qp,qsi,wd,ari)
    /* NULL PAINT */

}
static inline void nullDragDrop(QGraphicsSceneDragDropEvent* event,
                                QGraphicsItem* item) {
    MY_UNUSED(event,event,item,item)

}

static inline void customOnDragEnter(
        QGraphicsSceneDragDropEvent *event, QGraphicsItem* ari) {
    MY_UNUSED(event,event,ari,ari)
    ((QGraphicsItem*)((ActionRectItem*)ari->parentItem()))->update();
}

static inline void customOnDragLeave(
        QGraphicsSceneDragDropEvent *event, QGraphicsItem* ari) {
    MY_UNUSED(event,event,ari,ari)

    ((QGraphicsItem*)((ActionRectItem*)ari->parentItem()))->update();
}

static inline void customOnDrop(
        QGraphicsSceneDragDropEvent *event, QGraphicsItem* ari) {
    MY_UNUSED(event,event,ari,ari)

    ((QGraphicsItem*)((ActionRectItem*)ari->parentItem()))->update();
}
/* implement for ActionElliseItem */

static inline void customOnPaint2(QPainter* qp,
                                 const QStyleOptionGraphicsItem* qsi,
                                 QWidget* wd, QGraphicsItem* ari) {
    MY_UNUSED(qp,qsi,wd,ari)

    QBrush Brush(Qt::green);
    ((QGraphicsRectItem*)ari)->setBrush(Brush);
    ((QGraphicsRectItem*)ari)->setRect(
                ((QGraphicsRectItem*)ari)->boundingRect()
                );
    qp->fillRect(((QGraphicsRectItem*)ari)->boundingRect()
            , Brush);
}




static inline void dummy1(QGraphicsSceneMouseEvent* me, QGraphicsItem* ari) {
    MY_UNUSED(me,me,ari,ari)

    qDebug() << "dummy1()";
}


static inline void BoundsPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)
    QFont font;
    QFontMetrics qfm(font);
    font.setPixelSize(30);
    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QPen mypen(QColor(Qt::red));
    qp->setPen(mypen);
    qp->setFont(font);
    QString str = ((ActionItem*)ari)->toString();
    qp->drawText(rec.x()*1.3, rec.y()* 2, MainWindow::screenString);
    wd->update(); //needed

}


static inline void LifePaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari) {

    QRectF qrf = ((ActionItem*)ari)->boundingRect();
    QPixmap pm(":/resources/images/Star.png");
    QImage im = pm.toImage();
    qp->drawImage(qrf, im);
    wd->update();

}


static inline void TextPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari) {
         MY_UNUSED(qp,qsi,wd,ari)
    QFont wf("Times", 20);
    QPen pen(QColor(Qt::white));
    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QPixmap brick(":/resources/images/Brick.png");
    QImage im = brick.toImage();
    im = im.scaled(im.width(), im.height()* 1.1, Qt::KeepAspectRatio);
    qp->setPen(pen);
    qp->setFont(wf);
    qp->drawImage(rec, im );
    qp->drawText(rec, ((ActionItem*)ari)->toString());
    wd->update(); //needed

}

static inline void Blit(QPainter* qp,
                        const QStyleOptionGraphicsItem* qsi,
                        QWidget* wd, QGraphicsItem* ari) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ari->boundingRect();
    static int i=0;
    QPixmap pm(":/resources/images/lenin.jpg");
    QImage im = pm.toImage();
    switch (i) {
    case 1:  break;
    case 2: break;
    case 3: break;
    case 4: i=0; break;
    }
    i++;
    qp->drawImage(rec, im);
    wd->update(); //needed

}

static inline void ZoomInOut(QPainter* qp,
                        const QStyleOptionGraphicsItem* qsi,
                        QWidget* wd, QGraphicsItem* ari) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QBrush qbr(Qt::blue); //blit OK
    static int i=0;
    int w = ((ActionItem*)ari)->getWidth();
    int h = ((ActionItem*)ari)->getHeight();
    switch (i) {
    case 1: ((ActionItem*)ari)->setWidth(rec.width()*1.2);
            ((ActionItem*)ari)->setHeight(rec.height()*1.2);
        break;
    case 2: ((ActionItem*)ari)->setWidth(rec.width()*1.4);
        ((ActionItem*)ari)->setHeight(rec.height()*1.4);
        break;
    case 3: ((ActionItem*)ari)->setWidth(rec.width()*0.6);
        ((ActionItem*)ari)->setHeight(rec.height()*0.6);
        break;
    case 4: i=0;  break;
    }
    i++;
    qp->drawRect(rec);
    qp->fillRect(rec, qbr);
    wd->update(); //needed

}


static inline void TimerPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QBrush qbr(Qt::blue); //blit OK
    QFont qf;

    QString s( ((ActionItem*)ari)->toString() );
    QPen pen(QColor(255,0,0,255));
    qp->setPen(pen);
    qf.setPixelSize(50);
    qp->setFont(qf);
    qp->drawText(rec.x()*2.2, rec.y()*6, s) ;
    wd->update(); //needed
    return;
}



static inline void SplashPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QPixmap k1(":/resources/images/Splash.png");
    QImage im = k1.toImage();
    qp->drawImage(rec, im);
    wd->update(); //needed
}



static inline void SplashPaint2(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)
    static QString frames[2] = {":/resources/images/mb1.png",
                                ":/resources/images/mb2.png"
                               };
    static int indexf = 0;

    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QPixmap k1(frames[indexf]);
    if ( indexf >= 1) indexf = 0;
    else  indexf++;
    QImage im = k1.toImage();
    qp->drawImage(rec, im);
    wd->update(); //needed
}

static inline void SplashPaint3(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ((ActionItem*)ari)->boundingRect();
    QPixmap k1(":/resources/images/mb2.png");
    QImage im = k1.toImage();
    qp->drawImage(rec, im);
    wd->update(); //needed
}

static inline void KominPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

        QRectF rec = ((ActionItem*)ari)->boundingRect();
        QPixmap k1(":/resources/images/s1.png");
        QImage im = k1.toImage();
        qp->drawImage(rec, im);
        wd->update(); //needed

}

static inline void KominPaint2(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

        QRectF rec = ((ActionItem*)ari)->boundingRect();
        QPixmap k1(":/resources/images/s2.png");
        QImage im = k1.toImage();
        qp->drawImage(rec, im);
        wd->update(); //needed

}



static inline void KominPaint3(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

        QRectF rec = ((ActionItem*)ari)->boundingRect();
        QPixmap k1(":/resources/images/s3.png");
        QImage im = k1.toImage();
        qp->drawImage(rec, im);
        wd->update(); //needed

}


static inline void PaintLenin1(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

        QRectF rec = ((ActionItem*)ari)->boundingRect();
        QPixmap k1(":/resources/images/Lenin1.png");

        QImage im = k1.toImage();
        qp->drawImage(rec, im);
        wd->update(); //needed

}



static inline void PaintLenin2(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

        QRectF rec = ((ActionItem*)ari)->boundingRect();
        QPixmap k1(":/resources/images/Lenin2.png");
        QImage im = k1.toImage();
        qp->drawImage(rec, im);
        wd->update(); //needed

}



static inline void* leninAction(void* v, ...) {

    static bool tf=false;
    if ( tf ) {
        tf = false;
        ((ActionItem*)v)->getFunctors()->onPaint
                = PaintLenin1;
        return (void*) 0x00;
    } else {
        tf= true;
        ((ActionItem*)v)->getFunctors()
                ->onPaint = PaintLenin2;
        return (void*) 0x00;
    }
}



/* OK ------------------------------ TIMED DOWN/UP */
/* CALL DIFFERENT PAINTS FROM HERE ! */



static inline void* SplashTimer(void *e,...) {

   ((ActionItem*)e)->getFunctors()->onPaint
            = SplashPaint2;

}



static inline void* decreaseTime(void *e,...) {

    ((ActionItem*)e)->setTimeRemain(
                ((ActionItem*)e)->getTimeRemain()-1);
    static bool tf = false;
    if ( tf ) {
        ((ActionItem*)e)->getFunctors()->onPaint
            = nullPaint;
        tf = false;
    } else {
        tf = true;
        ((ActionItem*)e)->getFunctors()->onPaint
            = TimerPaint;
    }
}

static inline void* decreaseTime2(void *e,...) {
    static QString s[]= {"29","28", "27", "26", "25", "24",
                         "23", "22", "21", "20", "19","18",
                         "17","16", "15", "14", "13", "12",
                         "11", "10", "9", "8", "7", "6", "5",
                         "4", "3", "2", "1"};
    static int i=0;
    if ( i > 28 ) i =0;
    /* GAMEOVER */
    ((ActionItem*)e)->setTimeRemain(
                ((ActionItem*)e)->getTimeRemain()-1);
    static bool tf = false;

    if ( tf ) {
        ((ActionItem*)e)->getFunctors()->onPaint
            = TimerPaint;
        tf = false;
    } else {
        tf = true;
        ((ActionItem*)e)->setName(s[i++]);
        ((ActionItem*)e)->getPlayer()->playSound(false,0);
        ((ActionItem*)e)->getFunctors()->onPaint
            = TimerPaint;


    }
}


static inline void* decreaseTimeKomin3(void *e,...) {
    static int frames = -1;
    frames++;
    qDebug() << frames << " KOMIN";
    if ( frames == 0) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = nullPaint;

    }
    if ( frames == 1 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint;

    }
    if ( frames == 2) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint2;
    }
    if ( frames == 3 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint3;
        frames -= 4;
    }


}


static inline void* decreaseTimeKomin1(void *e,...) {
    static int frames = -1;
    frames++;
    qDebug() << frames << " KOMIN";
    if ( frames == 0) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = nullPaint;

    }
    if ( frames == 1 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint;

    }
    if ( frames == 2) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint2;
    }
    if ( frames == 3 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint3;
        frames -= 4;
    }

}

static inline void* decreaseTimeKomin2(void *e,...) {
    static int frames = -1;
    frames++;
    qDebug() << frames << " KOMIN";
    if ( frames == 0) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = nullPaint;

    }
    if ( frames == 1 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint;

    }
    if ( frames == 2) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint2;
    }
    if ( frames == 3 ) {
        ((ActionItem*)e)->getFunctors()
                ->onPaint = KominPaint3;
        frames -= 4;
    }

}

static inline void* lifeChange(void* e, ...) {

}

static inline void SelectionRectPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)

    QRectF rec = ari->boundingRect();
    MY_UNUSED(rec,rec,rec,rec);
/*
    QBrush custom(Qt::red);
    QPen mypen(Qt::blue);
    qp->setPen(mypen);
    qp->drawRect(((ActionItem*)ari)->boundingRect());
    qp->fillRect(((ActionItem*)ari)->boundingRect(), custom);
    */
    QPixmap player(":/resources/images/knight.png");
    QImage img = player.toImage();
    img = img.scaled(60, 60, Qt::KeepAspectRatio);
    qp->drawImage( ((ActionItem*)ari)->boundingRect(), img);
    wd->update(); //needed

}
static inline void BorderRectPaintFadeIn(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)
    static int iterator=0;
    QRectF rec = ari->boundingRect();
    MY_UNUSED(rec,rec,rec,rec);
    QPen mypen(Qt::red);
    static int transp=0;
    switch ( iterator++ ) {
    case 0: transp = 150; break;
    case 1: transp = 120; break;
    case 2: transp = 100; break;
    case 3: transp = 90; break;
    case 4: transp = 100; break;
    case 5: transp = 120; break;
    case 6: transp = 130 ; break;
    case 7: iterator = 0;
    }

    QBrush custom(QColor(200,155,255,transp));
    qp->setPen(mypen);
    qp->drawRect(((ActionItem*)ari)->boundingRect());
    qp->fillRect(((ActionItem*)ari)->boundingRect(), custom);
    wd->update(); //needed

}


static inline void BorderRectPaint(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)
    int transp = 150;
    QRectF rec = ari->boundingRect();
    MY_UNUSED(rec,rec,rec,rec);
    QPen mypen(Qt::red);
    QBrush custom(QColor(200,155,255,transp));
    qp->setPen(mypen);
    qp->drawRect(((ActionItem*)ari)->boundingRect());
    qp->fillRect(((ActionItem*)ari)->boundingRect(), custom);
    wd->update(); //needed

}



static inline void BorderRectPaintFadeOut(QPainter* qp,
                             const QStyleOptionGraphicsItem* qsi,
                             QWidget* wd, QGraphicsItem* ari ) {
    MY_UNUSED(qp,qsi,wd,ari)
    static int iterator=0;
    QRectF rec = ari->boundingRect();
    MY_UNUSED(rec,rec,rec,rec);
    QPen mypen(Qt::red);
    int transp=0;
    switch ( iterator++ ) {
    case 0: transp = 50; break;
    case 1: transp = 100; break;
    case 2: transp = 150; break;
    case 3: transp = 200; break;
    case 4: iterator = 0; break;
    }
    QBrush custom(QColor(200,155,255,transp));
    qp->setPen(mypen);
    qp->drawRect(((ActionItem*)ari)->boundingRect());
    qp->fillRect(((ActionItem*)ari)->boundingRect(), custom);
    wd->update(); //needed

}

static inline void* dotransparentAnimation(void* v, ...) {
    ((ActionItem*)v)->getFunctors()->onPaint = BorderRectPaintFadeIn;
}


/****************************************************************************/
static inline void dummy3(int i, QGraphicsItem* ari) {

}

static inline void advanceForA(int j, QGraphicsItem* ari) {
    if ( !j ) return;
    ((QGraphicsRectItem*)ari)->mapFromParent(0,100);
}

static inline void dummy3_1(int i, QGraphicsItem* ari) {
    /* do nothing */
    MY_UNUSED(i,i,ari,ari)

}

static inline void* doer(void* v, ...) {
    MY_UNUSED(v,v,v,v)

}

static inline void* splashTimer(void* v,...) {
    static int i=0;
    if ( i == 2 ) {
        ((ActionItem*)v)->getFunctors()
                ->onPaint = nullPaint;
    }
    i++;
}

/* note at TheDoo
/*[BOUND PAINT]*/


static inline void clickOnItem(QGraphicsSceneMouseEvent* me,QGraphicsItem* ari) {
    qDebug() << "Got X:" << ((ActionItem*)ari)->getX() << "  X " <<
                ((ActionItem*)ari)->getY() ;
    static int lives=0;
    static int ind =0 ;

/* 3-hit COMBOS */
/*
    if ( clcl ) {
        t  = QTime::currentTime().msec();
        clcl = false;
        qDebug() << t -m;
    } else {
        m = QTime::currentTime().msec();
        clcl = true;
        qDebug() << m-t;
    }
*/
    if ( ((ActionItem*)ari)->toString() !=
         MainWindow::mstringList.at(ind).s) {
        qDebug() << "LOOOSER";
        MainWindow::actionItems3.at(lives)->getFunctors()
                ->onPaint = nullPaint;
        if ( lives >= 2) {
            emit MainWindow::MainWindowSelfRef->changedGameOver();
        }
        else lives++;
    } else {
        qDebug() << "WINNER";
        MainWindow::screenString.append(((ActionItem*)ari)->toString());
        ((ActionItem*)ari)->getFunctors()
                ->onPaint = nullPaint2;
        ind++;
        static FMPlayer *fm = new FMPlayer(":/resources/sounds/Slap.wav");
        fm->playSound(false, 0);
    }
}

/* OK !!!! */
static inline void SplashClick(QGraphicsSceneMouseEvent* me,QGraphicsItem* ari) {
 //   ((ActionItem*)ari)->getScene()->removeItem(ari);
    static bool clicked = false;

    if ( ! clicked ) {

        ((ActionItem*)ari)->getFunctors()
            ->onPaint = SplashPaint2;

        ((ActionItem*)ari)->getFunctors()
            ->doSomething = SplashTimer;
        ((ActionItem*)ari)->getMyTimer()->setInterval(600);
        ((ActionItem*)ari)->startMyTimer();
        clicked = true;
    } else {
        clicked = false;
    }

    /* UGLY!!! but inevitable! */

}




/************************************************************************/

/* MainWIndow functions ------------------------------------------------ */
/*************************************************************************
 * TODO add description
 *
 *
 *
 * ************************************************************************/

void MainWindow::addItemToScene(QGraphicsItem *i) {
    this->myScene->addItem(i);
}

MainWindow::MainWindow() { }

MainWindow::MainWindow(QWidget* pw, int w, int h, QApplication* qapp, int selectGame):
width(w), height(h), myQapp(qapp), parentWindow(pw) {

    QString res("/home/ilian/QT5/ProjectZ/myresource.rcc");
    AssetManager::loadFileFromResource(res);

    int id = QFontDatabase::addApplicationFont(":/resources/fonts/Fipps-Regular.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont dyslex(family);
    qapp->setFont(dyslex);
    MainWindow::MainWindowSelfRef = this;
   // splashScreen(pw, w, h, qapp);
    trainGame(pw, w, h, qapp);

}





QList<ActionItem *> MainWindow::getActionItems()
{
    return MainWindow::actionItems3;
}


QGraphicsView* MainWindow::getView() {
    return myView;
}

QGraphicsScene *MainWindow::getScene()
{

}


ActionItem *MainWindow::getActionItemByName(QString s)
{
    int i=0;
    while ( i < actionItems3.size()) {
        if ( actionItems3.at(i)->toString() == s ) {
            qDebug() << "Found item ";
            return actionItems3.at(i);
        }
        i++;
    }
    return NULL;
}

ActionRectItem *MainWindow::getRectItemByName(QString s)
{
    int i=0;
    while ( i < actionItems2.size()) {
        if ( actionItems2.at(i)->toString() == s ) {
            return actionItems2.at(i);
        }
        i++;
    }
    return NULL;
}


MainWindow::~MainWindow() {
    qDebug() << "Destroyed MainWindow instacne";

    while ( !actionItems2.isEmpty()){
        actionItems2.takeFirst();
    }

}

void MainWindow::setMoleWinner(bool tf)
{
}

void MainWindow::setZooWinner(bool tf)
{

}

void MainWindow::emitChangedGameOver()
{
    emit changedGameOver();
}


void MainWindow::startStringFighter()
{

}

void MainWindow::moleGameEnd() {



}



void MainWindow::trainGame(QWidget *wdd, int w, int h, QApplication *qap)
{
    MY_UNUSED(wdd,w,h,qap);
    QDesktopWidget wd;

    int width = wd.screenGeometry().width();
    int height = wd.screenGeometry().height()-70;

    QPixmap background(":/resources/images/background.png");
    background = background.scaled(width,
                                   height);
    myView = new QGraphicsView;

    FMPlayer *pl1 = new FMPlayer(":/resources/sounds/salute.mp3");
    if ( pl1->playSound(true, 1)) {

    } else {
        qDebug() << "FMOD failed";
    }

    ActionItem* splashScreen = new ActionItem(0,0, width, height, "SPLASH",1, myScene,NULL, "",
                                              new Callbacks(
                                                  dummy3,
                                                  dummy1,//SwapOn,
                                                  Blit,
                                                  splashTimer,
                                                  nullDragDrop,
                                                  nullDragDrop,
                                                  nullDragDrop,
                                                  nullDragDrop));

    myScene = new QGraphicsScene;
    myScene->setSceneRect(0,0,
                          width,
                          height);
    myView->setScene(myScene);
    myScene->setBackgroundBrush(background);
    splashScreen->setMyTimer(1000);
    splashScreen->startMyTimer();


    myScene->addItem(splashScreen);

    QString s[] = {
        "One man with a gun can control 100 without one.",
        "A lie told often enough becomes the truth.",
        "I trust no one, not even myself.",
    };

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int ind = qrand()%3;
    qDebug() << "RANDOM IND: " << ind;


    ActionItem* komin1 = new ActionItem(width-(width*0.75), 20, 70,90, "30",1, myScene,
                                        NULL, "",
                                            new Callbacks(
                                                dummy3,
                                                dummy1,//SwapOn,
                                                nullPaint,
                                                decreaseTimeKomin1,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop));


    ActionItem* komin2 = new ActionItem(width-(width*0.34),
                                        height-(height*0.55), 40,80, "",1, myScene,
                                        NULL, "",
                                            new Callbacks(
                                                dummy3,
                                                dummy1,//SwapOn,
                                                nullPaint,
                                                decreaseTimeKomin2,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop));


    ActionItem* komin3 = new ActionItem(width/2, height-500, 85,130, "",1, myScene,
                                        NULL, "",
                                            new Callbacks(
                                                dummy3,
                                                dummy1,
                                                nullPaint,
                                                decreaseTimeKomin3,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop,
                                                nullDragDrop));





    FMPlayer *gong  = new FMPlayer(":/resources/sounds/gong.wav");
    ActionItem *timer= new ActionItem(250, 20, 100,100, "30",1, myScene,
                                      gong, "",
                                          new Callbacks(
                                              dummy3,
                                              dummy1,//SwapOn,
                                              TimerPaint,
                                              decreaseTime2,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop));


    timer->setMyTimer(1000);

    ActionItem* heart1 = new ActionItem(width-(width/2.5), 50, 92,92, "life1",1, myScene,NULL, "",
                                       new Callbacks(
                                           dummy3,
                                           dummy1,//SwapOn,
                                           LifePaint,
                                           lifeChange,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop));

    ActionItem* heart2 = new ActionItem(width-(width/3.0), 50, 92,92, "life2",1, myScene,NULL, "",
                                       new Callbacks(
                                           dummy3,
                                           dummy1,//SwapOn,
                                           LifePaint,
                                           lifeChange,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop));

    ActionItem* heart3 = new ActionItem(width-(width/3.5), 50, 92, 92, "life3",1, myScene,NULL, "",
                                       new Callbacks(
                                           dummy3,
                                           dummy1,//SwapOn,
                                           LifePaint,
                                           lifeChange,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop));


    actionItems3.append(heart1);
    actionItems3.append(heart2);
    actionItems3.append(heart3);

    myScene->addItem(heart1);
    myScene->addItem(heart2);
    myScene->addItem(heart3);

    ActionItem* lenin = new ActionItem(0, 120, 300, 480, "lenin",1, myScene,NULL,
                                       "",
                                       new Callbacks(
                                           dummy3,
                                           dummy1,
                                           nullPaint,
                                           leninAction,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop,
                                           nullDragDrop));

    ActionItem *bigScreen= new ActionItem(180, 90, 700,200,
                                          MainWindow::screenString,1, myScene,NULL, "",
                                          new Callbacks(
                                              dummy3,
                                              dummy1,//SwapOn,
                                              BoundsPaint,
                                              doer,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop));
    qDebug() << "BIG SCR:" << bigScreen->toString();
    /* split algo */
    int size = s[ind].length();
    QStringList qstl;
    qDebug() << "String is " << size << " big";

    int i, xgap, ygap;
    xgap =  ygap = 0;

    while ( i < size ) {
      int bytes = (qrand()%4)+2;
      QStringRef substr(&s[ind], i, bytes);
      qstl.append(substr.toString());
      i += bytes;
    }
    QStringList randomized;
    while(qstl.isEmpty()) {
        int rnd = qrand() % qstl.size();
        randomized.append(qstl.at(rnd));
        qstl.removeAt(rnd);
    }

    qDebug() << "SCENE COORDS: " << myScene->width()
             << " X " << myScene->height();
    int x= width - (width* 0.70);
    int y = height - (height*0.35);
    for (i=0; i < qstl.size(); i++) {
        struct MString m = {qstl.at(i),i};
        this->mstringList.append(m);
    }
    QList<ActionItem*> alist;
    int auxi=0;
    while ( !qstl.isEmpty() ) {
        int rnd= qrand() % qstl.size();
        qDebug() << "LIST :"<< qstl.at(rnd);
        int auxX;
        int auxY;
        if ( i % 2 == 0 ) {
            x+= 50;
            y -= 35;
        } else {
            x += 50;
            y += 35;
        }
        i++;

        ActionItem *item= new ActionItem(
                    x,y + 90,
                    (qstl.at(rnd).size())+70, 30,
                     qstl.at(rnd),rnd, myScene,
                    NULL, "",
                                              new Callbacks(
                                                  dummy3,
                                                  clickOnItem,//SwapOn,
                                                  TextPaint,
                                                  doer,
                                                  nullDragDrop,
                                                  nullDragDrop,
                                                  nullDragDrop,
                                                  nullDragDrop));


        alist.append(item);
        qstl.removeAt(rnd);
    }
    while  ( !alist.isEmpty() ) {
        int rnd = qrand() % alist.size();
        myScene->addItem(((ActionItem*) alist.at(rnd)));
        alist.removeAt(rnd);
    }

    myScene->addItem(lenin);
    myScene->addItem(timer);
    myScene->addItem(bigScreen);

    myScene->addItem(komin1);
    myScene->addItem(komin2);
    myScene->addItem(komin3);


    lenin->setMyTimer(1000);
    lenin->startMyTimer();
    komin1->setMyTimer(1000);
    komin1->startMyTimer();


    komin2->setMyTimer(600);
    komin2->startMyTimer();


    komin3->setMyTimer(1200);
    komin3->startMyTimer();
    timer->startMyTimer();

    myView->setMinimumSize(width- width*0.9, height -height*0.6);
    // myView->show();
}

void MainWindow::splashScreen(QWidget *wdd, int w, int h, QApplication *qapp)
{
    QDesktopWidget wd;
    this->width = wd.screenGeometry().width();
    this->height = wd.screenGeometry().height();


  //  QPixmap background(":/resources/images/Splash.png");
  //  background = background.scaled(this->width, this->height);

    myView = new QGraphicsView;
    myScene = new QGraphicsScene;
    myScene->setSceneRect(0,0,
                          width,
                          height);
    myView->setScene(myScene);
    ActionItem *splash= new ActionItem(
                0,0,
                width, height,
                 "",0, myScene,NULL, "",
                                          new Callbacks(
                                              dummy3,
                                              SplashClick,
                                              SplashPaint,
                                              SplashTimer,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop,
                                              nullDragDrop));
    QObject::connect(this, SIGNAL(changedGameOver()),
                     this, SLOT(moleGameEnd()) );
    myScene->addItem(splash);
    connect(splash, SIGNAL(destroyed()),
            this, SLOT(moleGameEnd()) );
    myView->show();

}
