TEMPLATE = app

TARGET = qthyena

QT += core \
#    opengl \
    gui

#CONFIG += debug
    
HEADERS += qthyena.h \
    globals.h \
    environment.h \
    node.h \
    team.h \
    vect.h \
    indiv.h \
    pop.h \
    widget.h \
    drawhelper.h \
    playback.h \
    types.h
    
SOURCES += qthyena.cpp \
    environment.cpp \
    indiv.cpp \
    main.cpp \
    node.cpp \
    pop.cpp \
    team.cpp \
    vect.cpp \
    widget.cpp \
    drawhelper.cpp \
    playback.cpp \
    globals.cpp
    
FORMS += qthyena.ui \
    playback.ui

RESOURCES += 

LIBS += -lRandom

#CONFIG(release, debug|release):
#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg
