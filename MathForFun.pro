#-------------------------------------------------#
#                                                 #
# Project created by QtCreator 2014-11-04T22:15:51#
#                                                 #
#-------------------------------------------------#
QMAKE_CXXFLAGS += -std=c++11

QT       += core gui
#win32:RC_FILE = t.rc

#LINUX
unix {
    message("*using settings for linux")
ICON = t.svg
    #FMOD linux
Release:DESTDIR = ../../QT5/MathForFun/builds/linux/release
Release:OBJECTS_DIR = ../../QT5/MathForFun/builds/linux/release/obj/
Release:MOC_DIR = ../../QT5/MathForFun/builds/linux/release/moc/
Release:RCC_DIR = ../../QT5/MathForFun/builds/linux/release/rcc/
Release:UI_DIR = ../../QT5/MathForFun/builds/linux/release/ui/

#Debug:DESTDIR = debug
#Debug:OBJECTS_DIR = debug/.obj
#Debug:MOC_DIR = debug/.moc
#Debug:RCC_DIR = debug/.rcc
#Debug:UI_DIR = debug/.ui
    INCLUDEPATH += /home/ilian/fmodstudioapi10509linux/api/lowlevel/inc/
    LIBS += -L/home/ilian/fmodstudioapi10509linux/api/lowlevel/lib/x86/ -lfmod

    INCLUDEPATH +=/home/ilian/MyLibs/libutils/includes/
    LIBS += -L/home/ilian/MyLibs/libutils/lib/unix/ -lutilz
}
#
#ANDROID
android {
    message("*using settigs for android")
    INCLUDEPATH += /home/ilian/fmodstudioapi10509android/api/lowlevel/inc/
    LIBS += /home/ilian/fmodstudioapi10509android/api/lowlevel/lib/armeabi/libfmod.so -lfmod

}

#WINDOWS
win32 {
    message("*using settings for windows")

#FMOD
    INCLUDEPATH += Z:/home/ilian/.wine/drive_c/FMODSoundSystem/FMODStudioAPIWindows/api/lowlevel/inc/
    LIBS += /home/ilian/.wine/drive_c/FMODSoundSystem/FMODStudioAPIWindows/api/lowlevel/lib/libfmod.a
#my utilz
    INCLUDEPATH += /home/ilian/MyLibs/libutils/includes/
    LIBS        += /home/ilian/MyLibs/libutils/lib/win32/libutilz.a
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StringFighter_TheWordWarrior
TEMPLATE = app
RESOURCES += application.qrc
#
SOURCES += \
    libs/miniz/miniz.c \
    src/MainWindow.cpp \
    src/ActionRectItem.cpp \
    src/TextNodes.cpp \
    src/AssetManager.cpp \
    src/WindowFrame.cpp \
    src/Callbacks.cpp \
    src/FModePlayer.cpp \
    src/ActionItem.cpp \
    src/SelectionMenu.cpp \
    src/ZooGame.cpp \
    src/StringOv.cpp

HEADERS  += \
    src/MainWindow.h \
    src/ActionRectItem.h \
    src/TextNodes.h \
    src/AssetManager.h \
    src/WindowFrame.h \
    src/LayoutFactory.h \
    src/Callbacks.h \
    src/FModePlayer.h \
    src/ActionItem.h \
    src/SelectionMenu.h \
    src/ZooGame.h \
    src/StringOv.h

