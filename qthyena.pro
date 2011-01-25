TEMPLATE = app

TARGET = qthyena

QT += core \
    gui \
    opengl
    
HEADERS += qthyena.h \
    globals.h \
    environment.h \
    node.h \
    team.h \
    vect.h \
    indiv.h \
    pop.h \
    helper.h \
    window.h \
    widget.h \
    glwidget.h
    
SOURCES += qthyena.cpp \
    environment.cpp \
    indiv.cpp \
    main.cpp \
    node.cpp \
    pop.cpp \
    team.cpp \
    vect.cpp \
    glwidget.cpp \
    helper.cpp \
    widget.cpp \
    window.cpp
    
FORMS += qthyena.ui

RESOURCES += 
