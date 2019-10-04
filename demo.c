/*  demo.c*/
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct{
	int x;
	int y;
}Ponto;

int window;

int color[3] = {0, 0, 0};

/*********** Protótipos ***********/

void drawLine(Ponto *pI, Ponto *pF);
void setup();
void display();

/********************************/

int main(int argc, char *argv[]){

   glutInit(&argc, argv);
   
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   
   glutInitWindowSize(800,600);
   
   window = glutCreateWindow("Hello World");
   
	glutDisplayFunc(display);
	
	setup();
	
   glutMainLoop();


   return 0;
}

/*********** Funções ***********/

void drawLine(Ponto *pI, Ponto *pF){

	int dx, dy, inc_e, d, inc_ne, x, y, xf;

	dx = (*pF).x - (*pI).x;
	dy = (*pF).y - (*pI).y;
	d = 2 * dy - dx;
	inc_e = 2 * dy;
	inc_ne = 2 * (dy - dx);

	if((*pI).x > (*pF).x)
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
	glEnd();

	glFlush();

	while(x < xf)
	{
		x++;

		if(d < 0)
			d += inc_e;
	
		else
		{
			y++;
			d += inc_ne;
		}

        glPointSize(3);
		glBegin(GL_POINTS);
			glColor3f(color[0], color[1], color[2]);
			glVertex2i(x, y);
		glEnd();

		glFlush();		
	}
}

void setup() 
{
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 800, 0, 600);
}

void display()
{
   		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Ponto i,f;

		i.x = 0,
		i.y = 0;

		f.x = 600;
		f.y = 300;

		drawLine(&i, &f);

   glutSwapBuffers();
}



