#include "widget.h"

#include <QTimer>
#include <QPoint>
#include <QRandomGenerator>

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    snakeShape = circle;
    setWindowTitle("OpenGL Sname Game");

    firstpaint = true;
    firsttime = true;
    timerInterval = 150;
    xpos = 0; ypos = 0;
    blockX = 0; blockY = 0;
    score = 0;
    key = Qt::Key_Right;
    lastKey = Qt::Key_Right;
    levelText = "Level : 1";
    snakeList.append(QPoint((int)xpos, (int)ypos));

    resize(640, 480);

    connect(&timer, SIGNAL(timeout( )), SLOT(updateTimer( )));
    timer.start(timerInterval);
}

Widget::~Widget( )
{
}

int Widget::randomMinMax(int min, int max)
{
    int random = QRandomGenerator::global()->generate();
    return (max)?random % (int)(max - min) + min:random % (int)(min);
}

void Widget::drawRandomBlock( )
{
    int neg = randomMinMax(-5, 5);
    blockX = randomMinMax(11) * 8 * (neg > 0 ? 1 : -1);
    neg = randomMinMax(-5, 5);
    blockY = randomMinMax(11) * 8 * (neg > 0 ? 1 : -1);
}

void Widget::checkScore( )
{
    if (score == 30) {
        timerInterval = 100;
        levelText = "Level : 2";
    } else if (score == 50) {
        timerInterval = 80;
        levelText = "Level : 3";
    } else if (score == 70) {
        timerInterval = 60;
        levelText = "Level : 4";
    } else if (score == 100) {
        timerInterval = 40;
        levelText = "Level : 5";
    } else if (score == 130) {
        timerInterval = 20;
        levelText = "Level : 6";
    } else if (score == 150) {
        timerInterval = 10;
        levelText = "Level : 7";
    }

    timer.setInterval(timerInterval);
}

int Widget::checkCollision( )
{
    if ((-80 + xpos) == blockX && 80 + ypos == blockY &&
            (-72 + xpos) == blockX + 8 && 72 + ypos == blockY - 8)
        return go;
    if ((-80 + xpos) >= 92 || (-80 + xpos) <= -100 ||
            (80 + ypos) >= 100 || (80 + ypos) <= -92)
        return stop;

    for (int i = 1; i < snakeList.count( ); i++) {
        if (xpos == snakeList[i].x( ) && ypos == snakeList[i].y( ))
            return stop;
    };

    return -1;
}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-100, 100, -100, 100, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glClearColor(1.0f, 1.0f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Widget::resizeGL(int width, int height)
{
    glViewport(0,0, width, height);
}

void Widget::paintGL( )
{
    QFont font;
    font.setPixelSize(14);

    QPainter painter(this);
    painter.setPen(Qt::darkMagenta);
    painter.setFont(font);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawText(30, 20, QString("Score : %1").arg(score));
    painter.setPen(Qt::blue);
    painter.drawText(width() - 100, 20, levelText);
    painter.end( );

    glPushMatrix( );
        glColor3f(1.0f, 0.0f, 0.0f);
        glRectf((float)blockX, (float)blockY, (float)blockX + 8, (float)blockY - 8);
    glPopMatrix( );

    for (int i = 0; i < snakeList.count( ); i++) {
        glPushMatrix( );
        glColor3f(0.0f, 0.0f, (i == 0)?1.0f:0.0f);
        glTranslated(snakeList[i].x( ), snakeList[i].y( ), 0);
        if (snakeShape == square) {
            glRectf(-80.0f, 80.0f, -72.0f, 72.0f);
        } else if (snakeShape == triangle) {
            glBegin(GL_TRIANGLES);
            glVertex2f(-80, 72);
            glVertex2f(-72, 72);
            glVertex2f(-76, 80);
            glEnd( );
        } else if (snakeShape == circle) {
            int r = 5;
            float delta_theta = 0.01f;
            glBegin(GL_POLYGON);
            for (float angle = 0; angle < 2 * M_PI; angle += delta_theta)
                glVertex3d(r * cos(angle) - 76, r * sin(angle) + 76, 0);
            glEnd( );
        }
        glPopMatrix( );
    }

    glFlush( );
}

void Widget::updateTimer( )
{
    QPoint p;
    glClear(GL_COLOR_BUFFER_BIT);

    checkScore( );

    if (firstpaint) {
        drawRandomBlock( );
        firstpaint = false;
    }

    if (checkCollision( ) == go) {
        score += 10;
        snakeList.append(QPoint(snakeList[snakeList.count( ) - 1].x( ),
                         snakeList[snakeList.count( ) - 1].y( )));
        drawRandomBlock( );
    } else if (checkCollision( ) == stop) {
        levelText = "Game Over!!";
        timer.stop( );
        update( );
        return;
    }

    switch (lastKey) {
    case Qt::Key_W:
    case Qt::Key_Up:
        for (int i = snakeList.count( ) - 1; i > 0; i--) {
            QPoint pp = snakeList[i - 1];
            snakeList[i] = pp;
        }
        p = snakeList[0];
        snakeList[0] = QPoint(p.x( ), p.y( ) + 8);
        ypos += 8;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        for (int i = snakeList.count( ) - 1; i > 0; i--) {
            QPoint pp = snakeList[i - 1];
            snakeList[i] = pp;
        }
        p = snakeList[0];
        snakeList[0] = QPoint(p.x( ), p.y( ) - 8);
        ypos -= 8;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        for (int i = snakeList.count( ) - 1; i > 0; i--) {
            QPoint pp = snakeList[i - 1];
            snakeList[i] = pp;
        }
        p = snakeList[0];
        snakeList[0] = QPoint(p.x( ) - 8, p.y( ));
        xpos -= 8;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        for (int i = snakeList.count( ) - 1; i > 0; i--) {
            QPoint pp = snakeList[i - 1];
            snakeList[i] = pp;
        };
        p = snakeList[0];
        snakeList[0] = QPoint(p.x( ) + 8, p.y( ));
        xpos += 8;
        break;
    }

    lastKey = key;

    update( );
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key( )) {
    case Qt::Key_X:
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    case Qt::Key_Escape:
        qApp->quit( );
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
    case Qt::Key_S:
    case Qt::Key_Down:
    case Qt::Key_A:
    case Qt::Key_Left:
    case Qt::Key_D:
    case Qt::Key_Right:
        if (firsttime) {
            timer.start(timerInterval);
            firsttime = false;
        }
        key = ev->key( );
        break;
    case Qt::Key_Pause:
    case Qt::Key_CapsLock:
        timer.stop( );
        break;
    case Qt::Key_Tab:
        timer.start(timerInterval);
        break;
    case Qt::Key_1:
        snakeShape = square;
        break;
    case Qt::Key_2:
        snakeShape = triangle;
        break;
    case Qt::Key_3:
        snakeShape = circle;
        break;
    default:
        break;
    };
}

