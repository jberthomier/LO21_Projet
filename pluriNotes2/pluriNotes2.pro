

TEMPLATE = app
TARGET = PluriNotes

QT += core \
      xml \
      multimedia \
      multimediawidgets \
      widgets \
      gui

SOURCES += \
    date.cpp \
    main.cpp \
    note.cpp \
    couple.cpp \
    relation.cpp \
    notemanager.cpp \
    plurinotes.cpp \
    affichagenote.cpp \
    articleediteur.cpp \
    noteediteur.cpp \
    tacheediteur.cpp \
    mediaediteur.cpp \
    player.cpp

HEADERS += \
    date.h \
    note.h \
    couple.h \
    relation.h \
    notemanager.h \
    relationmanager.h \
    plurinotes.h \
    affichagenote.h \
    articleediteur.h \
    noteediteur.h \
    tacheediteur.h \
    mediaediteur.h \
    player.h

FORMS += \
    plurinotes.ui
