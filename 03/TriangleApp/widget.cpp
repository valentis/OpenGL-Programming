#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_mode(0)
{
    setWindowTitle("OpenGL Triangles");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions();
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
    GLfloat x = -0.8;
    GLfloat y = 0.4;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);   // R, G, B 색상 : 흰색

    if(m_mode == 0) {
        glBegin(GL_TRIANGLES);
            for (int i = 0; i < 6; i++) {
                glVertex2f(x, y);
                x += 0.3;
                y *= -1;
            };
        glEnd( );
    } else if(m_mode == 1) {
        glShadeModel(GL_FLAT);
        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < 6; i++) {
                (i % 2 == 0)?glColor3f(1.0, 0.0, 0.0):glColor3f(0.0, 1.0, 0.0);
                glVertex2f(x, y);
                x += 0.3;
                y *= -1;
            };
        glEnd( );
    } else if(m_mode == 2) {
        glShadeModel(GL_FLAT);
        glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.0, 0.5);
            glVertex2f(-0.35, 0.35);

            glColor3f(0.0, 1.0, 0.0);
            glVertex2f(-0.5, 0.0);

            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(-0.35, -0.35);

            glColor3f(0.0, 1.0, 0.0);
            glVertex2f(0.0, -0.5);
       glEnd( );
    }
    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_1:
        m_mode = 0;
        break;
    case Qt::Key_2:
        m_mode = 1;
        break;
    case Qt::Key_3:
        m_mode = 2;
        break;
    }
    update();
}



