TEMPLATE = lib
TARGET = qanboardcore
CONFIG += c++14 staticlib
DEFINES += QANBOARDCORE_LIBRARY

SOURCES += Task.cpp \
	TaskQueue.cpp \
	Workflow.cpp \
    WorkflowSerializer.cpp \
    XmlSerializer10.cpp \
    XmlSerializer20.cpp \
    WorkflowStorage.cpp \
    MemoryStorage.cpp \
    FileStorage.cpp \
    TaskMove.cpp \
    TaskRegistry.cpp \
    History.cpp \
    ConvertingSerializer.cpp
HEADERS += Task.h \
	TaskQueue.h \
	Workflow.h \
    WorkflowSerializer.h \
    XmlSerializer10.h \
    XmlSerializer20.h \
    WorkflowStorage.h \
    MemoryStorage.h \
    FileStorage.h \
    TaskMove.h \
    TaskRegistry.h \
    History.h \
    ConvertingSerializer.h
