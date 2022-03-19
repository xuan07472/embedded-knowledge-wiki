TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../group_buf_queue/arch_buffer_config.c \
    ../../group_buf_queue/group_buf_queue.c \
    ../../group_buf_queue/group_buf_queue_init.c \
    ../../group_buf_queue/pair_list.c \
    ../module.c \
    ../module1.c \
    ../module2.c \
    ../module3.c \
    ../module_queue.c \
    ../module_unitest.c

HEADERS += \
    ../../group_buf_queue/arch_buffer_config.h \
    ../../group_buf_queue/group_buf_queue.h \
    ../../group_buf_queue/group_buf_queue_init.h \
    ../../group_buf_queue/list.h \
    ../../group_buf_queue/pair_list.h \
    ../module.h \
    ../module_queue.h

INCLUDEPATH += ../../group_buf_queue
