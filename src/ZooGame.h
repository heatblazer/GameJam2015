#ifndef ZOOGAME
#define ZOOGAME
#include <QList>
#include <QString>

class  ActionItem;
class MainWindow;

namespace zoogame {

    struct Cell {
        struct Animal;
        struct Swap;
        friend class Animal;
        friend class Swap;

        QString animalName;
        QString cellName;
        int position;
        bool isFree;

        Cell();
        ~Cell();
        Cell(QString, QString, int, Cell*, Cell*);
        Cell* left;
        Cell* right;
        Cell* swap;

        Animal* animal;
    };

    struct Animal {
        struct Cell;
        struct Swap;

        QString animalName;
        bool canMoveToSwap;
        bool canMoveToAnyCell;

        Animal();
        Animal(QString*, Cell*);
        ~Animal();
        Cell *cell;
    } ;

    struct Swap {
        struct Animal;
        struct Cell;

        Animal* animal;
        Swap();
        ~Swap();
        Cell* emptyCell;
    };
}

class ZooGame {
    friend class MainWindow;
    friend class ActionItem;

public:
    void checkConditions();
    void getReport(ActionItem*);
    ZooGame() ;
    ZooGame(MainWindow* mw);
    ~ZooGame();

    void getReportFrom(ActionItem *);
    void sendReportTo(ActionItem* );

    void checkReport(ActionItem*);
    void createWinningNumbers(QList<ActionItem*>* listItems);
    void setParentChildrenRelation();
    void createWinningNumbers2(ActionItem*);
    bool isWinner(ActionItem*);
    void increaseTurns();
    int getTurns();

    void checkWinningCondition() ;

    void setCell(QString n, QString cell, int pos, int index);
    void openCell(zoogame::Cell* c);
    zoogame::Cell *getOpenedCell();
    void setCellsRelation();
    bool canMoveToCell(zoogame::Cell*);
    bool canMoveToSwap(zoogame::Cell*);
    void moveToSwap(zoogame::Cell*);
private:
    MainWindow* mainWindowRef;
    bool winningCondition;

private:
    /* major Zabozvane :( */

    QList<zoogame::Cell*> cells;
    zoogame::Cell* swap;

};


#endif // ZOOGAME

