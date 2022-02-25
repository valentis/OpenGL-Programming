#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    xAngle = 0, yAngle = 0, zAngle = 0;
    red = 0.5, green = 0.5, blue = 0.5;
    bColorTrack = GL_FALSE;

    setWindowTitle("OpenGL Material");
    resize(300, 300);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    // 주변광 설정
    glEnable(GL_LIGHTING);
    GLfloat arLight[]={red, green, blue, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, arLight);
    if (bColorTrack) {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT);
    } else {
        glDisable(GL_COLOR_MATERIAL);
    }

    glPushMatrix( );
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    // 아랫면 흰 바닥면
    GLfloat arbottom[]={1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, arbottom);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
       glVertex2f(-0.5, 0.5);
       glVertex2f(0.5, 0.5);
       glVertex2f(0.5, -0.5);
       glVertex2f(-0.5, -0.5);
    glEnd( );

    GLfloat arMat1[]={1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, arMat1);
    glBegin(GL_TRIANGLE_FAN);
       // 위쪽 빨간면
       glColor3f(1, 1, 1);
       glVertex3f(0.0, 0.0, -0.8);
       glColor3f(1, 0, 0);
       glVertex2f(0.5, 0.5);
       glVertex2f(-0.5, 0.5);
       // 왼쪽 노란면
       GLfloat arMat2[]={0.0, 0.0, 0.5, 1.0};
       glMaterialfv(GL_FRONT, GL_AMBIENT, arMat2);
       glColor3f(1, 1, 0);
       glVertex2f(-0.5, -0.5);
       // 아래쪽 초록면
       GLfloat arMat3[]={0.0, 0.25, 0.0, 1.0};
       glMaterialfv(GL_FRONT, GL_AMBIENT, arMat3);
       glColor3f(0, 1, 0);
       glVertex2f(0.5, -0.5);
       // 오른쪽 파란면
       GLfloat arMat4[]={0.0, 0.0, 1.0, 1.0};
       glMaterialfv(GL_FRONT, GL_AMBIENT, arMat4);
       glColor3f(0, 0, 1);
       glVertex2f(0.5, 0.5);
    glEnd( );
    glPopMatrix( );
    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_Q:				// Color Tracking ON
        bColorTrack = GL_TRUE;
        break;
    case Qt::Key_W:				// Color Tracking OFF
        bColorTrack = GL_FALSE;
        break;
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
