#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>

#include <stdlib.h>
#include <GL/glut.h>



GLfloat elevacion =   0.0f;
GLfloat azimitud  =   0.0f;
GLfloat giro      =   0.0f;

double posicionX = 15.0f;

void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth)
{
glTranslated(0.0, 0.0, -distance);
glRotated(-twist, 0.0, 0.0, 1.0);
glRotated(-elevation, 1.0, 0.0, 0.0);
glRotated(azimuth, 0.0, 0.0, 1.0);
}

//Inicializa las propiedades de la fuente de luz
static void init(void)
{
    GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void display (void)
{   
    //Defino un material Verde
    GLfloat mat_ambient_esfera[] = {0.1, 0.1, 0.1, 1.0f}; 
    GLfloat mat_diffuse_esfera[] = {0.0, 0.7, 0.0, 1.0f};
    GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};

    GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();
    polarView(15.0f, giro, elevacion, azimitud);
    
    //Dibuja la esfera de radio 2.5
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_esfera);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    glPushMatrix ();
    glTranslatef (-1.0, 1.0, 0.0); 
    glutSolidSphere (1.0, 16, 16);
    glPopMatrix ();

    glFlush ();
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode (GL_MODELVIEW);
}

//Mueve los objetos...
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 'x':
   case 'X':
      elevacion = elevacion + 10.0f;
      glutPostRedisplay();
      break;
   case 'v':
   case 'V':
      elevacion = elevacion - 10.0f;
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      azimitud = azimitud + 10.0f;
      glutPostRedisplay();
      break;
   case 'u':
   case 'U':
      azimitud = azimitud - 10.0f;
      glutPostRedisplay();
      break;
   case 'z':
   case 'Z':
      giro = giro + 10.0f;
      glutPostRedisplay();
      break;
   case 'c':
   case 'C':
      giro = giro - 10.0f;
      glutPostRedisplay();
      break;
   case 27:
      exit(0);
      break;
   }
}


void DetectarControl(unsigned int buttonMask, int x, int y, int z)
{
	////glTranslated();
	//std::cout << "Eje X: " << x << std::endl;
	//std::cout << "Eje Y: " << y << std::endl;
	//if (x > 800)
	//{
	//	std::cout << "Hooolaaaa" << x << std::endl;
	//	posicionX += 10.99f;
	//	glTranslated(posicionX, 1.0, 0.0);
	//	//glutPostRedisplay();
	//}

	glClear(GL_COLOR_BUFFER_BIT);
	int present = glfwJoystickPresent(buttonMask);
	std::cout << present << std::endl;

	if (1 == present)
	{
		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		//std::cout << count << std::endl;


		std::cout << "Analogo izquierdo X Axis: " << axes[0] << std::endl; // tested with PS4 controller connected via micro USB cable
		//std::cout << "Analogo izquierdo Y Axis: " << axes[1] << std::endl; // tested with PS4 controller connected via micro USB cable
		//std::cout << "Analogo derecho X Axis: " << axes[2] << std::endl; // tested with PS4 controller connected via micro USB cable
		//std::cout << "Analogo derecho Y Axis: " << axes[3] << std::endl; // tested with PS4 controller connected via micro USB cable
		//std::cout << "Left Trigger/L2: " << axes[4] << std::endl; // tested with PS4 controller connected via micro USB cable
		//std::cout << "Right Trigger/R2: " << axes[5] << std::endl; // tested with PS4 controller connected via micro USB cable


		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		if (GLFW_PRESS == buttons[1])
		{
			//std::cout << "Pressed" << std::endl;
		}
		else if (GLFW_RELEASE == buttons[0])
		{
			//std::cout << "Released" << std::endl;
		}

		const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		//std::cout << name << std::endl;

		// Swap front and back buffers
		//glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}	
}

int main(int argc, char **argv)
{
   glutInitWindowSize(300, 300);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   int pollInterval = 3;
   //glutJoystickFunc(DetectarControl,pollInterval);
   glutDisplayFunc(display);

   glutMainLoop();
   return 0;
}