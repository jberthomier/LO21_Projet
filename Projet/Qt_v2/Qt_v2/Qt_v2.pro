QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
QT += xml

SOURCES += \
    main.cpp \
    date.cpp \
    note.cpp

HEADERS += \
    date.h \
    note.h
