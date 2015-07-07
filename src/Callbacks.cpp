#include "Callbacks.h"
#include <QDebug>

/*************************************************************************
 * TODO add description
 * class for functors. The intent is to add different behaviour per class
 * that contains the Callbacks. Behaviour can be added as new funcor or
 * removed if needed to. See usage in MainWindow.cpp static inline functions
 * and ActionRectItem new().
 * 22.12.2014 - added functionality for ActionEllipseItem see the usage
 * with casts ((ActionRectItem*)ari)->actionRectItemSpecific()...
 * ((ActionEllipseItem*)aei)->actionEllipseItemSpecific()..
 * these are called from static inline foos from the MainWindow class, which
 * loads logics and items
 * ************************************************************************/

Callbacks::Callbacks()
{
/* empty Callbacks() for tests only */
    qDebug() << "Empty Callbacks construction is not recommended";
}

Callbacks::Callbacks(onadvance onadv,
                     onmousepressevt onmous,
                     onpaint opaint,
                     dosth doit, ondragEnterEvent enter,
                     ondragLeaveEvent leave, ondragMoveEvent move,
                     ondropEvent drop)
    :onAdvance(onadv), onMouse(onmous),
      onPaint(opaint), doSomething(doit),
      onDragEnter(enter), onDragLeave(leave),onDragMove(move),
      onDrop(drop)
{
    /*callbacks must have pointrs to static inline foos
     * void or NULL is not recommended
     * */

}

Callbacks::~Callbacks() {
    qDebug() << "Callbacks removed";
}
