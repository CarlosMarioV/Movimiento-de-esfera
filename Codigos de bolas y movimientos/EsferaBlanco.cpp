#include <GL/glut.h>

GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
GLfloat anguloEsfera = 0.0f;

GLint ancho = 400;
GLint alto = 400;

int hazPerspectiva = 0;

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (hazPerspectiva)
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	else

		glOrtho(-4, 4, -4, 4, 1, 10);

	glMatrixMode(GL_MODELVIEW);

	ancho = width;
	alto = height;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(anguloEsfera, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(0.5f, 8, 8);

	glFlush();
	glutSwapBuffers();

	anguloEsfera += 0.2f;
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	ancho = 400;
	alto = 400;
}


void idle()
{
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
	case 'P':
		hazPerspectiva = 1;
		reshape(ancho, alto);
		break;

	case 'o':
	case 'O':
		hazPerspectiva = 0;
		reshape(ancho, alto);
		break;

	case 27:   // escape
		exit(0);
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Pelota");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}