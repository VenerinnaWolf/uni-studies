QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
win32: CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    docviewer.cpp \
    docwindow.cpp \
    explorer.cpp \
    filetabs.cpp \
    main.cpp \
    mainwindow.cpp \
    syntaxhighlighter.cpp

HEADERS += \
    docviewer.h \
    docwindow.h \
    explorer.h \
    filetabs.h \
    mainwindow.h \
    syntaxhighlighter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    highlightRules.xml

RESOURCES += \
    resourses.qrc
