#include "widget.h"

#include <QTimer>
#include <cstdlib>      // 표준 라이브러리(표준 C 함수 집합)
#include <cmath>        // 수학 라이브러리(고등 수학 함수 )
#include <cstring>

#include "widget.h"

// alingment of boxes in which one can win
// We have 8 posiblities, 3 accross, 3 down and 2 diagnally
//
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
//
// row, colunm, diagnal information
static int box[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                        {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};


Widget::Widget(QWidget *parent)  : QOpenGLWidget(parent)
{
    view_state = 0;
    light_state = 0;

    setWindowTitle("X's and O's 3D");

    resize(500, 500);
    init_game( );

    connect(&timer, SIGNAL(timeout( )), SLOT(updateTimer( )));
    timer.start(10);
}

Widget::~Widget( )
{
}

// Begin game routine
void Widget::init_game( )
{
    // Clear map for new game
    for(int i = 0; i < 9; i++) {
        box_map[i] = 0;
    };

    // Set 0 for no winner
    win = 0;
    start_game = 1;
}

// Check for three in a row/colunm/diagnal
// returns 1 if there is a winner
int Widget::check_move( )
{
    int t = 0;

    //Check for three in a row
    for(int i = 0; i < 8; i++) {
        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        if ( (t == 3) || ( t == -3) ) {
            spinboxes = i;
            return 1;
        }
    };
    t = 0;
    // check for tie
    for(int i = 0; i < 8; i++) {
        t = t + abs(box_map[box[i][0]]) + abs(box_map[box[i][1]]) +
                abs(box_map[box[i][2]]);
    };
    if (t == 24) return 2;

    return 0 ;
}

// Do we need to block other player?
int Widget::blocking_win( )
{
    int t;
    for(int i = 0; i < 8; i++) {
        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        if ( (t == 2) || ( t == -2) ) {
            // Find empty
            if (box_map[box[i][0]] == 0) box_map[box[i][0]] = computer;
            if (box_map[box[i][1]] == 0) box_map[box[i][1]] = computer;
            if (box_map[box[i][2]] == 0) box_map[box[i][2]] = computer;
            return 1;
        }
    };
    return 0;
}

// check for a free space in corner
int Widget::check_corner( )
{
    if (box_map[0] == 0) {
        box_map[0] = computer;
        return 1;
    }

    if (box_map[2] == 0) {
        box_map[2] = computer;
        return 1;
    }

    if (box_map[6] == 0) {
        box_map[6] = computer;
        return 1;
    }

    if (box_map[8] == 0) {
        box_map[8] = computer;
        return 1;
    }

    return 0;
}

// Check for free space in row
int Widget::check_row( )
{
    if (box_map[4] == 0) {
        box_map[4] = computer;
        return 1;
    }

    if (box_map[1] == 0) {
        box_map[1] = computer;
        return 1;
    }

    if (box_map[3] == 0) {
        box_map[3] = computer;
        return 1;
    }

    if (box_map[5] == 0) {
        box_map[5] = computer;
        return 1;
    }

    if (box_map[7] == 0) {
        box_map[7] = computer;
        return 1;
    }

    return 0;
}

// logic for computer's turn
int Widget::computer_move( )
{
    if (blocking_win( ) == 1) return 1;
    if (check_corner( ) == 1) return 1;
    if (check_row( ) == 1) return 1;

    return 0;
}

void Widget::Draw_O(int x, int y, int z, int a)
{
    glPushMatrix( );
    glTranslatef(x, y, z);
    glRotatef(a, 1, 0, 0);
    glutSolidTorus(0.5, 2.0, 8, 16);
    glPopMatrix( );
    update( );
}

void Widget::Draw_X(int x, int y, int z, int a)
{
    glPushMatrix( );
    glTranslatef(x, y, z);
    glPushMatrix( );
    glRotatef(a, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glTranslatef( 0, 0, -3);
    gluCylinder( Cylinder, 0.5, 0.5, 6, 16, 16);   //glutSolidCone( 2.5, 3.0, 16, 8 );
    glPopMatrix( );

    glPushMatrix( );
    glRotatef(a, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(315, 1, 0, 0);
    glTranslatef( 0, 0, -3);
    gluCylinder( Cylinder, 0.5, 0.5, 6, 16, 16);
    glPopMatrix( );

    glPopMatrix( );
    update( );
}

void Widget::Sprint(int x, int y, QString st)
{
    QFont font;
    font.setPixelSize(24);
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(font);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::blue);
    painter.drawText(x, y, st);
    painter.end( );
}

void Widget::initializeGL( )
{
    initializeOpenGLFunctions( );
    // lighting
    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightPosition[]= { 5.0f, 25.0f, 5.0f, 1.0f };

    glClearColor (1.0, 1.0, 1.0, 0.0);  // When screen cleared, use black.
    glShadeModel (GL_SMOOTH);  // How the object color will be rendered smooth
    glEnable(GL_DEPTH_TEST);   // Check depth when rendering

    // Lighting is added to scene
    glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
    glEnable(GL_LIGHTING);  // Turn on lighting
    glEnable(GL_LIGHT1);     // Turn on light 1

    start_game = 0;
    win = 0;

    // Create a new quadric
    Cylinder = gluNewQuadric( );
    gluQuadricDrawStyle( Cylinder, GLU_FILL );
    gluQuadricNormals( Cylinder, GLU_SMOOTH );
    gluQuadricOrientation( Cylinder, GLU_OUTSIDE );
}

void Widget::resizeGL(int w, int h)
{
    win_x = w;
    win_y = h;
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);  // Setup an Ortho view
}

void Widget::paintGL( )
{
    // center x,y location for each box
    int object_map[9][2] = {{-6,6}, {0,6}, {6,6}, {-6,0}, {0,0}, {6,0}, {-6,-6},
                            {0,-6}, {6,-6}};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen


    glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix

    glLoadIdentity( ); // Clear the model matrix

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.0, 1.0);

    if (start_game == 0) {
        Sprint(width()/2-60, height()/2-45, "Tic Tac Toe");
        Sprint(width()/2-70, height()/2-15, "To Start press");
        Sprint(width()/2-90, height()/2+15, "right button for X's");
        Sprint(width()/2-80, height()/2+45, "and left for O's");
    }

    if (win == 1) Sprint(width()/2-60, height()/2+150, "You win");
    if (win == -1) Sprint(width()/2-80, height()/2+150, "Computer win");
    if (win == 2) Sprint(width()/2-20, height()/2+150, "Tie");

    // Setup view, and print view state on screen
    if (view_state == 1) {
        glColor3f(0.0, 0.0, 1.0);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity( );
        gluPerspective(60, 1, 1, 30);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity( );
        qDebug("Perspective view");
    } else {
        glColor3f(0.0, 0.0, 1.0);
        qDebug("Ortho view");
    }

    // Lighting on/off
    if (light_state == 1) {
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
    }

    gluLookAt( 0, 0, 20, 0, 0, 0, 0, 1, 0);

    // Draw Grid
    for(int ix = 0; ix < 4; ix++) {
        glPushMatrix( );
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        glVertex2i(-9 , -9 + ix * 6);
        glVertex2i(9 , -9 + ix * 6 );
        glEnd( );
        glPopMatrix( );
    };

    for(int iy = 0; iy < 4; iy++) {
        glPushMatrix( );
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        glVertex2i(-9 + iy * 6, 9 );
        glVertex2i(-9 + iy * 6, -9 );
        glEnd( );
        glPopMatrix( );
    };

    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.5, 0.5, 0.5, 1.0);
    glColorMaterial(GL_FRONT, GL_EMISSION);
    glColor4f(0.0, 0.0, 0.0, 1.0 );
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor4f(0.35, 0.35, 0.35, 1.0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor4f(0.69, 0.69, 0.69, 1.0);
    glColor3f( 1.0, 0.0, 1.0);  // Cube color

    for(int i = 0; i < 9; i++) {
        int j = 0;
        if (abs(win) == 1 ) {
            if ((i == box[spinboxes][0]) || (i == box[spinboxes][1]) ||
                    (i == box[spinboxes][2])) {
                j = spin;
            } else j = 0;
        }
        if(box_map[i] == 1) Draw_X( object_map[i][0], object_map[i][1], -1, j);
        if(box_map[i] == -1) Draw_O( object_map[i][0], object_map[i][1], -1, j);
    };

    glFlush( );
}

