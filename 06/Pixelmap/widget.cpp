#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Pixelmap");
    resize(600, 600);
}

Widget::~Widget()
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

#if 0
void Widget::paintGL( )
{
    GLubyte data[32*32*3];
    for (int y=0;y<32;y++) {
        for (int x=0;x<32;x++) {
            data[y*32*3+x*3+0] = 0xff;     // R
            data[y*32*3+x*3+1] = 0xff;     // G
            data[y*32*3+x*3+2] = 0x00;     // B
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2f(0.0, 0.0);
    glDrawPixels(32, 32, GL_RGB, GL_UNSIGNED_BYTE, data);

    glFlush( );
}
#else
void Widget::paintGL( )
{
    GLubyte *data;
    glClear(GL_COLOR_BUFFER_BIT);
    QImage* image = new QImage("bmp_24.bmp");
    data = image->bits( );
    if (data != NULL) {
        glRasterPos2f(0.1, 0.1);
        glDrawPixels(image->width( ), image->height( ),
                     GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
    }

    glRasterPos2f(-0.9, -0.9);
    glCopyPixels(100, 100, 80, 50, GL_COLOR);

    glFlush( );
}
#endif

