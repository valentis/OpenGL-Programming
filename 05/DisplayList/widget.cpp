#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL DisplayList");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL( )
{
    qDebug("initializeGL");
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 1.0);
    dl = glGenLists(1);
    glNewList(dl, GL_COMPILE);
    {
        glBegin(GL_TRIANGLES);
        {
            glVertex2f(0.0, 0.2);
            glVertex2f(-0.2, -0.2);
            glVertex2f(0.2, -0.2);
        }
        glEnd();
    }
    glEndList();
}

void Widget::resizeGL(int w, int h)
{
    qDebug("resizeGL");
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    qDebug("paintGL");

   glClear(GL_COLOR_BUFFER_BIT);
/*
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity( );
*/
   glPushMatrix();
   glColor3f(1, 0, 0);
   glCallList(dl);

   glTranslatef(0.2, 0.0, 0.0);
   glColor3f(0, 1, 0);
   glCallList(dl);

   glTranslatef(0.2, 0.0, 0.0);
   glColor3f(0, 0, 1);
   glCallList(dl);
   glPopMatrix();

   glFlush( );
}
