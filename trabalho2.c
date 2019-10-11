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

int color[] = {1, 0, 0};

/*********** Protótipos ***********/

void drawLine(Ponto *pI, Ponto *pF);
void setup();
void display();

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 600);

	glutCreateWindow("Trabalho retas otimizadas");

	glutDisplayFunc(display);

	setup();

	glutMainLoop();

	return 0;
}

/* Desenha uma reta otimizada usando apenas operações inteiras*/
void drawLine(Ponto *pI, Ponto *pF)
{

	int dx, dy, inc_e, d, inc_ne, x, y, xf;

	dx = pF->x - pI->x; // Variação de X
	dy = pF->y - pI->y; // Variação de Y
	d = 2 * dy - dx;	// Valor inicial da equação da reta aplicada com os valores do ponto x0 e y0

	// Incremento de E, caso o valor de 'd' esteja abaixo do ponto Médio
	// (esse valor é constante pois a diferença de um para o próximo é a mesma)
	inc_e = 2 * dy;

	// Incremento de NE, caso o valor de 'd' esteja acima do ponto Médio
	// (esse valor é constante pois a diferença de um para o próximo é a mesma)
	inc_ne = 2 * (dy - dx);

	// Caso o ponto inicial esjeta acima do final, então inverte
	if ((*pI).x > (*pF).x)
	{
		x = (*pF).x;
		y = (*pF).y;
		xf = (*pI).x;
	}
	else
	{
		x = (*pI).x;
		y = (*pI).y;
		xf = (*pF).x;
	}

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	glVertex2i(x, y);

	while (x < xf)
	{
		//TODO continuar a comentar
		if (d < 0)
		{
			// Se d está
			d += inc_e;
			x++; //Vai andando no eixo X
		}
		else
		{
			x++; //Vai andando no eixo X
			y++;
			d += inc_ne;
		}

		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

void setup()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0, 800, 0, 600);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Ponto i, f;

	i.x = 0,
	i.y = 0;

	f.x = 600;
	f.y = 300;

	drawLine(&i, &f);

	glutSwapBuffers();
}
