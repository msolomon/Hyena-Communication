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
    pop.h \
    widget.h \
    drawhelper.h \
    playback.h \
    types.h \
    agent_info.h \
    indiv_nn.h \
    indiv_base.h \
    weightset.h \
    indiv.h
    
SOURCES += qthyena.cpp \
    environment.cpp \
    main.cpp \
    node.cpp \
    pop.cpp \
    team.cpp \
    vect.cpp \
    widget.cpp \
    drawhelper.cpp \
    playback.cpp \
    globals.cpp \
    indiv_nn.cpp \
    indiv_base.cpp \
    indiv.cpp
    
FORMS += qthyena.ui \
    playback.ui

RESOURCES += 

LIBS += -lRandom

win32 {
    LIBS += -lacml_dll
}

unix {
    LIBS += -ltcmalloc_minimal -lacml
}

CONFIG(release):
QMAKE_CXXFLAGS_RELEASE += -march=amdfam10 -flto
QMAKE_LFLAGS += -march=amdfam10 -flto -fwhole-program

#CONFIG(release, debug|release):
#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg
