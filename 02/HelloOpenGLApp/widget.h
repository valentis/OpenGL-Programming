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
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;

private:
    // 사각형의 위치와 크기
    GLfloat rectPosX;
    GLfloat rectPosY;
    GLfloat rectSize;

    // 사각형의 이동 변위(속도) / 한번에 이동하는 픽셀 값
    GLfloat xStep;
    GLfloat yStep;

    // 화면의 크기
    GLfloat windowWidth;
    GLfloat windowHeight;

public slots:
    void timerFunction( );
};

#endif // WIDGET_H
