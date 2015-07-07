#ifndef WINDOWFRAME_H
#define WINDOWFRAME_H
#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include "LayoutFactory.h"
/* Main container for the items
 * 1.Screen area
 * 2.Text area
 * 3.Misc area (buttons <<  and >> )
 * */

class QApplication;
class QTextEdit;

class WindowFrame : QObject{
    Q_OBJECT
private:
    QWidget* myFrame;
    /*1. screen */
    MainWindow* animationWindow;
    /*TODO 2. text widget */
    QTextEdit textArea;
    /*TODO 3. misc buttons */
    QPushButton *back;
    QPushButton* next;
    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;
    LayoutFactory* lFactory;
    QApplication* qappRef;
public slots:
    void message();
public:
    void show();
    static int self_main(int, char**, QApplication*);
    ~WindowFrame();
    WindowFrame();
    WindowFrame(int, int, QApplication*,int) ;

};


#endif // WINDOWFRAME_H
