#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    nx = 0, ny = 0;
    bScissor = false;
    bStencil = false;
    bEqual = false;
    setWindowTitle("OpenGL Stencil");
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
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 가위 테스트 속성 설정
    if (bScissor)
        glEnable(GL_SCISSOR_TEST);
    else
        glDisable(GL_SCISSOR_TEST);
    glScissor(10, 10, 150, 150);

    if (bStencil)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);

    // 스탠실 버퍼에 마킹만 한다.
    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    // 수평 선 그음
    glColor3f(1, 1, 1);
    GLint arFac[] = { 1,   1,   1,   2,   3,   4,   2,   3,   2};
    GLushort arPat[]={0xaaaa, 0x33ff, 0x57ff, 0xaaaa, 0xaaaa,
                      0xaaaa, 0x33ff, 0x33ff, 0x57ff };
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(3);
    GLfloat y;
    GLint idx = 0;

    for (y = 0.8; y > -0.8;y -= 0.2) {
        glLineStipple(arFac[idx], arPat[idx]);
        glBegin(GL_LINES); {
            glVertex2f(-0.8, y);
            glVertex2f(0.8, y);
        }
        glEnd( );
        idx++;
    }

    // 스텐실 값과 비교하여 특정 영역에만 출력한다.
    glStencilFunc(bEqual?GL_EQUAL:GL_NOTEQUAL, 0x1, 0xFF);

    // nx, ny 위치에 삼각형 그림
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
      glVertex2f(nx + 0.0, ny + 0.5);
      glVertex2f(nx -0.5, ny - 0.5);
      glVertex2f(nx + 0.5, ny - 0.5);
    glEnd( );

    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_1:         // Scissor ON
        bScissor=true;
        break;
    case Qt::Key_2:         // Scissor OFF
        bScissor=false;
        break;
    case Qt::Key_3:         // Stencil ON
        bStencil=true;
        break;
    case Qt::Key_4:         // Stencil OFF
        bStencil=false;
        break;
    case Qt::Key_5:         // Equal
        bEqual=true;
        break;
    case Qt::Key_6:         // Not Equal
        bEqual=false;
        break;
    case Qt::Key_A:
        nx -= 0.1;
        break;
    case Qt::Key_S:
        nx += 0.1;
        break;
    case Qt::Key_D:
        ny += 0.1;
        break;
    case Qt::Key_F:
        ny -= 0.1;
        break;
    };

    update( );
}
