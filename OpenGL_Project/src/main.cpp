/*
 * Disciplina: Construção de Software Gráfico 3D
 * Professor: Luiz Antonio Pavão
 * Aluno: João Pedro Rodrigues de Lima
 */

#include <windows.h>	 
#include <GL\freeglut.h> 
#include <fstream>		
#include <iostream>

using namespace std;

GLdouble angleV, fAspect;
GLdouble angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

// VARIÁVEIS DE DESENHO 

GLdouble dx = 0; GLdouble dy = 0; GLdouble dz = 0; 

GLdouble dxTeacup = -60, dyTeacup = 60, dzTeacup = 0; // xícara
GLdouble dxSphere = 0, dySphere = 60, dzSphere = 0; // esfera
GLdouble dxCylinder = 60, dyCylinder = 60, dzCylinder = 0; // cilindro
GLdouble dxCube = -60, dyCube = -20, dzCube = 0; // cubo
GLdouble dxTeapot = 0, dyTeapot = -20, dzTeapot = 0; // bule
GLdouble dxTeaspoon = 60, dyTeaspoon = -20, dzTeaspoon = 0; // colher

int choice = 0; // escolha do sólido

int numObjects;
int ObjectList[6]; // lista de objetos, 10 é o número máximo
int x[6], y[6], z[6]; // coordenadas dos objetos

char title[] = "Trabalho OpenGL - João Pedro Lima";

// LEITURA DO ARQUIVO DE CENA
void DisplayFileRead(const char *fileName)
{
	ifstream inStream;
	inStream.open(fileName, ios::in); // abre o arquivo

	if (inStream.fail())
	{
		return;
	}

	else
	{
		cout << "File Was Successfully Opened" << endl;
	}
	
	inStream >> numObjects;	// lê primeira linha do arquivo, número de objetos 
	cout << "Number of Objects: " << numObjects << endl;

	for (int i = 1; i <= numObjects; i++) // leitura das demais linhas, ID dos objetos, posição e cor
	{
		inStream >> ObjectList[i] >> x[i] >> y[i] >> z[i];
	}

	inStream.close(); // fecha o arquivo
}


// CALLBACK PARA O DESENHO
void render(void)
{
	//DisplayFileRead("readfile.txt");  // remover, pois causa repetição quando abrem os desenhos

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glPushMatrix();

	glRotatef(angleX, 1.0f, 0.0f, 0.0f); // rotação em x 
	glRotatef(angleY, 0.0f, 1.0f, 0.0f); // rotação em y	
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f); // rotação em Z
	
	glutWireCube(300);  // simula os limites da cena (formato de cubo)

	// INÍCIO DAS FUNÇÕES DE DESENHO 

	// Sólido 1 - Teacup
	glPushMatrix();

	glColor3d(0.0, 0.3, 0.4);
	glTranslated(dxTeacup, dyTeacup, dzTeacup);
	glutWireTeacup(30);

	glPopMatrix();
		
	// Sólido 2 - Sphere
	glPushMatrix();

	glColor3d(0.8, 0.3, 0.0);
	glTranslated(dxSphere, dySphere, dzSphere);
	glutWireSphere(10, 24, 24);

	glPopMatrix();

	// Sólido 3 - Cylinder
	glPushMatrix();

	glColor3d(0.9, 0.0, 1.0);
	glTranslated(dxCylinder, dyCylinder, dzCylinder);
	glutWireCylinder(15, 15, 10, 10);

	glPopMatrix();
	
	// Sólido 4 - Cube
	glPushMatrix();

	glColor3d(0.3, 0.9, 1.0);
	glTranslated(dxCube, dyCube, dzCube);
	glutSolidCube(20);

	glPopMatrix();
	   	 
	// Sólido 5 - Teapoot
	glPushMatrix();

	glColor3d(0.4, 0.0, 0.5);
	glTranslated(dxTeapot, dyTeapot, dzTeapot);
	glutWireTeapot(10);

	glPopMatrix();

	// Sólido 6 - Teaspoon
	glPushMatrix();

	glColor3d(0.9, 1.0, 0.0);
	glTranslated(dxTeaspoon, dyTeaspoon, dzTeaspoon);
	glutWireTeaspoon(40);

	glPopMatrix();

	// FIM DAS FUNÇÕES DE DESENHO

	glPopMatrix();

	glutSwapBuffers();
}

// PARÂMETROS DE RENDERING
void initGL(void)
{
	angleV = 45;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);                

	glEnable(GL_DEPTH_TEST);   
	glDepthFunc(GL_LEQUAL);    
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  

	GLfloat luzAmbiente[4] = {0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};	   
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};

	// brilho
	GLfloat especularidade[4] = {1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	glClearColor(0.0, 0.0f, 0.0f, 1.0f); // cor de fundo (preto)

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
}

// VOLUME DA VISUALIZAÇÃO
void setVisParam(void)
{
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	gluPerspective(angleV, fAspect, 0.1, 500);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
	gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
}

// CALLBACK ALTERAÇÃO TAMANHO DA JANELA 
void reshape(GLsizei w, GLsizei h)
{
	if (h == 0) // previnir divisões por zero
	{
		h = 1;
	}

	glViewport(0, 0, w, h); // tamanho viewport
	fAspect = (GLdouble)w / (GLdouble)h; //correção de aspecto

	setVisParam();
}

// CALLBACK EVENTOS DO MOUSE
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (angleV >= 10)
			{
				angleV -= 5;
				cout << "Zoom In" << endl;
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (angleV <= 130)
			{
				angleV += 5;
				cout << "Zoom Out" << endl;
			}
		}
	}

	setVisParam();
	glutPostRedisplay();
}

