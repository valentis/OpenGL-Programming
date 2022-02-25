#include "widget.h"

#include <QTimer>

#ifdef __APPLE__    // macOS인 경우
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else                      // Linux 등의 OS인 경우
#include <GL/glut.h>
#include <GL/glu.h>
#endif

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_isFogOn(GL_TRUE)
{
    setWindowTitle("OpenGL Fog");
    resize(900, 900);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]{ m_angle++; m_dist++; update(); });
    timer->start(1000/60);
}

Widget::~Widget()
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
    float position[] = {1.0f,1.0f,0.0f,1.0f};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluPerspective(45, width()/height(), 1, 100); //set in perspective projection
}

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW); //set the modelview matrix
    glLoadIdentity(); //reset the modelview matrix
    gluLookAt(0.0, 0.75f, 8.0, 0, 0, 0.0, 0.0f, 1.0f, 0.0f); //set the camera

    (m_isFogOn)?glEnable(GL_FOG):glDisable(GL_FOG);

    float fogColour[] = {0.5f, 0.5f, 0.5f, 1};
    glFogfv(GL_FOG_COLOR, fogColour);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glHint (GL_FOG_HINT, GL_NICEST);  /*  per pixel  */
    glFogf(GL_FOG_START, -10.0f+(m_dist/20)%40);
    glFogf(GL_FOG_END, 20.0f+(m_dist/20)%40);

    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat redColor[4] = {1,0,0,1};
    GLfloat whiteColor[4] = {1,1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteColor);
    glPushMatrix();
    glRotatef(m_angle, 0, 1, 0);

    glutSolidTeapot(1);
    glPopMatrix();

    glTranslatef(3, 0, -9);
    glRotatef(m_angle++, 1, 1, 1);
    glutSolidTeapot(1);

    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    m_isFogOn = (event->key() == Qt::Key_A)?GL_TRUE:GL_FALSE;
    update();
}
