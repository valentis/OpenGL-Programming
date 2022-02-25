#ifdef __APPLE__    // macOS인 경우
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else                      // Linux 등의 OS인 경우
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    xAngle = 0, yAngle = 0, zAngle = 0;
    red = 1.0, green = 1.0, blue = 1.0;

    setWindowTitle("OpenGL LightModel");
    resize(300, 300);
}

Widget::~Widget( )
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    // 조명 모델 설정
    glEnable(GL_LIGHTING);
    GLfloat arLight[]={red, green, blue, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, arLight);

    glPushMatrix( );
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

//    drawPyramid();
    glutSolidTeapot(0.5);

    glPopMatrix( );
    glFlush( );
}

void Widget::drawPyramid()
{
    // 아랫면 흰 바닥면
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
#if 1
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(-0.5, -0.5);
#else
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
#endif
    glEnd( );

    glBegin(GL_TRIANGLE_FAN);
        // 위쪽 빨간면
        glColor3f(1,1,1);
        glVertex3f(0.0, 0.0, -0.8);
        glColor3f(1,0,0);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);

        // 왼쪽 노란면
        glColor3f(1,1,0);
        glVertex2f(-0.5, -0.5);

        // 아래쪽 초록면
        glColor3f(0,1,0);
        glVertex2f(0.5, -0.5);

        // 오른쪽 파란면
        glColor3f(0,0,1);
        glVertex2f(0.5, 0.5);
    glEnd( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_1:
        yAngle += 2;
        break;
    case Qt::Key_2:
        yAngle -= 2;
        break;
    case Qt::Key_3:
        xAngle += 2;
        break;
    case Qt::Key_4:
        xAngle -= 2;
        break;
    case Qt::Key_5:
        zAngle += 2;
        break;
    case Qt::Key_6:
        zAngle -= 2;
        break;
    case Qt::Key_0:
        xAngle = yAngle = zAngle = 0.0;
        break;
    case Qt::Key_A:
        red += 0.1;
        break;
    case Qt::Key_S:
        red -= 0.1;
        break;
    case Qt::Key_D:
        green += 0.1;
        break;
    case Qt::Key_F:
        green -= 0.1;
        break;
    case Qt::Key_G:
        blue += 0.1;
        break;
    case Qt::Key_H:
        blue -= 0.1;
        break;
    case Qt::Key_J:
        red = 0.5, green = 0.5, blue = 0.5;
        break;
    };

    QString str;
    str.asprintf("(%.0f,%.0f,%.0f)"
                 "(%.1f,%.1f,%.1f)",
                 xAngle, yAngle, zAngle,
                 red, green, blue);
    setWindowTitle(str);

    update( );
}
