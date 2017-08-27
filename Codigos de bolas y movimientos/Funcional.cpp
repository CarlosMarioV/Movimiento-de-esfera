#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat elevacion = 0.0f;
GLfloat azimitud = 0.0f;
GLfloat giro = 0.0f;

static GLfloat translate[] = { 0.0,0.0,0.0 };

void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth)
{
	glTranslated(0.0, 0.0, -distance);
	glRotated(-twist, 0.0, 0.0, 1.0);
	glRotated(-elevation, 1.0, 0.0, 0.0);
	glRotated(azimuth, 0.0, 0.0, 1.0);
}

static void init(void)
{
	//Inicializa las propiedades de la fuente de luz
	GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	//Se define el color Verde
	GLfloat mat_ambient_esfera[] = { 0.1, 0.1, 0.1, 1.0f };
	GLfloat mat_diffuse_esfera[] = { 0.0, 0.7, 0.0, 1.0f };
	GLfloat mat_specular_esfera[] = { 0.8, 0.8, 0.8, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();

	glTranslatef(translate[0], translate[1], translate[2]);

	polarView(15.0f, giro, elevacion, azimitud);

	//Se dibuja la esfera con un radio de 2.5
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_esfera);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	glPushMatrix();
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void DetectarControl(unsigned int buttonMask, int x, int y, int z)
{
	std::cout << "Eje X: " << buttonMask << std::endl;
	std::cout << "Eje y: " << y << std::endl;
	if (x <= -800)
	{
		translate[0] -= 0.1;
		glutPostRedisplay();
	}
	else if (x >= 800)
	{
		translate[0] += 0.1;
		glutPostRedisplay();
	}

	else if (y <= -800)
	{
		translate[1] += 0.1;
		glutPostRedisplay();
	}
	else if (y >= 800)
	{
		translate[1] -= 0.1;
		glutPostRedisplay();
	}

	else if (buttonMask == 16)
	{
		translate[2] -= 0.1;
		glutPostRedisplay();
	}

	else if (buttonMask == 32)
	{
		translate[2] += 0.1;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 600);

	glutCreateWindow(argv[0]);
	glutSetWindowTitle("Lenguajes De Programacion 2016");
	glutPositionWindow(180,60);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	init();
	glutReshapeFunc(reshape);
	int pollInterval = 3;
	glutJoystickFunc(DetectarControl,pollInterval);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}