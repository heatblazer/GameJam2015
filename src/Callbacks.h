#ifndef CALLBACKS_H
#define CALLBACKS_H

/* functors are fun :) */
/* 23.12.2014
 * IMPORTANT NOTE- Callbacks constructur MUST have
 * parameters to functions, do not use NULL, causes break
 * use dummy static inlines like
 * static inline void* dosth(void*,...) { }
 * and pass it to the Callbacks or the program crashesh */

struct QGraphicsSceneMouseEvent;
struct QPainter;
struct QStyleOptionGraphicsItem;
struct QWidget;
struct ActionRectItem;
struct QGraphicsItem;
struct QGraphicsSceneDragDropEvent;

/*[info]
 * QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget
*/
/*created 20.11.2014 */
/*add more callbacks if needed */
typedef void (*onadvance)(int, QGraphicsItem*);
typedef void(*onmousepressevt)(QGraphicsSceneMouseEvent*, QGraphicsItem*);
typedef void(*onpaint)(QPainter*, const QStyleOptionGraphicsItem*,
                       QWidget*, QGraphicsItem*); /* match the same function fro
                                    QGraphicsItem */

typedef void (*ondragEnterEvent)(QGraphicsSceneDragDropEvent*, QGraphicsItem*);
typedef void (*ondragLeaveEvent)(QGraphicsSceneDragDropEvent*, QGraphicsItem*);
typedef void (*ondropEvent)(QGraphicsSceneDragDropEvent*, QGraphicsItem* );
typedef void (*ondragMoveEvent)(QGraphicsSceneDragDropEvent*, QGraphicsItem* );



typedef void* (*dosth)(void*,...);

class Callbacks {
private:
    static int instancesCreated; //optional
    int cusomId; // customId = instancesCreated++ in ctor
public:
    ActionRectItem* client;
    onadvance onAdvance;
    onmousepressevt onMouse;
    onpaint onPaint;
    /* new updated for drag/drop */
    ondragEnterEvent    onDragEnter;
    ondragLeaveEvent    onDragLeave;
    ondragMoveEvent     onDragMove;
    ondropEvent         onDrop;

    dosth doSomething; //implement with casts
    ~Callbacks();
    Callbacks();
    Callbacks(onadvance, onmousepressevt,
              onpaint, dosth, ondragEnterEvent
              ,ondragLeaveEvent, ondragMoveEvent,ondropEvent); //see new C++ for lambdas
    /* 14.12.2014
     * added functions for setting callbacks
     * in runtime, for exchanging logics
     * between objects.
     * ex. Object1 says "Hello", and Object2 says "Holla",
     * after setting the functors or calling the swap
     * O1 will seay Holla and O2 Hello.
     * public callbacks will make this obsolete,
     * since anybodya can access them.
     * TODO is to add getters/setters for them
     * and make them private.
     */
};


#endif // CALLBACKS_H
