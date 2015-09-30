TEMPLATE = app

QT += qml quick widgets network

HEADERS += pubnub_qt.h pubnub_qt_gui_sample.h
SOURCES += main.cpp pubnub_qt.cpp pubnub_qt_gui_sample.cpp $$PWD/../c-core/core/pubnub_ccore.c $$PWD/../c-core/core/pubnub_assert_std.c $$PWD/../c-core/core/pubnub_json_parse.c $$PWD/../c-core/core/pubnub_helper.c

#RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../c-core/core
DEPENDPATH += $$PWD/../c-core/core

#RESOURCES += \
#    dashboard.qrc

OTHER_FILES += \
    dashboard.qml

#OTHER_FILES += \
#    qml/dashboard.qml \
#    qml/DashboardGaugeStyle.qml \
#    qml/IconGaugeStyle.qml \
#    qml/TachometerStyle.qml \
#    qml/TurnIndicator.qml \
#    qml/ValueSource.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/pubnub_qt
INSTALLS += target

# Default rules for deployment.
include(deployment.pri)

