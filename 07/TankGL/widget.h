#ifndef WIDGET_H
#define WIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include <QtOpenGL>
#include <QtOpenGLWidgets>

#ifdef __APPLE__    // Mac OS X인 경우
  #include <OpenGL/glu.h>
#else                // Linux 등의 OS인 경우
  #include <GL/glu.h>
#endif

struct bullet
{
    float ypos;
    float xpos;
    float speed;
    bullet *next;
};

struct enemy
{
    float ypos;
    float xpos;
    float speed;
    enemy *next;
};

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void updateBullet();
    void updateEnemy();
    int loadGLTextures();

    GLuint  filter;             // Which Filter To Use
    GLuint  texture[4];         // Storage For 3 Textures
    GLuint  base;

    bullet *headB;
    bullet *tailB;
    bullet *currentB;

    bool firstShot;
    bool enemyAround;
    float tankPosHoriz;
    float lastShot;
    float newShot;
    float lastMove, newMove;

    enemy normalEnemy;

    GLUquadricObj *quadratic;

    QTimer timer;

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *);

private slots:
    void updateTimer();
};

#endif // WIDGET_H
