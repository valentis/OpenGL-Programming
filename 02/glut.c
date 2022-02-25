#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
 
// OpenGL 표시 함수
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);   // R, G, B의 3개의 값 : 흰색
 
   // OpenGL의 사각형을 위한 함수
    glBegin(GL_POLYGON);
      glVertex3f(0.25, 0.25, 0.0);
      glVertex3f(0.75, 0.25, 0.0);
      glVertex3f(0.75, 0.75, 0.0);
      glVertex3f(0.25, 0.75, 0.0);
    glEnd( );
    glFlush( );
}
 
void init(void) 
{
    // OpenGL 초기화 함수
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("sampling");
 
    init( );
 
    glutDisplayFunc(display); 
    glutMainLoop( );  
    return 0;   
} 
