#include "widget.h"

#ifdef __APPLE__    // macOS인 경우
    #include <OpenGL/glu.h>
#else                     // Linux 등의 OS인 경우
    #include <GL/glu.h>
#endif

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    xAngle = yAngle = zAngle = 0;
    setWindowTitle("OpenGL GLU3D");
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);   // R, G, B 색상 : 흰색

    glPushMatrix( );
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    GLUquadricObj *pQuad;
    pQuad = gluNewQuadric( );
    gluQuadricDrawStyle(pQuad, GLU_LINE);

    gluSphere(pQuad, 0.3, 20, 20);

    glPushMatrix( );
    glTranslatef(-0.6, 0.6, 0.0);
    gluCylinder(pQuad, 0.2, 0.2, 0.5, 20, 20);
    glPopMatrix( );

    glPushMatrix( );
    glTranslatef(-0.6, -0.6, 0.0);
    gluCylinder(pQuad, 0.2, 0.0, 0.5, 20, 20);
    glPopMatrix( );

    glPushMatrix( );
    glTranslatef(0.6, 0.6, 0.0);
    gluDisk(pQuad, 0.1, 0.3, 10, 10);
    glPopMatrix( );

    glPushMatrix( );
    glTranslatef(0.6, -0.6, 0.0);
    gluDisk(pQuad, 0.0, 0.3, 10, 10);
    glPopMatrix( );

    gluDeleteQuadric(pQuad);
    glPopMatrix( );

    glFlush( );
}

