#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    qDebug("Widget::Widget");
    act = 0;
    setWindowTitle("OpenGL Modeling");
    resize(600, 600);
}

Widget::~Widget()
{
    qDebug("Widget::~Widget");
}

void Widget::initializeGL( )
{
    qDebug("Widget::initializeGL");
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Widget::resizeGL(int w, int h)
{
    qDebug("Widget::resizeGL");
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    qDebug("Widget::paintGL");
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
 //   glLoadIdentity( );

    if(act == 0) {
        glPushMatrix( );
        drawObj();
        glTranslatef(0.6, 0.0, 0.0);
        drawObj();
        glTranslatef(0.0, 0.6, 0.0);
        drawObj();
        glPopMatrix( );
    } else if(act == 1) {      // Translate
        drawObj();

        glPushMatrix( );
            glTranslatef(0.6, 0.0, 0.0);
            drawObj();
//            glLoadIdentity( );
        glPopMatrix( );

        glPushMatrix( );
            glTranslatef(0.0, 0.6, 0.0);
            drawObj();
        glPopMatrix( );
    } else if(act == 2) {      // Scale
        glPushMatrix( );
        glScalef(2.0, -3.0, 0);
        drawObj();
        glPopMatrix( );
    } else if(act == 3) {       // Rotate
        glPushMatrix( );
        glRotatef(45.0, 0.0, 0.0, 1.0);
        drawObj();
        glPopMatrix( );
    } else if(act == 4) {       // Scale & Translate
        glPushMatrix( );
        glTranslatef(0.5, 0.5, 0.0);
        glScalef(2.0, 2.0, 1.0);
        drawObj();
        glPopMatrix( );
    } else if(act == 5) {       // Scale & Translate
        glPushMatrix( );
        glScalef(2.0, 2.0, 1.0);
        glTranslatef(0.5, 0.5, 0.0);
        drawObj();
        glPopMatrix( );
    } else if(act == 6) {      // Rotate & Translate
        glPushMatrix( );
            glColor3f(1.0, 1.0, 1.0);
            drawObj2();
            glRotatef(45, 0.0, 0.0, 1.0);
            glColor3f(1.0, 1.0, 0.0);
            drawObj2();
        glPopMatrix( );
    } else if(act == 7) {      // Rotate & Translate
        glPushMatrix( );
            glColor3f(1.0, 1.0, 1.0);
            drawObj2();
            glTranslatef(0.5, 0.5, 0.0);
            glRotatef(45, 0.0, 0.0, 1.0);
            glTranslatef(-0.5, -0.5, 0.0);
            glColor3f(1.0, 1.0, 0.0);
            drawObj2();
        glPopMatrix( );
    }
    glFlush();
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

void Widget::drawObj2()
{
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(0.5, 0.8);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.8, 0.2);
    }
    glEnd();
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_Z:
        break;
    case Qt::Key_1:
        act = 0;
        break;
    case Qt::Key_2:
        act = 1;
        break;
    case Qt::Key_3:
        act = 2;
        break;
    case Qt::Key_4:
        act = 3;
        break;
    case Qt::Key_5:
        act = 4;
        break;
    case Qt::Key_6:
        act = 5;
        break;
    case Qt::Key_7:
        act = 6;
        break;
    case Qt::Key_8:
        act = 7;
        break;
    case Qt::Key_9:
        act = 8;
        break;
    case Qt::Key_0:
        act = 9;
        break;
    };

    update( );
}

