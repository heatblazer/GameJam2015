#ifndef FMODEPLAYER_H
#define FMODEPLAYER_H
#ifdef __linux__
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_codec.h>
#elif __ANDROID_API__
#include <stdio.h>
#include "fmod.h"
#include "fmod_codec.h"
#else //win32 for now
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#endif
#include <QFile>
#include <QByteArray>

//#pragma comment(lib, "fmodex_vc.lib")
//#pragma comment(lib, "fmod.a")
class QString;
class QFile;
class QByteArray;

class FMPlayer {
private:

    bool systemInit(const char* fname, int len);
    FMOD_CHANNEL *channel[20];
    static int index;
    int myindex;
    FMOD_SYSTEM *system;
    FMOD_SOUND *sound;
    FMOD_CREATESOUNDEXINFO *info;
    QFile io;
    QByteArray bitstream;
    FMPlayer();
public:
    ~FMPlayer();
    FMPlayer(const char* fname);
    bool playSound(bool,int);
};

#endif // FMODEPLAYER_H
