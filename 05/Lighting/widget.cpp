#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    lx = 0, ly = 0, lz = -1.0;
    xAngle = 0, yAngle = 0, zAngle = 0;
    bAmbient = false;
    bAttach = false;
    setWindowTitle("OpenGL Lighting");
    resize(300, 300);
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

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix( );

//    glRotatef(180, 0.0f, 1.0f, 0.0f);
    if (bAttach) {
        glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
        glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
    }

    // 0번 광원 배치.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = {lx, ly, lz, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    // 주변광을 초록색으로 설정
    if (bAmbient) {
        GLfloat ambient[4]={0,1,0,1};
        glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    } else {
        GLfloat ambient[4]={0,0,0,1};
        glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    }

    if (bAttach == false) {
        glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
        glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
    }

    drawPyramid();

    glPopMatrix( );
    glFlush( );
}

void Widget::drawPyramid()
{
    // 아랫면 흰 바닥면
    glColor3f(1,1,1);
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
    //        glColor3f(1,1,1);
    glVertex3f(0.0, 0.0, -0.8);
    glColor3f(1,0,0);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);

    // 왼쪽 노란면
    //        glColor3f(1,1,0);
    glVertex2f(-0.5, -0.5);

    // 아래쪽 초록면
    //        glColor3f(0,1,0);
    glVertex2f(0.5, -0.5);

    // 오른쪽 파란면
    //        glColor3f(0,0,1);
    glVertex2f(0.5, 0.5);
    glEnd( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_1:          // Ambient ON
        bAmbient = GL_TRUE;
        break;
    case Qt::Key_2:         // Ambient OFF
        bAmbient = GL_FALSE;
        break;
    case Qt::Key_3:         // Attach light
        bAttach = GL_TRUE;
        break;
    case Qt::Key_4:         // Unattach light
        bAttach = GL_FALSE;
        break;

    case Qt::Key_A:
        yAngle += 2;
        break;
    case Qt::Key_S:
        yAngle -= 2;
        break;
    case Qt::Key_D:
        xAngle += 2;
        break;
    case Qt::Key_F:
        xAngle -= 2;
        break;
    case Qt::Key_G:
        zAngle += 2;
        break;
    case Qt::Key_H:
        zAngle -= 2;
        break;
    case Qt::Key_J:
        xAngle = yAngle = 0;
        zAngle = 180.0;
        break;

    case Qt::Key_Z:
        lx -= 0.1;
        break;
    case Qt::Key_X:
        lx += 0.1;
        break;
    case Qt::Key_C:
        ly += 0.1;
        break;
    case Qt::Key_V:
        ly -= 0.1;
        break;
    case Qt::Key_B:
        lz += 0.1;
        break;
    case Qt::Key_N:
        lz -= 0.1;
        break;
    case Qt::Key_M:
        lx = 0, ly = 0, lz = -1.0;
        break;
    };

    QString str;
    str.asprintf("x : %.1f, y : %.1f, z : %.1f", xAngle, yAngle, zAngle);
    setWindowTitle(str);

    update( );
}

