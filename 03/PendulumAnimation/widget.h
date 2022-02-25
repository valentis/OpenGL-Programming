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
    Widget(QWidget *parent = 0);
    ~Widget( );

    double radius;
    double delta_theta, cord_length;
    double xcenter, ycenter;
    double x, y, theta;
    double current_angle, atime;

 private:
     void initializeGL( );
     void paintGL( );
     void resizeGL(int w, int h);

 public slots:
     void timerFunction( );
};

#endif // WIDGET_H
