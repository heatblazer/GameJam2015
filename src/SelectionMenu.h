#ifndef SELECTIONMENU
#define SELECTIONMENU
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QTextEdit>
#include "WindowFrame.h"

class SelectionMenu : QObject {
    Q_OBJECT
signals:
    void gameSelected(int);
public slots:
    void selectGame1();
    void selectGame2();
    void selectGame3();

    void startGame();

    /* not game realteed misc */
    void showReadme();
    void showReq();
private: int choice;
private:
    QTextEdit readme;
    int argc;
    char** argv;
    int w; int h;
    WindowFrame* game;
    QPushButton* myButtons[4];
    QApplication* qapp;
    QWidget*  myWidget;

    QWidget* qwd;
    QVBoxLayout* qvb;

    QVBoxLayout* myVBoxLayout;
    QHBoxLayout* myHBoxLayout;
public:
    SelectionMenu();
    SelectionMenu(int, char**, QApplication*);
    ~SelectionMenu();
};

#endif // SELECTIONMENU

