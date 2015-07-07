#include "ActionItemContainer.h"
#define BUILDER ActionItemContainer::Builder
ActionItemContainer::Builder::Builder() {
    /* do nothing */
    qDebug() << "Static construct of Builder\n";
}



ActionItemContainer::Builder ActionItemContainer::builder ;

BUILDER* BUILDER::setEllipse(ActionEllipseItem *el) {
    qDebug() << "Creating an ellipse item\n";
    this->ell = el;
    return this;
}

BUILDER* BUILDER::setRectangle(ActionRectItem *el) {
    qDebug() << "Creating an rect item\n";
    this->rct = el;
    return this;
}
ActionItemContainer::ActionItemContainer() {}
ActionItemContainer* BUILDER::build() {
    qDebug() << "Building the new item...\n";
    return new ActionItemContainer(this);
}

ActionItemContainer::ActionItemContainer(Builder *bld) {
    this->ellipse =  bld->ell == NULL ? NULL : bld->ell;
    this->rect = bld->rct == NULL ? NULL : bld->rct;

}

ActionRectItem* ActionItemContainer::getRectItem() {
    return rect;
}

ActionEllipseItem* ActionItemContainer::getEllipseItem() {
    return ellipse;
}
