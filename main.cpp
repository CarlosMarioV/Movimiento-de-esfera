#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

//Variables para las animaciones de rotar.
GLfloat elevacion = 0.0f;
GLfloat azimitud = 0.0f;
GLfloat giro = 0.0f;

//Matriz de elementos de punto flotante, que contiene las coordenadas X, Y y Z respectivamente
static GLfloat translate[] = { 0.0,0.0,0.0 };
int bandera = 0;

//Estructura de lista enlazada, se utiliza para guadar las coodenadas elegidas por el usuario.
struct Coordenadas
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	Coordenadas *sig = NULL;
};
struct Coordenadas *primero, *ultimo;

void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth)
{
	//Inicia las variables para dar movimiento a los objetos en la ventana, con las coordenadas de la vista. 
	glTranslated(0.0, 0.0, -distance);
	glRotated(-twist, 0.0, 0.0, 1.0);
	glRotated(-elevation, 1.0, 0.0, 0.0);
	glRotated(azimuth, 0.0, 0.0, 1.0);
}

static void init(void)
{
	//Se inicia las configuaraciones del ambiente donde estara la bolita,
	//el factor luz que le afectara y como se vera en su entorno.
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

	//Se limpia la pantalla, de cualquier basura.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	//Se carga la matriz identidad
	glLoadIdentity();
	//Se inicia el traslado de la bolita, con las coordenadas dadas.
	glTranslatef(translate[0], translate[1], translate[2]);
	//Se dibuja la esfera con un radio de 2.5
	polarView(15.0f, giro, elevacion, azimitud);

	//Se dibuja la esfera con un radio de 2.5
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_esfera);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	glPushMatrix();
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();
	//Se cargan las configuraciones.
	glFlush();
}