void Widget::updateTimer( )
{
    spin++;  // increase cube rotation by 1
    if (spin > 360) spin = 0; // if over 360 degress, start back at zero.
    update( );
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    int x, y;
    x = ev->position( ).x( );
    y = ev->position( ).y( );

    // We convert windows mouse coords to out openGL coords
    mouse_x = (18 * (float) ((float)x/(float)win_x))/6;
    mouse_y = (18 * (float) ((float)y/(float)win_y))/6;

    // What square have they clicked in?
    object_select = mouse_x + mouse_y * 3;

    if (start_game == 0) {
        if (ev->button( ) == Qt::RightButton) { // GLUT_RIGHT_BUTTON
            player = 1;
            computer = -1;
            init_game( );
            return;
        }

        if (ev->button( ) == Qt::LeftButton) { // GLUT_LEFT_BUTTON
            player = -1;
            computer = 1;
            init_game( );
            computer_move( );
            return;
        }
    }

    if (start_game == 1) {
        if (ev->button( ) == Qt::LeftButton) { // GLUT_LEFT_BUTTON
            if (win == 0) {
                if (box_map[ object_select ] == 0) {
                    box_map[ object_select ] = player;
                    win = check_move( );
                    if (win == 1) {
                        start_game = 0;
                        return;
                    }
                    computer_move( );
                    win = check_move( );
                    if (win == 1) {
                        win = -1;
                        start_game = 0;
                    }
                }
            }
        }
    }

    if (win == 2) start_game = 0;

    update( );
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key( )) {
    case Qt::Key_V:
        view_state = abs(view_state -1);
        break;
    case Qt::Key_L:
        light_state = abs(light_state -1);
        break;
    case Qt::Key_X:
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        play_x( );
        break;
    case Qt::Key_Y:
    case Qt::Key_O:
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        play_y( );
        break;
    case Qt::Key_Escape:
        qApp->quit( );
        break;
    default:
        break;
    }
    update( );
}

void Widget::play_x( )
{
    player = 1;
    computer = -1;
    init_game( );
}

void Widget::play_y( )
{
    player = -1;
    computer = 1;
    init_game( );
    computer_move( );
}
