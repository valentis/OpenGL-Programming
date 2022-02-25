#ifndef WIDGET_H
#define WIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include <QtOpenGL>
#include <QtOpenGLWidgets>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void initializeGL( ) override;
    void paintGL( ) override;
    void resizeGL(int w, int h) override;

    void drawPyramid( );

    GLfloat xAngle, yAngle, zAngle;
    GLfloat left, right, bottom, top, bNear, bFar;
    GLsizei lastWidth, lastHeight;
    GLfloat fov;
    int bProjection;
    int bObject;
};

#endif // WIDGET_H
