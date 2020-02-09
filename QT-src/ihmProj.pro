QT       += core gui printsupport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datamodel.cpp \
    edge.cpp \
    emetteursignal.cpp \
    graphview.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    randomization/columngenerator.cpp \
    randomization/curve/curve.cpp \
    randomization/curve/distributioncurve.cpp \
    randomization/curve/exponentialcurve.cpp \
    randomization/curve/linearcurve.cpp \
    randomization/curve/noconstraintcurve.cpp \
    randomization/curve/restrictioncurve.cpp \
    randomization/curve/uniformcurve.cpp \
    randomization/distributive_law.cpp \
    randomization/exponentialdistribution.cpp \
    randomization/generation_dialog.cpp \
    randomization/linearconstraint.cpp \
    randomization/noconstraint.cpp \
    randomization/uniformdistribution.cpp \
    randomization/valueconstraint.cpp

HEADERS += \
    emetteursignal.h \
    datamodel.h \
    edge.h \
    graphview.h \
    mainwindow.h \
    node.h \
    datamodel.h \
    randomization/columngenerator.h \
    randomization/curve/curve.h \
    randomization/curve/distributioncurve.h \
    randomization/curve/exponentialcurve.h \
    randomization/curve/linearcurve.h \
    randomization/curve/noconstraintcurve.h \
    randomization/curve/restrictioncurve.h \
    randomization/curve/uniformcurve.h \
    randomization/distributive_law.h \
    randomization/exponentialdistribution.h \
    randomization/generation_dialog.h \
    randomization/linearconstraint.h \
    randomization/noconstraint.h \
    randomization/uniformdistribution.h \
    randomization/valueconstraint.h

FORMS += \
    mainwindow.ui \
    randomization/generation_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
