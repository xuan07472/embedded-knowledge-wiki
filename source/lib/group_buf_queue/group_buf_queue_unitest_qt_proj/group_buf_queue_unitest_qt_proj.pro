TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../arch_buffer_config.c \
    ../group_buf_queue.c \
    ../group_buf_queue_init.c \
    ../group_buf_queue_unitest.c \
    ../module_buf_queue.c \
    ../pair_list.c

DISTFILES += \
    ../group_buf_queue_demo.exe

HEADERS += \
    ../arch_buffer_config.h \
    ../group_buf_queue.h \
    ../group_buf_queue_init.h \
    ../list.h \
    ../pair_list.h
