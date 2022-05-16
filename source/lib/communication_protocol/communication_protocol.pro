TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -pthread
LIBS += -pthread

SOURCES += \
    communication_protocol_unitest.c
