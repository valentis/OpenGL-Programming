#ifndef WIDGET_H
#define WIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QList>

class QTimer;

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    enum snakeType {square, triangle, circle};
    enum game { go, stop };

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL( ) override;
    void paintGL( ) override;
    void resizeGL(int w, int h) override;
    void keyPressEvent(QKeyEvent *event)  override;

private:
    void drawRandomBlock( );
    void checkScore( );
    int checkCollision( );
    int randomMinMax(int min, int max = 0);

    double xpos, ypos;
    double blockX, blockY;
    int score;
    int key, lastKey;
    bool firsttime, firstpaint;

    QTimer timer;
    QString levelText;
    int timerInterval;

    QList<QPoint> snakeList;
    int snakeShape;

private slots:
    void updateTimer( );
};
#endif // WIDGET_H
