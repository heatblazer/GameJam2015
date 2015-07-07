#ifndef LAYOUTFACTORY_H
#define LAYOUTFACTORY_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>

class LayoutFactory {
private:

public:
   QList<QVBoxLayout*> verticalLayouts;
   QList<QHBoxLayout*> horizontalLayouts;

   QVBoxLayout* getVLayoutAt(int);
   QHBoxLayout* getHLayoutAt(int);


};

#endif // LAYOUTFACTORY_H