void reshape(int w, int h)
{
	//Función de visualización secundaria.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

/*Funcion que crea un nuevo nodo y lo inserta al final de la lista enlazada que se encuentra en memoria.*/
void ActualizarLista(float x, float y, float z) {
	struct Coordenadas *nuevo;
	nuevo = (struct Coordenadas *) malloc(sizeof(struct Coordenadas));
	if (nuevo == NULL)
		printf("No hay memoria disponible!\n");
	nuevo->x = x;
	nuevo->y = y;
	nuevo->z = z;
	nuevo->sig = NULL;
	if (primero == NULL) {
		primero = nuevo;
		ultimo = nuevo;
	}
	else if (primero->sig == NULL) {
		primero->sig = nuevo;
		ultimo = nuevo;
	}
	else {
		ultimo->sig = nuevo;
		ultimo = nuevo;
	}
}

/* Funcion que borra toda la lista que se encuentra en memoria y asimismo borra el contenido del archivo*/
void BorrarLista() {
	struct Coordenadas *temp = primero, *temp2 = primero->sig;
	while (temp != NULL) {
		free(temp);
		if (temp2 == NULL) {
			break;
		}
		temp = temp2;
		temp2 = temp2->sig;
	}
	primero = NULL;
	ultimo = NULL;
}

/* Funcion que permite conocer los datos almacenados en la lista enlazada */
void ImprimirLista() {
	struct Coordenadas * temp = primero;
	while (temp != NULL)
	{
		printf("%f %f %f \n", temp->x, temp->y, temp->z);
		temp = temp->sig;
	}
}

/* Funcion que se encarga de obtener los datos que estan en el archivo y transformarlos en coordenadas. */
void CargarDatosArchivo() {
	float ejeX;
	float ejeY;
	float ejeZ;
	FILE *archivo;
	archivo = fopen("coordenadas.txt", "r");
	char caracter;
	double potencia = 0;
	float coordenada = 0;
	int contXYZ = 0, esNegativo = 0;
	while (!feof(archivo)) {
		caracter = fgetc(archivo);
		if (caracter == ' ') {
			if (esNegativo == 1) {
				coordenada = coordenada * -1;
			}
			if (contXYZ == 0) {
				ejeX = coordenada;
				contXYZ++;
			}
			else if (contXYZ == 1) {
				ejeY = coordenada;
				contXYZ++;
			}
			else if (contXYZ == 2)
			{
				ejeZ = coordenada;
				contXYZ = 0;
				ActualizarLista(ejeX, ejeY, ejeZ);
			}
			potencia = 0;
			coordenada = 0;
			esNegativo = 0;
		}
		else if (caracter == '.') {
			continue;
		}
		else if (caracter == '-')
		{
			esNegativo = 1;
		}
		else {
			coordenada = coordenada + (((float)caracter - 48) * (pow(10, potencia)));
			potencia = potencia - 1;
		}
	}
	fclose(archivo);
}

/* Funcion que accede al archivo y almacena en el las coordenadas que se encuentran en la lista */
void GuardarDatosArchivo() {
	FILE *archivo;
	archivo = fopen("coordenadas.txt", "w+");
	struct Coordenadas *auxiliar = primero;
	while (auxiliar != NULL)
	{
		fprintf(archivo, "%f %f %f ", auxiliar->x, auxiliar->y, auxiliar->z);
		auxiliar = auxiliar->sig;
	}

	fclose(archivo);
}

/* Funcion que procesa cada nodo de la lista como un punto destino y toma la posición actual como un
punto inicio, para moverse de un punto a otro de manera lineal. Realiza un calculo matematico para
obtener la distancia entre coordenadas, la cantidad de movimientos que hará la esfera
y la distancia que recorrerá en cada movimiento para X e Y*/

void RecorrerCoordenadas() {
	struct Coordenadas *temp = primero;
	float distanciaX = 0.0;
	float distanciaY = 0.0;
	int cantMovimientos = 0;
	int mayor = 0;
	float movX = 0;
	float movY = 0;
	while (temp != NULL) {
		printf("\n------Vuelta--------\n");
		distanciaX = temp->x - translate[0];
		distanciaY = temp->y - translate[1];
		printf("\nDistancia X: %f Distancia Y: %f \n", distanciaX, distanciaY);
		if (abs(distanciaX) > abs(distanciaY)) {
			mayor = abs(distanciaX);
		}
		else {
			mayor = abs(distanciaY);
		}
		cantMovimientos = mayor / 0.2;
		if (cantMovimientos != 0)
		{
			printf("\nCantidad de movimientos: %i\n", cantMovimientos);
			movX = distanciaX / cantMovimientos;
			movY = distanciaY / cantMovimientos;
			printf("\n X se mueve en %f --- Y se mueve en %f\n\n\n", movX, movY);
			for (int i = 0; i < cantMovimientos; i++) {
				translate[0] += movX;
				translate[1] += movY;
				elevacion = elevacion + 10.0f;
				giro = giro + 5.0f;
				azimitud = azimitud + 10.0f;
				printf("x: %d y: %d", movX, movY);
				display();
				Sleep(30);
			}
			Sleep(30);
		}
		temp = temp->sig;
	}
}


void DetectarControl(unsigned int buttonMask, int x, int y, int z) {
	/*Esta función es llamada de la función del joystick de la libreria GLUT,
	y permite detectar ya sea un movimiento del analogo (en X o Y) o si se presiona
	un boton (lo cual retorna un entero determinado). Se actualiza cada 3 segundos.
	*/
	if (x <= -800)
	{
		elevacion = elevacion + 10.0f;
		translate[0] -= 0.1;
		glutPostRedisplay();
	}
	else if (x >= 800)
	{
		elevacion = elevacion - 10.0f;
		translate[0] += 0.1;
		glutPostRedisplay();
	}

	else if (y <= -800)
	{
		elevacion = elevacion + 10.0f;
		translate[1] += 0.1;
		glutPostRedisplay();
	}
	else if (y >= 800)
	{
		elevacion = elevacion + 10.0f;
		translate[1] -= 0.1;
		glutPostRedisplay();
	}

	else if (buttonMask == 16)
	{
		elevacion = elevacion - 10.0f;
		translate[2] -= 0.1;
		glutPostRedisplay();
	}

	else if (buttonMask == 32)
	{

		elevacion = elevacion + 10.0f;
		translate[2] += 0.1;
		glutPostRedisplay();
	}

	/* Se llama a la funcion ActualizarLista, que creara un nuevo nodo con las coordenadas
	del objeto en el momento en el que se presiona el boton */
	else if (buttonMask == 1) {
		ActualizarLista(translate[0], translate[1], translate[2]);
	}

	/* Accion que hace un llamado a RecorrerCoordenadas, funcion que permite
	recorrer cada nodo de la lista y dibujar la esfera en las coordenadas que
	esten almacenadas en memoria. En caso de no haber coordenadas almacenadas,
	se le notificará al usuario. */
	else if (buttonMask == 2) {
		if (primero == NULL) {
			printf("\n-----El archivo no contiene coordenadas-----\n");
			MessageBox(NULL, TEXT("El archivo no contiene coordenadas"), TEXT("Estimado noob"), NULL);

		}
		else {
			RecorrerCoordenadas();
		}

	}

	// Se llama a la funcion BorrarLista. En caso de que el archivo esté vacío, se le notifica al usuario.
	else if (buttonMask == 4) {
		if (primero == NULL) {
			printf("\n----- No hay coordenadas que borrar -----\n");
			MessageBox(NULL, TEXT("No hay coordenadas que borrar"), TEXT("Estimado noob"), NULL);
		}
		else {
			BorrarLista();
			FILE *archivo = fopen("coordenadas.txt", "w+");
			fclose(archivo);
		}
	}

	/* Las coordenadas de cada nodo de la lista en memoria se almacenan en el archivo. Se cierra el programa. */
	else if (buttonMask == 8) {
		GuardarDatosArchivo();
		exit(0);
	}
}


// Eventos del teclado
void keyboard(unsigned char key, int x, int y)
{
	FILE *archivo;
	struct Coordenadas *temp;
	float distanciaX = 0.0;
	float distanciaY = 0.0;
	int cantMovimientos = 0;
	int mayor = 0;
	float movX = 0;
	float movY = 0;
	switch (key) {
	case 'w':
	case 'W':
		elevacion = elevacion + 10.0f;
		translate[1] += 0.1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		elevacion = elevacion + 10.0f;
		translate[0] -= 0.1;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		elevacion = elevacion + 10.0f;
		translate[1] -= 0.1;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		elevacion = elevacion - 10.0f;
		translate[0] += 0.1;
		glutPostRedisplay();
		break;
	case 'g':
	case 'G':
		ActualizarLista(translate[0], translate[1], translate[2]);
		break;
	case 'r':
	case 'R':
		if (primero == NULL) {
			printf("\n-----El archivo no contiene coordenadas-----\n");
			MessageBox(NULL, TEXT("El archivo no contiene coordenadas"), TEXT("Estimado noob"), NULL);

		}
		else {
			RecorrerCoordenadas();
		}
		break;
	case'b':
	case'B':
		if (primero == NULL) {
			printf("\n----- No hay coordenadas que borrar -----\n");
			MessageBox(NULL, TEXT("No hay coordenadas que borrar"), TEXT("Estimado noob"), NULL);
		}
		else {
			BorrarLista();
			FILE *archivo = fopen("coordenadas.txt", "w+");
			fclose(archivo);
		}
		break;
	case'i':
	case'I':
		elevacion = elevacion + 10.0f;
		glutPostRedisplay();
		break;
	case'o':
	case'O':
		giro = giro + 10.0f;
		glutPostRedisplay();
		break;
	case'p':
	case'P':
		azimitud = azimitud + 10.0f;
		glutPostRedisplay();
		break;
	case'q':
	case'Q':
		GuardarDatosArchivo();
		exit(0);
		break;
	}
}


int main(int argc, char **argv) {
	/* Función que inicializa los valores para crear la ventana, dibujar la esfera e iniciar los
	EventListener para el joystick. Se hace la llamada a la funcion CargarDatosArchivo, que se encarga
	de obtener los datos almacenados en el archivo de texto para generar una lista enlazada a partir de
	estos*/
	CargarDatosArchivo();//Carga los datos de archivo.
	ImprimirLista();

	glutInit(&argc, argv);//Se inicia la libreria Glut.
	glutInitWindowSize(1000, 600);//Se establece el tamaño de la ventada
	glutCreateWindow(argv[0]);//Se crea la ventana en memoria.
	glutSetWindowTitle("Lenguajes De Programacion 2016");//Nombre que aparece ne la parte de arriba.
	glutPositionWindow(180, 60);//Posicion de la ventana en la pantalla de la computadora.
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);//Se establece el modo de la ventada, percibe la profundidad un buffer simple y la paleta de colores RGB
	init();//Da inicio a las variables de la libreria.
	glutReshapeFunc(reshape);//función secundaria de visualización
	//int pollInterval = 3;
	//glutJoystickFunc(DetectarControl, pollInterval);//Función que ejecuta el joistick, se ejecuta en un intervalo de 3 segundos cada cambio del joistick
	glutKeyboardFunc(keyboard);//Espera evento del teclado.
	glutDisplayFunc(display);//Funcion de redibujado.

	glutMainLoop();
	return 0;
}
