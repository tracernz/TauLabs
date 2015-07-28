TEMPLATE = lib
TARGET = STLoader

QT += svg
QT += opengl
QT += serialport

include(../../taulabsgcsplugin.pri)
include(../../plugins/coreplugin/coreplugin.pri)
include(../../plugins/uavobjects/uavobjects.pri)
include(../../plugins/uavtalk/uavtalk.pri)
include(../../plugins/rawhid/rawhid.pri)

HEADERS += \
    stm32.h \
    stloadergadget.h \
    stloadergadgetfactory.h \
    stloadergadgetwidget.h \
    stloaderplugin.h

SOURCES += \
    stm32.cpp \
    stloadergadget.cpp \
    stloadergadgetfactory.cpp \
    stloadergadgetwidget.cpp \
    stloaderplugin.cpp

OTHER_FILES += STLoader.pluginspec

FORMS += \
    stloader.ui

RESOURCES +=




