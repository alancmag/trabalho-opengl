#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/*
Grupo 1:
Alan,
Hugo,
Jônatas,
Lucas,
Vinicius
*/

/* Struct Vertex para implementar uma estrutura de dados de ponto */
typedef struct vertex Vertex;
struct vertex
{
    double x;
    double y;
};

/*Definindo a struct das cores para facilitar*/
typedef struct cor Cor;
struct cor
{
    double RED;
    double GREEN;
    double BLUE;
};

Cor *AZUL;
Cor *VERMELHO;
Cor *VERDE;


char *monta_nome_janela(const char *funcao);

void handleKeypress(unsigned char key, int x, int y)
{

    switch (key)

    {

    case 27:

        exit(0);
    }
}

void initRendering()
{

    glEnable(GL_DEPTH_TEST);
}

void handleResize(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix
    if (width >= height)
    {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

void drawLine(Vertex vtx_i, Vertex vtx_f, Cor *cor)
{
    double dx, dy, d, inc_e, inc_ne, x, y, xf;

	dx = vtx_f.x - vtx_i.x; // Calcula dx -> distância entre os pontos no eixo x
	dy = vtx_f.y - vtx_i.y; // Calcula dy -> distância entre os pontos no eixo y
	d = 2 * dy - dx; // Variável de decisão -> ponto médio aplicado sobre a equação da reta
	inc_e = 2 * dy; // Incremento para o ponto inferior
    inc_ne = 2 * (dy - dx); // Incremento para o ponto superior

    /* X do ponto inicial > x do ponto final -> começa com o ponto "final" */
	if(vtx_i.x > vtx_f.x)
    {
		x = vtx_f.x;	
		y = vtx_f.y;
		xf = vtx_i.x;		
	}
    /* X do ponto final > x do ponto inical -> começa com o ponto incial */
	else
    {
		x = vtx_i.x;		
		y = vtx_i.y;
		xf = vtx_f.x;
	}

	// Plota o primeiro ponto
    glBegin(GL_POINTS);
        glColor3d((*cor).RED, (*cor).GREEN, (*cor).BLUE);
		glVertex2d(x, y);
	glEnd();

	glFlush();

	while(x < xf)
    {
		x+=0.001;

		/* -> d < 0
         *  -> incrementa apenas x
         *  -> calcula o novo d somando o antigo d com dy
         */
        if(d < 0) 
			d += inc_e;

        /* -> d = 0 ou d > 0
         *  -> ponto médio superior
         *  -> incrementa x e y
         *  -> calcula o novo d somando o antigo d com (dy - dx)
         */
		else 
        {
			y+=0.001; 
			d += inc_ne; 
		}

		// Plota o ponto calculado
        glBegin(GL_POINTS);
            glColor3d((*cor).RED, (*cor).GREEN, (*cor).BLUE);
			glVertex2d(x, y);
		glEnd();

		glFlush();		
	}	

}

void display_line(void)
{

    /* Array base das transformações*/
    Vertex v_array[] =
        {
            {.x = 0.25, .y = 0.25},
            {.x = 0.50, .y = 0.25}
        };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // Título da janela
    char *titulo = monta_nome_janela("Desenhando linha");
    glutSetWindowTitle(titulo);
    // Desenha a linha
    drawLine(v_array[0], v_array[1], VERMELHO);

    glutSwapBuffers();
    free(titulo);
}

int main(int argc, char **argv)
{
    /*Definindo as cores para facilitar    */

    AZUL = (Cor *)calloc(1, sizeof(Cor));
    VERMELHO = (Cor *)calloc(1, sizeof(Cor));
    VERDE = (Cor *)calloc(1, sizeof(Cor));
    (*AZUL).BLUE = 1;
    (*VERMELHO).RED = 1;
    (*VERDE).GREEN = 1;

    glutInit(&argc, argv);
    initRendering();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Cria a primeira janela
    glutInitWindowSize(700, 600);
    glutCreateWindow("LINHA");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Define a posição da janela
    glutPositionWindow(10, 10);
    // Registrar os callbacks
    glutDisplayFunc(display_line);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutMainLoop();

    free(AZUL);
    free(VERDE);
    free(VERMELHO);
    return 0;
}


/* Função auxiliar para montar o nome da janela com os parametros que geram a tranformação.
* Se angulo for 0, ignora ele e assume que é o vertex que deve ser usado pra montar, caso contrario, use ele.
* Precisa dar free no titulo retornado.
*/
char *monta_nome_janela(const char *funcao)
{
    char *titulo = malloc(40 * sizeof(char));
    // sprintf formata strings, em vez de imprimir, ela salva em uma variável.
    sprintf(titulo, "%s", funcao);
    
    return titulo;
}