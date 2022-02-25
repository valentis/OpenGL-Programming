#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    bEdge = GL_FALSE;
    setWindowTitle("OpenGL EdgeFlag3D");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL( )
{
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEdgeFlag(true);

    glBegin(GL_TRIANGLES);
      if (bEdge)
          glEdgeFlag(true);
      glVertex2f(0.0, 0.0);
      glVertex2f(-0.5, 0.5);
      if (bEdge)
          glEdgeFlag(false);
      glVertex2f(-0.5, -0.5);

      glVertex2f(0.0, 0.0);
      if (bEdge)  glEdgeFlag(true);
      glVertex2f(0.5, -0.5);
      glVertex2f(0.5, 0.5);

      if (bEdge)
          glEdgeFlag(false);
      glVertex2f(0.0, 0.0);
      if (bEdge)
          glEdgeFlag(true);
      glVertex2f(-0.5, -0.5);
      if (bEdge)
          glEdgeFlag(false);
      glVertex2f(0.5, -0.5);
    glEnd( );
    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_Up:
        bEdge = GL_TRUE;
        break;
    case Qt::Key_Down:
        bEdge = GL_FALSE;
        break;
    };
    update( );
}


