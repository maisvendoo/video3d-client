DEFINES += LIBRARY_LIB

TEMPLATE = lib

CONFIG -= qt

TARGET = library

DESTDIR = ../../lib

CONFIG(debug, debug|release) {

    TARGET = $$join(TARGET,,,_d)

} else {

}

INCLUDEPATH += ../include
INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)

