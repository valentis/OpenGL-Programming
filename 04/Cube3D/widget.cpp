#include "widget.h"

#define ONE 1

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    rotation = 0;
    drawInOrtho = GL_TRUE;

    setWindowTitle("OpenGL Cube");
    resize(300, 300);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout( )), SLOT(update( )));
    timer->start(250);
}

Widget::~Widget()
{
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-10, 10, -10, 10, -10, 10);

    glClearColor(0.5, 0.5, 0.5, 0.0);
}

void Widget::paintGL( )
{
    // 정육면체의 각 면들을 설정
    // 정육면체이기 때문에 6개의 face 를 설정했다.
    // 방향성 때문에 순서에 일관성이 있다.
    static GLubyte front[]  = {2,1,3,0}; //front face
    static GLubyte back[]   = {5,6,4,7}; //back face
    static GLubyte top[]    = {6,2,7,3}; //top face
    static GLubyte bottom[] = {1,5,0,4}; //bottom face
    static GLubyte left[]   = {3,0,7,4}; //left face
    static GLubyte right[]  = {6,5,2,1}; //right face

     // X,Y,Z 로 된 좌표(꼭지점)이다.
    // 예를 들면 face 에서 설정된 0 은 (-5,-5,-,5) 이다.
    static GLshort vertices[] = {-5,-5,-5,  5,-5,-5,  5,5,-5,
                       -5,5,-5,  -5,-5,5,   5,-5,5,   5,5,5,  -5,5,5};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

    if(!drawInOrtho)
      glTranslated(0, 0, -30);

    // Y 축 기준으로 45도 Rotate 한다.
    glRotated(45, ONE, 0, 0);
    glRotated(rotation++, 0, ONE,0);

    glEnableClientState(GL_VERTEX_ARRAY);
    // 사용할 vertex 를 등록
    glVertexPointer(3, GL_SHORT, 0, vertices);

    // 6개의 face 를 각각 Draw
    // 각 face 를 다른 색으로 표현한다.
    glColor4d(ONE,0,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4,
                      GL_UNSIGNED_BYTE, front);

    glColor4d(0,ONE,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4,
                       GL_UNSIGNED_BYTE, back);

    glColor4d(0,0,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, top);

    glColor4d(ONE,ONE,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, bottom);

    glColor4d(0,ONE,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, left);

    glColor4d(ONE,0,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, right);

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush( );
}