// CALLBACK EVENTOS DO TECADO
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{		
		case GLUT_KEY_F1: // sólido 1
			choice = 1;
			cout << "Teacup Selected" << endl;
			break;

		case GLUT_KEY_F2: // sólido 2
			choice = 2;
			cout << "Sphere Selected" << endl;
			break;

		case GLUT_KEY_F3: // sólido 3
			choice = 3;
			cout << "Cylinder Selected" << endl;
			break;

		case GLUT_KEY_F4: // sólido 4
			choice = 4;
			cout << "Cube Selected" << endl;
			break;

		case GLUT_KEY_F5: // sólido 5
			choice = 5;
			cout << "Teapoot Selected" << endl;
			break;

		case GLUT_KEY_F6: // sólido 6
			choice = 6;
			cout << "Teaspoon Selected" << endl;
			break;

		case GLUT_KEY_F10: // nenhum objeto 
			choice = 0;
			cout << "No Object Selected" << endl;
			break;

		case GLUT_KEY_PAGE_UP: // rotação da cena (eixo x)
			angleX++;
			cout << "Scene Rotating Upwards" << endl;
			break;

		case GLUT_KEY_PAGE_DOWN:
			angleX--;
			cout << "Scene Rotating Downwards" << endl;
			break;

		case GLUT_KEY_HOME: // rotação da cena (eixo y)
			angleY++;
			cout << "Scene Rotating Leftwards" << endl;
			break;

		case GLUT_KEY_END:
			angleY--;
			cout << "Scene Rotating Rightwards" << endl;
			break;

		case GLUT_KEY_LEFT: // movimentação para a esquerda
			if (choice == 1)
			{
				dxTeacup--;
			}

			else if (choice == 2)
			{
				dxSphere--;
			}

			else if (choice == 3)
			{
				dxCylinder--;
			}

			else if (choice == 4)
			{
				dxCube--;
			}

			else if (choice == 5)
			{
				dxTeapot--;
			}

			else if (choice == 6)
			{
				dxTeaspoon--;
			}

			break;

		case GLUT_KEY_RIGHT: // movimentação para a direita 
			if (choice == 1)
			{
				dxTeacup++;
			}

			else if (choice == 2)
			{
				dxSphere++;
			}

			else if (choice == 3)
			{
				dxCylinder++;
			}

			else if (choice == 4)
			{
				dxCube++;
			}

			else if (choice == 5)
			{
				dxTeapot++;
			}

			else if (choice == 6)
			{
				dxTeaspoon++;
			}
				
			break;

		case GLUT_KEY_UP: // movimentação para cima
			if (choice == 1)
			{
				dyTeacup++;
			}

			else if (choice == 2)
			{
				dySphere++;
			}

			else if (choice == 3)
			{
				dyCylinder++;
			}

			else if (choice == 4)
			{
				dyCube++;
			}

			else if (choice == 5)
			{
				dyTeapot++;
			}

			else if (choice == 6)
			{
				dyTeaspoon++;
			}

			break;

		case GLUT_KEY_DOWN: // movimentação para baixo
			if (choice == 1)
			{
				dyTeacup--;
			}

			else if (choice == 2)
			{
				dySphere--;
			}

			else if (choice == 3)
			{
				dyCylinder--;
			}

			else if (choice == 4)
			{
				dyCube--;
			}

			else if (choice == 5)
			{
				dyTeapot--;
			}

			else if (choice == 6)
			{
				dyTeaspoon--;
			}

			break;
	}

	glutPostRedisplay();
}

// MAIN
int main(int argc, char** argv)
{
	DisplayFileRead("readfile.txt");
	
	cout << "---------- ACTIONS MENU ---------- " << endl;

	// AÇÕES NOS OBJETOS
	cout << "\n1. OBJECTS" << endl;
	cout << "UP Key: moves object upwards" << endl;
	cout << "DOWN Key: moves object downwards" << endl;
	cout << "RIGHT Key: moves object rightwards" << endl; 
	cout << "LEFT Key: moves object leftwards" << endl;

	// AÇÕES NA CENA
	cout << "\n2. SCENE" << endl;
	cout << "Page Up: rotates the scene upwards" << endl;
	cout << "Page Down: rotates the scene downards" << endl;
	cout << "Home: rotates the scene leftwards" << endl;
	cout << "End: rotates the scene rightwards" << endl;

	// AÇÕES DE ZOOM
	cout << "\n3. ZOOM" << endl;
	cout << "Mouse Left Button: zoom in" << endl;
	cout << "Mouse Right Button: zoom out" << endl;
				   
	// SELEÇÃO DE OBJETOS
	cout << "\n4. OBJECT SELECTION" << endl;
	cout << "F1 - choose Teacup" << endl;
	cout << "F2 - choose Sphere" << endl;
	cout << "F3 - choose Cylinder" << endl;
	cout << "F4 - choose Cube" << endl;
	cout << "F5 - choose Teapot" << endl;
	cout << "F6 - choose Teaspoon" << endl;
	cout << "F10 - no objects chosen" << endl;

	cout << "---------- ACTIONS MENU ---------- " << endl;

	glutInit(&argc, argv);					
	glutInitDisplayMode(GLUT_DOUBLE);

	glutInitWindowSize(640, 480);			
	glutInitWindowPosition(50, 50);	

	glutCreateWindow(title);				
	glutDisplayFunc(render);				
	glutSpecialFunc(processSpecialKeys);	

	glutReshapeFunc(reshape);				
	glutMouseFunc(mouse);					
	glutIdleFunc(render);					
	initGL();								
	glutMainLoop();	

	return 0;
}
