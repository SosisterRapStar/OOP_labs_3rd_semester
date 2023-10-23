QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../protocol

SOURCES += \
    ../protocol/communicator.cpp \
    ../protocol/message.cpp \
    main.cpp \
    matrix.cpp \
    rational.cpp \
    serverapp.cpp

HEADERS += \
    ../protocol/communicator.h \
    ../protocol/headers.h \
    ../protocol/message.h \
    ../protocol/methods.h \
    matrix.h \
    number.h \
    rational.h \
    serverapp.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
