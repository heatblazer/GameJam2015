#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSvg/QSvgRenderer>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "ActionRectItem.h"
#include "ActionItem.h" /*universal factory for ActionRect/EllipseItem */
#include "TextNodes.h"
#include "AssetManager.h"
#include "GameOfNumbers.h"
#include "ZooGame.h"
#include "StringOv.h"

typedef void (*customInit)(int, int, QApplication*);
typedef void (*updatego)(bool);

class MainWindow : public QWidget {
    Q_OBJECT
signals:
        void changedGameOver();
public:
public: static MainWindow*  MainWindowSelfRef;
        void setMoleWinner(bool);
        void setZooWinner(bool);
public: void emitChangedGameOver(); // for Clang error
public slots:
    void startStringFighter();
    void moleGameEnd();
    /* parameters are needed if I decied ( in the future )
     * to make it with Callbacks pattern.
     * For now I`ll stick with separete functions FFS!!!
     * */
private: void moleGame(QWidget* wd, int w, int h, QApplication* );
private: void zooGame(QWidget* wd, int w, int h, QApplication* );
private: void trainGame(QWidget* wd, int w, int h, QApplication* );
private: void splashScreen(QWidget* wd, int w, int h, QApplication* qapp);
public:
    MainWindow(QWidget*, int w, int h, QApplication*,int); //passed from the main
    MainWindow();
    ~MainWindow();
    /* experimental */
    static QList<ActionItem*> getActionItems();

    void addItemToScene(QGraphicsItem*);
    QGraphicsView* getView();
    static QGraphicsScene* getScene();

    QWidget* parentWindow;

    static ActionItem *getActionItemByName(QString s);
    static ActionRectItem* getRectItemByName(QString s);
    static int freeCoords[2];
    static bool gameOver;


private:

    QWidget* myWindow;
    QApplication* myQapp;
    QGraphicsScene* myScene;
    QGraphicsView* myView;
    QTimer* timer;

    bool isWinner;
    customInit customConstruction;
    int height;
    int width;
    GameOfNumbers* gameofnumbers;
    ZooGame*    zoogame;
public:
    static QList<ActionRectItem*> actionItems2 ;
    static QList<ActionItem*> actionItems3;
    static QList<struct MString> mstringList;
    static QString screenString;
   public: static QList<ActionItem*> tmpList; static ActionItem* itemMap[20][20];
private:
    bool moleWinner;
    bool zooWinner;


private:


    Callbacks* functors;
    /*resources*/
    /* create QList of files later */
};

#endif // MAINWINDOW_H
