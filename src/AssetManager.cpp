#include "AssetManager.h"


void AssetManager::loadFileFromResource(QString& s) {
    QResource::registerResource(s);
//    QResource res("myresources.rcc");
//    res.registerResource("myresources.rcc");
    Q_INIT_RESOURCE(application);
}
