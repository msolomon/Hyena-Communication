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
    types.h \
    agent_info.h \
    indiv_nn.h
    
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
    globals.cpp \
    indiv_nn.cpp
    
FORMS += qthyena.ui \
    playback.ui

RESOURCES += 

LIBS += -lacml -lRandom

unix{
	LIBS += -ltcmalloc_minimal
}

CONFIG(release):
QMAKE_CXXFLAGS_RELEASE += -march=amdfam10 -flto
QMAKE_LFLAGS += -march=amdfam10 -flto -fwhole-program

#CONFIG(release, debug|release):
#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg
