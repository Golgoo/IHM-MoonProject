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
    customgenerator.cpp \
    datamodel.cpp \
    edge.cpp \
    emetteursignal.cpp \
    geneerrordialog.cpp \
    generator.cpp \
    graphview.cpp \
    integergenerator.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    random_generation_dialog.cpp \
    randomization/columngenerator.cpp \
    randomization/distributive_law.cpp \
    randomization/exponentialdistribution.cpp \
    randomization/generation_dialog.cpp \
    randomization/linearconstraint.cpp \
    randomization/noconstraint.cpp \
    randomization/uniform_curve.cpp \
    randomization/uniformdistribution.cpp \
    randomization/valueconstraint.cpp

HEADERS += \
    emetteursignal.h \
    customgenerator.h \
    datamodel.h \
    edge.h \
    geneerrordialog.h \
    generator.h \
    graphview.h \
    integergenerator.h \
    mainwindow.h \
    node.h \
    datamodel.h \
    random_generation_dialog.h \
    randomization/columngenerator.h \
    randomization/distributive_law.h \
    randomization/exponentialdistribution.h \
    randomization/generation_dialog.h \
    randomization/linearconstraint.h \
    randomization/noconstraint.h \
    randomization/uniform_curve.h \
    randomization/uniformdistribution.h \
    randomization/valueconstraint.h

FORMS += \
    geneerrordialog.ui \
    mainwindow.ui \
    randomgenerationdialog.ui \
    randomization/generation_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
