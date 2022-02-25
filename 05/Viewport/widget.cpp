#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    act = 1;

    setWindowTitle("OpenGL Viewport");
    resize(600, 600);
}

Widget::~Widget( )
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h)
{
    qDebug("resizeGL");
    lastWidth = w;
    lastHeight = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
//    glOrtho(-1, 1, -1, 1, -1, 1);
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    if (w > h) {
         glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 1.0, -1.0);
    } else {
         glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, 1.0, -1.0);
    }
}

void Widget::paintGL( )
{
    switch(act) {
    case 1:
        // 전체 창 사용
        glViewport(0, 0, lastWidth, lastHeight);
        break;
    case 2:
        // 좌하단 사용
        glViewport(0, 0, lastWidth/2, lastHeight/2);
        break;
    case 3:
        // 우하단 사용
        glViewport(lastWidth/2, 0, lastWidth/2, lastHeight/2);
        break;
    case 4:
        // 절대 크기 사용
        glViewport(30, 30, 200, 200);
        break;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);
    GLfloat aspect;

    if (lastWidth > lastHeight)
        aspect = (GLfloat)lastWidth / (GLfloat)lastHeight;
    else
        aspect = (GLfloat)lastHeight / (GLfloat)lastWidth;

    glRectf(-1.0*aspect, 1.0*aspect, 1.0*aspect, -1.0*aspect);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
    glEnd( );

    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
   qDebug("keyPressEvent");
    switch(event->key( )) {
    case Qt::Key_1:         // 전체 창 사용
        act = 1;
        break;
    case Qt::Key_2:         // 좌하단 사용
        act = 2;
        break;
    case Qt::Key_3:         // 우하단 사용
        act = 3;
        break;
    case Qt::Key_4:         // 절대 크기 사용
        act = 4;
        break;
    };

    resizeGL(width( ), height( ));
    update( );
}
