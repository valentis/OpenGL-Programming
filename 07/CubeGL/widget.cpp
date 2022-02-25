#include <QTimer>

#include "widget.h"

const GLfloat cube_vertices[] = {
    -1.0f,-1.0f,1.0f,  1.0f,-1.0f,1.0f, 1.0f,1.0f,1.0f, -1.0f,1.0f,1.0f,
    -1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,1.0f,-1.0f, -1.0f,1.0f,-1.0f };

const GLushort cube_indices[]= {
    0,1,2, 0,2,3, 1,5,6, 1,6,2, 4,0,3, 4,3,7, 5,4,7,
    5,7,6, 4,5,1, 4,1,0, 2,6,7, 2,7,3 };

const char *sample_vertex_shader_src =
        "attribute highp vec4 vertex;\n"
        "uniform mediump mat4 matrix;\n"
        "uniform mediump mat4 proj;\n"
        "varying highp vec4 frag_pos;\n"
        "void main(void)\n"
        "{\n"
        "    frag_pos = matrix * vertex;\n"
        "    gl_Position = proj*frag_pos;\n"
        "}\n";

const char *sample_fragment_shader_src =
        "varying highp vec4 frag_pos;\n"
        "void main(void)\n"
        "{\n"
        "    mediump float light = 2.0 / -(frag_pos.z);\n"
        "    gl_FragColor = vec4(light, light, light, 0.5);\n"
        "}\n";

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    setAutoFillBackground( false );
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_NativeWindow);
//    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_StyledBackground,false);

    // Startup the timer which will call updateGL as fast as it can.
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout( )), this, SLOT(update( )));
    timer->start( );
}

Widget::~Widget( ) { }

void Widget::initializeGL( )
{
    initializeOpenGLFunctions( );

    // Create and compile the vertex-shader
    QOpenGLShader *vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertex_shader->compileSourceCode(sample_vertex_shader_src);

    // Create and compile the fragment-shader
    QOpenGLShader *fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fragment_shader->compileSourceCode(sample_fragment_shader_src);

    // Add vertex-shader to our program
    m_sampleProgram.addShader(vertex_shader);

    // Add fragment-shader to our program
    m_sampleProgram.addShader(fragment_shader);

    // Link our program. It's now ready for use.
    m_sampleProgram.link( );

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
};

void Widget::resizeGL(int width, int height)
{
    // Reset the GL viewport for current resolution.
    glViewport(0,0, width, height);
};

void Widget::paintGL( )
{
    // Clear the background and depth-buffer for this frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Get the attribute locations from the shaderprogram
    GLint vertexAttr = m_sampleProgram.attributeLocation("vertex");
    GLint matrixAttr = m_sampleProgram.uniformLocation("matrix");
    GLint projAttr = m_sampleProgram.uniformLocation("proj");

    // Set our own shaderprogram as an active one to GPU. There
    // can be only one active program at the time.
    m_sampleProgram.bind( );

    // Create the projection-matrix with QMatrix4x4
    QMatrix4x4 projection;

    // Use perspective projection
    projection.perspective(45.0f, (float)width( )/(float)height( ), 0.1f, 20.0f );
    // Set our newly created projection matrix to our shaderprogram
    // Set projection to the shader
    m_sampleProgram.setUniformValue( projAttr, projection );

    // Set vertexarray to the shaderprogram
    m_sampleProgram.enableAttributeArray(vertexAttr);
    m_sampleProgram.setAttributeArray(vertexAttr, cube_vertices, 3 );

    // Create orientation for the cube we are about to render
    QMatrix4x4 orientation;
    orientation.setToIdentity( );

    // 4.5 units away from camera
    orientation.translate(0.0f, 0.0f, -4.5f );

    // Spinning rotation
    static float ang = 0.0f;
    ang+=0.1f;

    // Rotations around 3 main axis. Angles changing in varying speed.
    orientation.rotate(ang, 1.0f, 0.0f, 0.0f );
    orientation.rotate(ang*0.7f, 0.0f, 1.0f, 0.0f );
    orientation.rotate(ang*1.4f, 0.0f, 0.0f, 1.0f );

    // Set orientation matrix to the shaderprogram
    m_sampleProgram.setUniformValue( matrixAttr, orientation );

    // draw the cube.
    glDrawElements(GL_TRIANGLES, 6*2*3, GL_UNSIGNED_SHORT, cube_indices);

    // Disable the program
    m_sampleProgram.disableAttributeArray(vertexAttr);
    m_sampleProgram.release( );

    glFlush();
};

void Widget::mousePressEvent(QMouseEvent *e) {
    qApp->quit( );
};
