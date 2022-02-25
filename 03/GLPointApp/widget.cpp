#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Point");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 0.0);

    GLfloat range[2], granu;
    glGetFloatv(GL_LINE_WIDTH_RANGE, range);
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &granu);

    qDebug("%f %f %f", range[0], range[1], granu);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity( );			 // 단위 행렬(행렬 스택) 초기화
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_POINT_SMOOTH);
    glColor3f(1.0, 1.0, 1.0);   // R, G, B 색상 : 흰색
    glPointSize(10.0);
#if 1
    /*
    GLfloat w = 1, y;
    for (y = 0.8; y > -0.8;y -= 0.2) {
         glLineWidth(w++);
         glBegin(GL_LINES);
         glVertex2f(-0.8, y);
         glVertex2f(0.8, y);
         glEnd( );
    };
*/
    double rad = 0.5;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i+=10) {
        double angle, x, y;
        angle = i*3.141592 / 180;
        x = rad*cos(angle);
        y = rad*sin(angle);
        glVertex2f(x, y);
    }

#else
    glBegin(GL_POINTS);
    {
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
    }
#endif
    glEnd( );

    glFlush( );
}
