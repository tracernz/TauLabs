TEMPLATE = lib
TARGET = ESC

QT += svg
QT += opengl
QT += serialport

include(../../taulabsgcsplugin.pri)
include(../../plugins/coreplugin/coreplugin.pri)
include(../../plugins/uavobjects/uavobjects.pri)
include(../../plugins/uavtalk/uavtalk.pri)
include(../../plugins/rawhid/rawhid.pri)

HEADERS += escgadget.h \
    escgadgetconfiguration.h \
    escgadgetfactory.h \
    escgadgetoptionspage.h \
    escgadgetwidget.h \
    escplugin.h \
	widgetbar.h \
    escserial.h \
    stm32.h

SOURCES += escgadget.cpp \
    escgadgetconfiguration.cpp \
    escgadgetfactory.cpp \
    escgadgetoptionspage.cpp \
    escgadgetwidget.cpp \
    escplugin.cpp \
	widgetbar.cpp \
    escserial.cpp \
    stm32.cpp

OTHER_FILES += ESC.pluginspec

FORMS += \
    esc.ui \
    escgadgetoptionspage.ui

RESOURCES += \
    esc.qrc




