TEMPLATE = lib
TARGET = qanboardcore
CONFIG += c++14 staticlib
DEFINES += QANBOARDCORE_LIBRARY

SOURCES += Task.cpp \
	TaskQueue.cpp \
	Workflow.cpp \
    WorkflowSerializer.cpp \
    XmlSerializer.cpp \
    WorkflowStorage.cpp \
    MemoryStorage.cpp \
    FileStorage.cpp \
    TaskMove.cpp \
    TaskRegistry.cpp \
    History.cpp
HEADERS += Task.h \
	TaskQueue.h \
	Workflow.h \
    WorkflowSerializer.h \
    XmlSerializer.h \
    WorkflowStorage.h \
    MemoryStorage.h \
    FileStorage.h \
    TaskMove.h \
    TaskRegistry.h \
    History.h
