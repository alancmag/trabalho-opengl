#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/*
Grupo 1:
Alan,
Hugo,
Jônatas,
Lucas,
Vinicius
*/

typedef struct
{
	int x;
	int y;
} Ponto;

int color[] = {0};

/*********** Protótipos ***********/

void drawMidPointCircle(int raio);
void circlePoints(int x, int y);
void setup();
void display();

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(601, 601);

	glutCreateWindow("Trabalho circunferencia otimizada em torno do ponto central");

	glutDisplayFunc(display);

	setup();

	glutMainLoop();

	return 0;
}

/* Desenha uma reta otimizada usando apenas operações inteiras*/
void drawMidPointCircle(int raio)
{
	int x, y;
	float d;
	/*Valores iniciais*/
	x = 0;
	y = raio;
	d = 5 / 4 - raio;

	circlePoints(x, y);

	while (y > x)
	{
		//TODO continuar a comentar
		if (d < 0)
		{
			// Seleciona E
			// Se d está
			d = d + 2 * x + 3;
			x++; //Vai andando no eixo X
		}
		else
		{
			// Seleciona SE
			// Se d está
			d = d + 2 * (x - y) + 5;
			x++; //Vai andando no eixo X
			y--;
		}

		circlePoints(x, y);
	}
}

void setup()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Define a visualisação numa matriz com essas restrições onde o ponto central(0,0) será o meio da janela de 601x601
	gluOrtho2D(-300, 300, -300, 300);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	color[0] = 1;
	color[1] = 0;
	color[2] = 0;
	drawMidPointCircle(30);
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;
	drawMidPointCircle(50);
	color[0] = 0;
	color[1] = 0;
	color[2] = 1;
	drawMidPointCircle(70);
	color[0] = 0;
	color[1] = 1;
	color[2] = 1;
	drawMidPointCircle(90);
	color[0] = 1;
	color[1] = 0;
	color[2] = 0;
	drawMidPointCircle(110);
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;
	drawMidPointCircle(130);
	color[0] = 0;
	color[1] = 0;
	color[2] = 1;
	drawMidPointCircle(150);
	color[0] = 0;
	color[1] = 1;
	color[2] = 1;
	drawMidPointCircle(170);
	glutSwapBuffers();
}
void circlePoints(int x, int y)
{

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	glVertex2i(x, y);
	glVertex2i(x, -y);
	glVertex2i(-x, y);
	glVertex2i(-x, -y);

	glVertex2i(y, x);
	glVertex2i(y, -x);
	glVertex2i(-y, x);
	glVertex2i(-y, -x);

	glEnd();
	glFlush();
}
