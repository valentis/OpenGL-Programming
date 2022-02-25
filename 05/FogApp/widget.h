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

private:
    void keyPressEvent(QKeyEvent *event) override;

    void initializeGL( ) override;
    void paintGL( ) override;
    void resizeGL(int w, int h) override;

    int m_angle = 0, m_dist = 0;
    bool m_isFogOn;
};
#endif // WIDGET_H
