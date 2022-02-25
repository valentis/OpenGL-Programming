#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Bitmap");
    resize(600, 600);
}

Widget::~Widget( )
{

}

void Widget::initializeGL( )
{
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );

    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    static GLubyte bitmap[ ] = {
        0x07, 0xe0, 0x18, 0x18, 0x20, 0x04, 0x43, 0xc2,
        0x44, 0x22, 0x88, 0x11, 0x81, 0x81, 0x81, 0x81,
        0x80, 0x01, 0x80, 0x01, 0x92, 0x49, 0x4c, 0x32,
        0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xe0,
    };
    glClear(GL_COLOR_BUFFER_BIT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    glColor3f(1,1,0);
    glRasterPos2f(0.5,0.5);
    glBitmap(16,16,0,0,20,0,bitmap);
    glBitmap(16,16,0,0,20,0,bitmap);
    glBitmap(16,16,0,10,20,0,bitmap);
    glFlush( );
}

