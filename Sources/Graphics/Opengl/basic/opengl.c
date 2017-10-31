#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// #include <Windows.h>
#include <GL/glut.h>
#define true 1
#define false 0
typedef int bool;
#define random (rand()/(RAND_MAX+1.0))
static float xrot = 0.0;
static float yrot = 0.0;
static float zrot = 0.0;
const float d = 0.1, dh = 0;
//
inline float fun(float x, float y)
{
	//Matlab Peaks Function
	float z = 3 * (1 - x) * (1 - x) * exp(-x * x - (y + 1) * (y + 1))
	          - 10 * (x / 5 - x * x * x - y * y * y * y * y) * exp(-x * x - y * y)
	          - 1.0 / 3 * exp(-(x + 1) * (x + 1) - y * y);
	return z / 3.0;
}
void Initial()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);//注意:GL_CW与GL_CCW的区别。
	//glClearColor(1.0, 1.0, 1.0, 0.0);
}
void DrawSurface()
{
	float x, y, z1, z2, z3, z4;

	glColor3f(0, 1, 1);
	//glEnable(GL_CULL_FACE); // 开启剪裁
	//glCullFace(GL_BACK); // 裁掉背面
	//
	for (x = -3; x < 3; x += d) {
		for (y = -3; y < 3; y += d) {
			z1 = fun(x, y);
			z2 = fun(x + d, y);
			z3 = fun(x, y + d);
			z4 = fun(x + d, y + d);

			glBegin(GL_QUADS);
			glColor3f(random, random, random);
			glVertex3f(x, z1, y);
			glVertex3f(x + d, z2, y);
			glVertex3f(x + d, z4, y + d);
			glVertex3f(x, z3, y + d);
			//glVertex3f(x,z1,y);
			glEnd();
		}
	}

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(15, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(zrot, 0, 0, 1);
	DrawSurface();
	//xrot = xrot + 1;
	yrot = yrot + 1;
	//zrot = zrot + 1;
	glutSwapBuffers();
	//glFlush();
}

void reshape(int w, int h)
{
	int factor = 5;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-factor, factor, -factor * (GLfloat)h / (GLfloat)w, factor * (GLfloat)h / (GLfloat)w, -factor, factor);
	else
		glOrtho(-factor * (GLfloat)w / (GLfloat)h, factor * (GLfloat)w / (GLfloat)h, -factor, factor, -factor, factor);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void display();
void keyboard( unsigned char key, int x, int y );

float g_fps( void (*func)(void), int n_frame );

bool finish_without_update = false;



void keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 'F':
	case 'f':
		finish_without_update = true;
		printf( "%f fps\n", g_fps( display, 100 ) );
		finish_without_update = false;
		break;
	}
}



float g_fps( void (*func)(void), int n_frame )
{
	clock_t start, finish;
	int i;
	float fps;

	printf( "Performing benchmark, please wait" );
	start = clock();
	for ( i = 0; i < n_frame; i++ ) {
		if ( (i + 1) % 10 == 0 )
			printf(".");
		func();
	}
	printf( "done\n" );
	finish = clock();

	fps = (float)(n_frame) / (finish - start) * CLOCKS_PER_SEC;
	return fps;
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	// glutInitWindowPosition(350, 120);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-512)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-640)/2);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Press f to get FPS");
	Initial();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
