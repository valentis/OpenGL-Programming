#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    xAngle = 0, yAngle = 0, zAngle = 0;
    bNormal = GL_TRUE;

    setWindowTitle("OpenGL Normal");
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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

    // 조명을 켠다.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix( );
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    glColor3ub(255, 255, 255);
    // 아랫면 흰 바닥
    glBegin(GL_QUADS);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(-0.5, -0.5);
    glEnd( );

    GLfloat normal[3];
    glColor3ub(128, 128, 128);
    // 위
    glBegin(GL_TRIANGLES);
        GLfloat up[3][3]= {
             {0.0, 0.0, -0.8},
             {0.5, 0.5, 0.0,},
             {-0.5, 0.5, 0.0},
        };
        getNormal(up[0], up[1], up[2], normal);
        if (bNormal) glNormal3fv(normal);
        glVertex3fv(up[0]);
        glVertex3fv(up[1]);
        glVertex3fv(up[2]);
        // 왼쪽
        GLfloat left[3][3]= {
             {0.0, 0.0, -0.8},
             {-0.5, 0.5, 0.0},
             {-0.5, -0.5, 0.0},
        };
        getNormal(left[0], left[1], left[2], normal);
        if (bNormal) glNormal3fv(normal);
        glVertex3fv(left[0]);
        glVertex3fv(left[1]);
        glVertex3fv(left[2]);
        // 아래
        GLfloat down[3][3]= {
             {0.0, 0.0, -0.8},
            {-0.5, -0.5, 0.0},
            {0.5, -0.5, 0.0},
       };
       getNormal(down[0], down[1], down[2], normal);
       if (bNormal) glNormal3fv(normal);
       glVertex3fv(down[0]);
       glVertex3fv(down[1]);
       glVertex3fv(down[2]);
       // 오른쪽
       GLfloat right[3][3]= {
            {0.0, 0.0, -0.8},
            {0.5, -0.5, 0.0},
            {0.5, 0.5, 0.0},
       };
       getNormal(right[0], right[1], right[2], normal);
       if (bNormal) glNormal3fv(normal);
       glVertex3fv(right[0]);
       glVertex3fv(right[1]);
       glVertex3fv(right[2]);

   glEnd( );
   glPopMatrix( );
   glFlush( );
}

void Widget::getNormal(GLfloat a[3], GLfloat b[3], GLfloat c[3],
GLfloat normal[3])
{
    GLfloat ba[3];
    GLfloat ca[3];
    GLfloat n[3];
    // 두 정점간의 벡터 계산
    ba[0]=b[0]-a[0];ba[1]=b[1]-a[1];ba[2]=b[2]-a[2];
    ca[0]=c[0]-a[0];ca[1]=c[1]-a[1];ca[2]=c[2]-a[2];
    // 외적 구함
    n[0]=ba[1]*ca[2]-ca[1]*ba[2];
    n[1]=ca[0]*ba[2]-ba[0]*ca[2];
    n[2]=ba[0]*ca[1]-ca[0]*ba[1];
    // 정규화
    GLfloat l=sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    normal[0]=n[0]/l;normal[1]=n[1]/l;normal[2]=n[2]/l;
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {
    case Qt::Key_Q:				// Normal ON
        bNormal = GL_TRUE;
        break;
    case Qt::Key_W:			// Normal OFF
        bNormal = GL_FALSE;
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
    };

    QString str;
    str.asprintf("x : %.1f, y : %.1f, z : %.1f", xAngle, yAngle,
                 zAngle);
    setWindowTitle(str);

    update( );
}

