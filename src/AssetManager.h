#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <QResource>
#include <QtCore>

class AssetManager {
    AssetManager();

public:
    static void registerResources();
    static void loadFileFromResource(QString& s);
};

#endif // ASSETMANAGER_H
