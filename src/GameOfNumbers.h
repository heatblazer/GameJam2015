#ifndef GAMEOFNUMBERS_H
#define GAMEOFNUMBERS_H
#include <QObject>
#include <QList>
class  ActionEllipseItem;
class MainWindow;
/*[TODO] Create and implement
 * a comunicator class that derives from
 * QObject and sends/reports to GUI and Logics */

//class QList<ActionEllipseItem*>;

class GameOfNumbers {
    friend class MainWindow;
    friend class ActionEllipseItem;

public:
    void checkConditions();
    void getReport(ActionEllipseItem*);
    GameOfNumbers() ;
    GameOfNumbers(MainWindow* mw);
    ~GameOfNumbers();
    void sendReport(GameOfNumbers *, ActionEllipseItem *);
    void checkReport(ActionEllipseItem*);
    void createWinningNumbers(QList<ActionEllipseItem*>* listItems);
    void setParentChildrenRelation();
    void createWinningNumbers2(ActionEllipseItem*);
    bool isWinner(ActionEllipseItem*);
    void increaseTurns();
    int getTurns();
private:
    MainWindow* mainWindowRef;
    int turns;
    bool winningCondition;
};

#endif // GAMEOFNUMBERS_H
