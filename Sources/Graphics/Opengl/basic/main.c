#include <Windows.h>
#include <GL/glut.h>
//
#define width 640
#define height 480
//
void Run(void)
{
    glClear(0);
    GLfloat c[]= {0,1,1};
    glColor3fv(c);
    glBegin(GL_LINES);
    glVertex2i(0,0);
    glVertex2i(1,1);
    glEnd();
    glFlush();
}

int main(int argc,char*argv[])
{
    glutInit(&argc,argv);
    glutCreateWindow("title");
    glutInitWindowSize(width, height);
    // glClearColor(1,1,1,1);
    glutDisplayFunc(Run);
    glutMainLoop();
}