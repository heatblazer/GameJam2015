#include "WindowFrame.h"


#include "AssetManager.h"
#include <QFontDatabase>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextEdit>
#include <QPushButton>
#define CHOICE 2

#define BUTTON_WRATIO 0.1000
#define BUTTON_HRATIO 0.1200
#define TEXT_AREA_WRATIO 0.4
#define TEXT_AREA_HRATIO 0.3

#define SCREEN_RATIO_16_9W  0.16
#define SCREEN_RATIO_16_9H  0.9

#define SCREEN_RATIO_4_3W   0.4
#define SCREEN_RATIO_4_3H   0.3


/*************************************************************************
 * TODO add description
 *Container that will repaint itself, populating various games
 *
 *
 * ************************************************************************/
void WindowFrame::message() {
    qDebug() << "Screen changed";
    qappRef->exit(1);
}

WindowFrame::WindowFrame() { }

WindowFrame::WindowFrame(int w, int h, QApplication* qa,int options)
    : qappRef(qa)
{
    QString res("/home/ilian/QT5/MathForFun/myresource.rcc");
    AssetManager::loadFileFromResource(res);

    lFactory = new LayoutFactory;
    myFrame = new QWidget;
    myFrame->setMinimumWidth(w);
    myFrame->setMinimumHeight(h);
    animationWindow = new MainWindow(myFrame,
                                     w,h, qappRef,options);

    /* add different demo animations */
//    MainWindow* mmm = new MainWindow(w,h,qappRef,2);

    lFactory->verticalLayouts.append(new QVBoxLayout);
    lFactory->verticalLayouts.append(new QVBoxLayout);
    lFactory->horizontalLayouts.append(new QHBoxLayout);
    lFactory->horizontalLayouts.append(new QHBoxLayout);
    lFactory->horizontalLayouts.append(new QHBoxLayout);


    next = new QPushButton("Пълен екран");
    back = new QPushButton("Изход");
    next->setMinimumSize(myFrame->geometry().width()    *BUTTON_WRATIO,
                         myFrame->geometry().height()   *BUTTON_HRATIO);
    next->setMaximumSize(myFrame->geometry().width()    *BUTTON_WRATIO,
                         myFrame->geometry().height()   *BUTTON_HRATIO);

    back->setMinimumSize(myFrame->geometry().width()    *BUTTON_WRATIO,
                         myFrame->geometry().height()   *BUTTON_HRATIO);
    back->setMaximumSize(myFrame->geometry().width()    *BUTTON_WRATIO,
                         myFrame->geometry().height()   *BUTTON_HRATIO);
    lFactory->verticalLayouts.at(1)->addWidget(next);
    lFactory->verticalLayouts.at(1)->addWidget(back);

    /* [1] TEST TEXT */
    if ( options == 1 )
    textArea.append(
                QString(TextNodes::readFromFile(":/resources/texts/molegame.txt")));
    if ( options == 2 )
    textArea.append(
                QString(TextNodes::readFromFile(":/resources/texts/animalsgame.txt")));

    //textArea.setStyleSheet("background-image:url(/home/ilian/Untitled.png);background-attachemet:fixed;");
    textArea.setMinimumSize(myFrame->geometry().width()*    TEXT_AREA_WRATIO*1.6,
                            myFrame->geometry().height()*   TEXT_AREA_HRATIO);
    textArea.setMaximumSize(myFrame->geometry().width()*    TEXT_AREA_WRATIO*1.6,
                            myFrame->geometry().height()*   TEXT_AREA_HRATIO);
    lFactory->horizontalLayouts.at(0)->addLayout(
                lFactory->verticalLayouts.at(1));
    lFactory->horizontalLayouts.at(0)->addWidget(animationWindow
                                                 ->getView(), Qt::AlignAbsolute);

  //  lFactory->horizontalLayouts.at(1)->addWidget(&textArea, Qt::AlignCenter);

    lFactory->horizontalLayouts.at(2)->addWidget(back);
    lFactory->horizontalLayouts.at(2)->addWidget(next);
    back->setVisible(false);
    next->setVisible(false);
/*
    lFactory->horizontalLayouts.at(1)->addWidget(mmm
                                                 ->getView());
*/
    lFactory->verticalLayouts.at(0)->addLayout(
                lFactory->horizontalLayouts.at(0));

    lFactory->verticalLayouts.at(0)->addLayout(
                lFactory->horizontalLayouts.at(1));
    lFactory->verticalLayouts.at(0)->addLayout(
                lFactory->horizontalLayouts.at(2));

    myFrame->setLayout(lFactory->verticalLayouts.at(0));


    QObject::connect(next, SIGNAL(clicked()),
                     myFrame, SLOT(showFullScreen()));
    QObject::connect(back, SIGNAL(clicked()),
                     myFrame, SLOT(close()));

    //[1]myFrame->setStyleSheet(
    //            "background-image: url(:/resources/images/background.png);");

}
void WindowFrame::show() {
    myFrame->show();
  //[UNCOMMENT]//  myFrame->showFullScreen();
}

WindowFrame::~WindowFrame() {
    qDebug() << "Called ~WIndowFrame()";
    delete animationWindow;

}


int WindowFrame::self_main(int argc, char** argv, QApplication* qapp) {
    // select the appropriate width x height
    QDesktopWidget wd;
    QRect r = wd.availableGeometry();
    qDebug() << "SCREEN GEOMETRY:" << r.width() << "X" << r.height() <<"\n";
#ifdef __ANDROID_API__
    WindowFrame* wf = new WindowFrame(r.width()*0.5,
                                      r.height()*0.5 ,qapp,1);
#else
    WindowFrame* wf;
    if ( argc == 1 ) {
            wf = new WindowFrame(r.width(),
                                 r.height(),
                                      qapp,argc);
            wf->show();

    } else if ( argc == 2) {
            wf = new WindowFrame(r.width()/**0.53*/,
                                 r.height(),
                                 qapp,argc);
            wf->show();
    }  else if ( argc == 3) {
    wf = new WindowFrame(r.width(),
                         r.height(),
                         qapp,argc);

    wf->show();

}

#endif
    return qapp->exec();
}



int main(int argc, char** argv) {
    QApplication* qapp =  new QApplication(argc, argv);
    WindowFrame::self_main(argc, argv, qapp);
    return qapp->exec();
}

