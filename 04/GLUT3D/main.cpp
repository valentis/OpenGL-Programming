#include "widget.h"

#ifdef __APPLE__            // macOS인 경우
    #include <GLUT/glut.h>
#else                       // Linux 등의 OS인 경우
    #include <GL/glut.h>
#endif

#include <QApplication>

int main(int argc, char *argv[])
{
//    glutInit(&argc,argv);

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
