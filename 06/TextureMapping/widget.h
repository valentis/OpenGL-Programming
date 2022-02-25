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
    void initializeGL( );
    void paintGL( );
    void resizeGL(int w, int h);

     void keyPressEvent(QKeyEvent* event);

private:
    GLfloat xAngle, yAngle, zAngle;
    GLint EnvMode;
    GLint TexFilter;
};
#endif // WIDGET_H
