#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H
#include <QList>
/* UNUSED FOR NOW */
class QObject;

class GameOfNumbers;
class GameLogic;
class ActionEllipseItem;
class GameReporter;
class GameReciever;


namespace GameObserver {
template <class T> class GameReciever {

public:
    GameReciever();
    GameReciever(T item);
public:
    void recieveReport();
    void addElement(T& e);
    T& getElementAt(int);
private:
    QList<T> elements;
};

template <class T> class GameReporter {

public:
    GameReporter();
    GameReporter(T& item);

public:
    void addElement(T& e);
    T& getElementAt(int);
    void sendReport();
private:
    QList<T> elements;
};

}
#endif // GAMEOBSERVER_H
