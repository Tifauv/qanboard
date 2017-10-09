TEMPLATE = lib
TARGET = qanboardcore
CONFIG += c++11 staticlib
DEFINES += QANBOARDCORE_LIBRARY

SOURCES += Task.cpp \
	TaskQueue.cpp \
	Workflow.cpp \
    WorkflowSerializer.cpp \
    XmlSerializer.cpp \
    WorkflowStorage.cpp \
    MemoryStorage.cpp \
    FileStorage.cpp
HEADERS += Task.h \
	TaskQueue.h \
	Workflow.h \
    WorkflowSerializer.h \
    XmlSerializer.h \
    WorkflowStorage.h \
    MemoryStorage.h \
    FileStorage.h
