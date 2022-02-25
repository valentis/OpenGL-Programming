#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Rectangles");
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);   // R, G, B 색상 : 흰색
    glShadeModel(GL_FLAT);
    GLfloat x = -0.9;
    GLfloat y = 0.3;


    if(m_mode == 0) {
       glRectf(-0.8, 0.8, 0.8, -0.8);
    } else if(m_mode == 1) {
        glBegin(GL_QUADS);
            for (int i = 0; i < 8; i++) {
                if (i < 4) {
                    glColor3f(1.0, 0.0, 0.0);
                } else {
                    glColor3f(0.0, 1.0, 0.0);
                }
                glVertex2f(x, y);
                if (i % 2 == 1) x += 0.6;
                if (i != 1 && i != 5) y *= -1;
            }
        glEnd( );
    } else if(m_mode == 2) {
        glBegin(GL_QUAD_STRIP);
            for (int i = 0; i < 8; i++) {
                if (i < 4 || i > 5) {
                    glColor3f(1.0, 0.0, 0.0);
                } else {
                    glColor3f(0.0, 1.0, 0.0);
                }
                glVertex2f(x, y);
                if (i % 2 == 1) x += 0.6;
                y *= -1;
            }
        glEnd( );
    } else if(m_mode == 3) {
        x = -0.89;

        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < 8; i++) {
                if (i < 4 || i > 5) {
                    glColor3f(1.0, 0.0, 0.0);
                } else {
                    glColor3f(0.0, 1.0, 0.0);
                }
                glVertex2f(x, y);
                if (i % 2 == 1) x += 0.6;
                y *= -1;
            }
        glEnd( );
    } else if(m_mode == 4) {
        glBegin(GL_POLYGON);
            glVertex2f(0.0, 0.5);
            glVertex2f(-0.5, 0.0);
            glVertex2f(0.5, 0.0);
            glVertex2f(0.0, -0.5);
        glEnd( );
    };
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
    case Qt::Key_4:
        m_mode = 3;
        break;
    case Qt::Key_5:
        m_mode = 4;
        break;
    }
    update();
}
