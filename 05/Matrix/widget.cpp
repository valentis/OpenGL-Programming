#include <cmath>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Matrix");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix( );

#if 0       // translate
    GLfloat trans[16] = {
         1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0.5, 0.5, 0, 1
    };
    glMultMatrixf(trans);
#endif

#if 0       // scale
    GLfloat scale[16] = {
         1.5, 0, 0, 0,
         0, 1.5, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1
    };
    glMultMatrixf(scale);
#endif

#if 1       // rotate
    GLfloat angle = 45.0;
    GLfloat value = angle * M_PI / 180;
    GLfloat rotate[16] = {
         cos(value), -sin(value), 0, 0,
         sin(value), cos(value), 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1
    };
    glMultMatrixf(rotate);
#endif

#if 0       // translate + scale
    GLfloat transScale[16] = {
         1.5, 0, 0, 0,
         0, 1.5, 0, 0,
         0, 0, 1, 0,
         0.5, 0.5, 0, 1
    };
    glMultMatrixf(transScale);
#endif

#if 0       // sheer
    GLfloat sheer[16] = {
        1, 0, 0, 0,
        0.5, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(sheer);
#endif

    drawObj();

    glPopMatrix( );
    glFlush( );
}

void Widget::drawObj()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(0.0, 0.2);
        glVertex2f(-0.2, -0.2);
        glVertex2f(0.2, -0.2);
    }
    glEnd();
}

