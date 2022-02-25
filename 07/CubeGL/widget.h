#ifndef WIDGET_H
#define WIDGET_H

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QOpenGLShaderProgram>

extern const float cube_vertices[];
extern const unsigned short cube_indices[];
extern const char *sample_vertex_shader_src;
extern const char *sample_fragment_shader_src;

class Widget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget( );

private:
    void resizeGL(int width, int height);
    void initializeGL( );
    void paintGL( );

protected:
    QOpenGLShaderProgram m_sampleProgram;

    void mousePressEvent(QMouseEvent *e);
};

#endif // WIDGET_H
