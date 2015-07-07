#include "FModePlayer.h"
#include <QString>
#include <QDebug>

/* test for my tuils */
#ifdef __linux__
extern "C" {
#include "utils.h"
}
#endif

FMPlayer::~FMPlayer() {
    qDebug() << "Freeing FMPlayer chanel, system, sound and info";
    if (sound) free(sound);
    if (info) free(info);
    if (system) free(system);
    bitstream.remove(0, bitstream.size());

}

int FMPlayer::index = 0;

FMPlayer::FMPlayer(const char *fname) {
    myindex = index++;
    QFile io(fname);
    if ( !io.open(QFile::ReadOnly)) {
        qDebug() << "Error loading file";
    } else {
        char* begin = bitstream.data();
        bitstream = io.readAll();
        if ( FMPlayer::systemInit(bitstream.data(),
                                  bitstream.size()) ) {
            qDebug() << "Played sound";

        } else {
            qDebug() << "FMOD failed";
        }
    } /* END FMOD TEST */

}

bool FMPlayer::systemInit(const char *fname, int len) {

    info = new FMOD_CREATESOUNDEXINFO();
    info->cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    info->length = len;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, 0);

    if ( FMOD_OK == ( FMOD_System_CreateStream(system,
                          fname, FMOD_OPENMEMORY_POINT, info, &sound)) ) {

        return true;
    } else {
        return false;
    }

}

/* CNAHHEL IS OPTIONAL */
bool FMPlayer::playSound(bool loop,int chan) {

//    QFile io(":/resources/sounds/blop.wav");
    if (!loop) {
        FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);

    } else {
        FMOD_Sound_SetMode(sound, FMOD_LOOP_NORMAL);
    }
    if ( index > 3 ) index = 0;
    else index++;
    if ( FMOD_System_PlaySound(system, sound, false, 0, &channel[0]) ) {
        FMOD_System_Update(system);

    }

}


