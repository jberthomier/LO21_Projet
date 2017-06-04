QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
QT += xml

SOURCES += \
    date.cpp \
    main.cpp \
    note.cpp \
    couple.cpp \
    relation.cpp \
    notemanager.cpp

HEADERS += \
    date.h \
    note.h \
    couple.h \
    relation.h \
    notemanager.h \
    relationmanager.h
