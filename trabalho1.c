#include <GL/glut.h>
#include <string.h>
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
    float x;
    float y;
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

void drawPolygon(Cor *cor, int vertex_num, Vertex *v_array);
void escala(Vertex *v_array, int vertex_num, Vertex v_escala);
void rotate(Vertex *v_array, int vertex_num, int angulo);
void translate(Vertex *v_array, int vertex_num, Vertex dv);

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

void display_escala(void)
{
    Vertex v_escala;

    /* Array base das transformações*/
    Vertex v_array[] =
        {
            {.x = -0.25, .y = -0.25},
            {.x = 0.75, .y = -0.25},
            {.x = 0.75, .y = 0.75},
            {.x = -0.25, .y = 0.75},
        };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha primeiro quadrado AZUL
    drawPolygon(AZUL, 4, v_array);
    // Seta o vertex da escala pra reduzir pela metade o X e o Y do quadrado
    v_escala.x = 0.5, v_escala.y = 0.5;
    // Aplica a escala no array
    escala(v_array, 4, v_escala);
    // Desenha o quadrado escalado em VERDE
    drawPolygon(VERDE, 4, v_array);

    glutSwapBuffers();
}

void display_translate(void)
{
    Vertex v_translacao;

    /* Array base das transformações*/
    Vertex v_array[] =
        {
            {.x = -0.25, .y = -0.25},
            {.x = 0.75, .y = -0.25},
            {.x = 0.75, .y = 0.75},
            {.x = -0.25, .y = 0.75},
        };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha primeiro quadrado AZUL
    drawPolygon(AZUL, 4, v_array);
    // Seta o vertex da translação para descer em X e Y
    v_translacao.x = -0.5, v_translacao.y = -0.5;
    // Aplica a translação no array
    translate(v_array, 4, v_translacao);
    // Desenha o quadrado tranaladado em VERDE
    drawPolygon(VERDE, 4, v_array);

    glutSwapBuffers();
}

void display_rotacao(void)
{

    /* Array base das transformações*/
    Vertex v_array[] =
        {
            {.x = -0.25, .y = -0.25},
            {.x = 0.75, .y = -0.25},
            {.x = 0.75, .y = 0.75},
            {.x = -0.25, .y = 0.75},
        };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha primeiro quadrado AZUL
    drawPolygon(AZUL, 4, v_array);
    // Seta o vertex da rotacionado pra reduzir pela metade o X e o Y do quadrado
    int angulo = 45;
    // Aplica a escala no array
    rotate(v_array, 4, angulo);
    // Desenha o quadrado rotacionado em VERDE
    drawPolygon(VERDE, 4, v_array);

    glutSwapBuffers();
}

/* Escala o objeto no lugar, ele fica centralizado*/
void escala(Vertex *v_array, int vertex_num, Vertex v_escala)
{
    Vertex mid_vertex;
    mid_vertex.x = mid_vertex.y = (v_array[1].x + v_array[1].y) / 2; // Ponto central da figura
    for (int i = 0; i < vertex_num; i++)
    {

        /* Translada os pontos  */
        v_array[i].x -= mid_vertex.x;
        v_array[i].y -= mid_vertex.y;
        /* Escala os pontos */
        v_array[i].x *= v_escala.x;
        v_array[i].y *= v_escala.y;
        /* Retorna os pontos para sua posição original */
        v_array[i].x += mid_vertex.x;
        v_array[i].y += mid_vertex.y;
    }
}

/* Escala que move o objeto de lugar*/
void escala_relacao_origem(Vertex *v_array, int vertex_num, Vertex v_escala)
{
    for (int i = 0; i < vertex_num; i++)
    {
        v_array[i].x *= v_escala.x;
        v_array[i].y *= v_escala.y;
    }
}

void rotate(Vertex *v_array, int vertex_num, int angulo)
{
    Vertex mid_vertex, temp;
    mid_vertex.x = mid_vertex.y = (v_array[1].x + v_array[1].y) / 2; // Ponto central da figura

    for (int i = 0; i < vertex_num; i++)
    {
        /* Translada os pontos para em torno da  origem */
        v_array[i].x -= mid_vertex.x;
        v_array[i].y -= mid_vertex.y;
        temp = v_array[i];
        /* Rotaciona os pontos */
        v_array[i].x = (temp.x * cos(angulo * (3.14 / 180))) - (temp.y * sin(angulo * (3.14 / 180)));
        v_array[i].y = (temp.y * cos(angulo * (3.14 / 180))) + (temp.x * sin(angulo * (3.14 / 180)));
        /* Retorna os pontos para sua posição original */
        v_array[i].x += mid_vertex.x;
        v_array[i].y += mid_vertex.y;
    }
}

void translate(Vertex *v_array, int vertex_num, Vertex v_translate)
{
    for (int i = 0; i < vertex_num; i++)
    {
        v_array[i].x += v_translate.x;
        v_array[i].y += v_translate.y;
    }
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
    glutCreateWindow("ESCALA");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Registrar os callbacks
    glutDisplayFunc(display_escala);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    // Cria a segunda janela
    glutCreateWindow("ROTACAO");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //define a window position for second window
    glutPositionWindow(540, 40);
    // Registrar os callbacks
    glutReshapeFunc(handleResize);
    glutDisplayFunc(display_rotacao);
    glutKeyboardFunc(handleKeypress);

    // Cria a terceira janela
    glutCreateWindow("TRANSLACAO");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //define a window position for second window
    glutPositionWindow(540, 60);
    // Registrar os callbacks
    glutReshapeFunc(handleResize);
    glutDisplayFunc(display_translate);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();

    free(AZUL);
    free(VERDE);
    free(VERMELHO);
    return 0;
}

void drawPolygon(Cor *cor, int vertex_num, Vertex *v_array)
{
    // Define um poligono, pois não se sabe quantos vertices serão passados
    glBegin(GL_POLYGON);
    glColor3d((*cor).RED, (*cor).GREEN, (*cor).BLUE);

    for (int i = 0; i < vertex_num; i++)
    {
        glVertex2f(v_array[i].x, v_array[i].y);
    }
    glEnd();
}