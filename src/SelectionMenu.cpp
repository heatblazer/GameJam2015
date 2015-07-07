extern "C" {
#include "utils.h"
#include "LOGFILES.h"
}
#include "SelectionMenu.h"
#include "AssetManager.h"
#include "TextNodes.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QFontDatabase>
#include "WindowFrame.h"

#define DISABLE1
#define DISABLE2
#define DISABLE3
#define DISABLE4


#include <QDebug>

SelectionMenu::~SelectionMenu() {

}

void SelectionMenu::selectGame1() {
    choice = 1;
    gameSelected(choice);
}

void SelectionMenu::selectGame2() {
    choice = 2;
    gameSelected(choice);
}

void SelectionMenu::selectGame3() {
    choice = 3;
    gameSelected(choice);
}


void SelectionMenu::startGame() {
    qDebug() << "Will call a game..." << choice;
    delete this;
    WindowFrame::self_main(choice, argv, qapp);

}
SelectionMenu::SelectionMenu() {}

SelectionMenu::SelectionMenu(int argZ, char** argV, QApplication* qa) :
qapp(qa), choice(0), argc(argZ), argv(argV)
{


    int id = QFontDatabase::addApplicationFont(":/resources/fonts/Fipps-Regular.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont dyslex(family);
    readme.setFont(dyslex);

    myWidget = new QWidget;
    //[1] TEST ICON
    myWidget->setWindowIcon(QIcon(":/resources/icons/t.svg"));
    myVBoxLayout = new QVBoxLayout;
    myWidget->setMinimumSize(600,480);

    myButtons[0] =  new QPushButton("STRING FIGHTER : THE WORD WARRIOR");
    myButtons[0]->setMinimumSize(100,100);

    connect(myButtons[0], SIGNAL(clicked()),
            this,  SLOT(selectGame1()) );
    connect(this, SIGNAL(gameSelected(int)),
            this, SLOT(startGame()) );
    connect(myButtons[0], SIGNAL(clicked()),
            myWidget, SLOT(deleteLater()) );

    myButtons[1] =  new QPushButton("DEBUG MODE");
    myButtons[1]->setMinimumSize(100,100);
    connect(myButtons[1], SIGNAL(clicked()),
            this,  SLOT(selectGame2()) );
    connect(this, SIGNAL(gameSelected(int)),
            this, SLOT(startGame()) );
    connect(myButtons[1], SIGNAL(clicked()),
            myWidget, SLOT(deleteLater()) );


    myButtons[2] =  new QPushButton("TRAIN GAME");
    myButtons[2]->setMinimumSize(100,100);
    connect(myButtons[2], SIGNAL(clicked()),
            this,  SLOT(selectGame3()) );
    connect(this, SIGNAL(gameSelected(int)),
            this, SLOT(startGame()) );
    connect(myButtons[2], SIGNAL(clicked()),
            myWidget, SLOT(deleteLater()) );


    myButtons[3] =  new QPushButton("View readme[new]");
    myButtons[3]->setMinimumSize(100,100);
    myButtons[3]->setMinimumSize(100,100);
    connect(myButtons[3], SIGNAL(clicked()),
            this, SLOT(showReadme()));
#ifdef DISABLE1
    myButtons[1]->setEnabled(false);
#endif
#ifdef DISABLE2
    myButtons[2]->setEnabled(false);
#endif
#ifdef DISABLE3
    myButtons[3]->setEnabled(false);
#endif
#ifdef DISABLE4
    myButtons[4]->setEnabled(false);
#endif

    myVBoxLayout->addWidget(myButtons[0]);
    myVBoxLayout->addWidget(myButtons[1]);
    myVBoxLayout->addWidget(myButtons[2]);
    myVBoxLayout->addWidget(myButtons[3]);


    myWidget->setLayout(myVBoxLayout);

    myWidget->show();
}

void SelectionMenu::showReadme() {

    qwd = new QWidget;
    qvb = new QVBoxLayout;
    qwd->setMinimumSize(400,300);
    readme.setMinimumSize(400,300);


    readme.append(TextNodes::readFromFile(
                      QString(":/resources/texts/readme.txt")));
    connect(qapp, SIGNAL(aboutToQuit()),
            qwd, SLOT(close()) );
    qvb->addWidget(&readme);
    readme.setReadOnly(true);
    qwd->setLayout(qvb);
    qwd->show();
}

void SelectionMenu::showReq()
{

}



