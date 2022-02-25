QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qtglut.cpp \
    widget.cpp

HEADERS += \
    qtglut.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

windows {
#    LIBS +=  -lfreeglut -L\Qt\6.2.3\mingw_64\lib\x64 -static -lgdi32 -lwinmm -lopengl32
}

mac {
#    LIBS += -framework GLUT
}
