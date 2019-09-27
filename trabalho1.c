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
    double x;
    double y;
};
/*Definindo a struct das cores para facilitar*/
typedef struct cores Cor;
struct cores
{
    double RED;
    double GREEN;
    double BLUE;
};

void display_escala(void);
void display_escala_relacao_origem(void);
void display_translation(void);
void display_rotation(void);
void keyboard(unsigned char key, int x, int y);
void drawPolygon(Cor *cor, int vertex_num, ...);
Vertex *translate(Vertex *v_array, Vertex dv, int vertex_num, ...);
Vertex *rotate(Vertex *v_array, int angulo, int vertex_num, ...);
Vertex *escala(Vertex *v_array, Vertex ev, int vertex_num, ...);
Vertex *escala_relacao_origem(Vertex *v_array, Vertex ev, int vertex_num, ...);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        exit(2);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 900);
    glutInitWindowPosition(30, 30);
    glutCreateWindow(argv[1]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    glOrtho(0, 1, 0, 1, -1, 1);
    if (strcmp(argv[1], "e") == 0)
    {
        glutDisplayFunc(display_escala);
    }
    else if (strcmp(argv[1], "eo") == 0)
    {
        printf(argv[1]);
        glutDisplayFunc(display_escala_relacao_origem);
    }
    else if (strcmp(argv[1], "r") == 0)
    {
        glutDisplayFunc(display_rotation);
    }
    else if (strcmp(argv[1], "t") == 0)
    {
        glutDisplayFunc(display_translation);
    }
    else
    {
        printf("Entrada errada");
        return 1;
    }

    glutMainLoop();
    return 0;
}
void display_translation(void)
{
    /* 
    * Inicializa: 
    * vetor de pontos -> v_array
    * ponto de deslocamento -> dv
    * vetor de pontos transladados -> v_array_t
    */
    Vertex v_array[] =
        {
            {.x = 0.25, .y = 0.25},
            {.x = 0.75, .y = 0.25},
            {.x = 0.75, .y = 0.75},
            {.x = 0.25, .y = 0.75},
        },
           dv = {.x = -0.2, .y = 0.2}, // aumenta ou diminui o x ou y 
               *v_array_t = (Vertex *)malloc(4 * sizeof(Vertex));

    Cor *AZUL = (Cor *)calloc(1, sizeof(Cor));
    (*AZUL).BLUE = 1;
    Cor *VERMELHO = (Cor *)calloc(1, sizeof(Cor));
    (*VERMELHO).RED = 1;
    Cor *VERDE = (Cor *)calloc(1, sizeof(Cor));
    (*VERDE).GREEN = 1;

    glClear(GL_COLOR_BUFFER_BIT);
    // Desenha o polígono antes de transladar
    drawPolygon(AZUL, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Translada usando o dv
    v_array_t = translate(v_array_t, dv, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Desenha o polígono transladado
    drawPolygon(VERMELHO, 4, v_array_t[0], v_array_t[1], v_array_t[2], v_array_t[3]);

    /* @ Debug para ver se os pontos foram transladados */
    for (int i = 0; i < 4; i++)
        printf("@ v_array_t[%d] = %lf\n", i, v_array_t[i]);

    glFlush();
}
void display_rotation(void)
{
    /* 
    * Inicializa: 
    * vetor de pontos -> v_array
    * ponto de deslocamento -> dv
    * vetor de pontos rotacionados -> v_array_t
    */
    Vertex v_array[] =
        {
            {.x = 0.25, .y = 0.25},
            {.x = 0.75, .y = 0.25},
            {.x = 0.75, .y = 0.75},
            {.x = 0.25, .y = 0.75},
        },
           *v_array_r = (Vertex *)malloc(4 * sizeof(Vertex));

    int angulo = 25; // angulo para rotacionar em relação ao ponto central
    Cor *AZUL = (Cor *)calloc(1, sizeof(Cor));
    (*AZUL).BLUE = 1;
    Cor *VERMELHO = (Cor *)calloc(1, sizeof(Cor));
    (*VERMELHO).RED = 1;
    Cor *VERDE = (Cor *)calloc(1, sizeof(Cor));
    (*VERDE).GREEN = 1;

    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o polígono antes de rotacionar
    drawPolygon(AZUL, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // rotate usando o rv
    v_array_r = rotate(v_array_r, angulo, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Desenha o polígono rotacionado
    drawPolygon(VERMELHO, 4, v_array_r[0], v_array_r[1], v_array_r[2], v_array_r[3]);

    /* @ Debug para ver se os pontos foram rotacionados */
    for (int i = 0; i < 4; i++)
        printf("@ v_array_t[%d] = %lf\n", i, v_array_r[i]);

    glFlush();
}
void display_escala(void)
{
    /* 
    * Inicializa: 
    * vetor de pontos -> v_array
    * ponto de deslocamento -> dv
    * vetor de pontos escalados -> v_array_t
    */
    Vertex v_array[] =
        {
            {.x = 0.25, .y = 0.25},
            {.x = 0.75, .y = 0.25},
            {.x = 0.75, .y = 0.75},
            {.x = 0.25, .y = 0.75},
        },
           dv = {.x = 1.5, .y = 0.5}, //
               *v_array_t = (Vertex *)malloc(4 * sizeof(Vertex));

    Cor *AZUL = (Cor *)calloc(1, sizeof(Cor));
    (*AZUL).BLUE = 1;
    Cor *VERMELHO = (Cor *)calloc(1, sizeof(Cor));
    (*VERMELHO).RED = 1;
    Cor *VERDE = (Cor *)calloc(1, sizeof(Cor));
    (*VERDE).GREEN = 1;

    glClear(GL_COLOR_BUFFER_BIT);
    // Desenha o polígono antes de escalar
    drawPolygon(AZUL, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // escala usando o vd
    v_array_t = escala(v_array_t, dv, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Desenha o polígono escalado
    drawPolygon(VERMELHO, 4, v_array_t[0], v_array_t[1], v_array_t[2], v_array_t[3]);

    /* @ Debug para ver se os pontos foram escalados */
    for (int i = 0; i < 4; i++)
        printf("@ v_array_t[%d] = %lf\n", i, v_array_t[i]);

    glFlush();
}
void display_escala_relacao_origem(void)
{
    /* 
    * Inicializa: 
    * vetor de pontos -> v_array
    * ponto de deslocamento -> dv
    * vetor de pontos escalados -> v_array_t
    */
    Vertex v_array[] =
        {
            {.x = 0.25, .y = 0.25},
            {.x = 0.75, .y = 0.25},
            {.x = 0.75, .y = 0.75},
            {.x = 0.25, .y = 0.75},
        },
           dv = {.x = 0.2, .y = 0.2}, // escala mas a figura muda de lugar em relação a origem
               *v_array_t = (Vertex *)malloc(4 * sizeof(Vertex));

    Cor *AZUL = (Cor *)calloc(1, sizeof(Cor));
    (*AZUL).BLUE = 1;
    Cor *VERMELHO = (Cor *)calloc(1, sizeof(Cor));
    (*VERMELHO).RED = 1;
    Cor *VERDE = (Cor *)calloc(1, sizeof(Cor));
    (*VERDE).GREEN = 1;

    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(1.0, 0.0, 0.0);
    // Desenha o polígono antes de transladar
    drawPolygon(AZUL, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Translada usando o vd
    v_array_t = escala_relacao_origem(v_array_t, dv, 4, v_array[0], v_array[1], v_array[2], v_array[3]);
    // Desenha o polígono transladado
    drawPolygon(VERMELHO, 4, v_array_t[0], v_array_t[1], v_array_t[2], v_array_t[3]);

    /* @ Debug para ver se os pontos foram escalados */
    for (int i = 0; i < 4; i++)
        printf("@ v_array_t[%d] = %lf\n", i, v_array_t[i]);

    glFlush();
}

Vertex *translate(Vertex *v_array, Vertex dv, int vertex_num, ...)
{
    va_list vertex_list;

    va_start(vertex_list, vertex_num);
    for (int i = 0; i < vertex_num; i++)
    {
        v_array[i] = va_arg(vertex_list, Vertex);
        v_array[i].x += dv.x;
        v_array[i].y += dv.y;
    }
    va_end(vertex_list);
    return v_array;
}

Vertex *rotate(Vertex *v_array, int angulo, int vertex_num, ...)
{
    int i;
    va_list vertex_list;
    Vertex mid_vertex;

    va_start(vertex_list, vertex_num);

    for (i = 0; i < vertex_num; i++)
        v_array[i] = va_arg(vertex_list, Vertex);

    mid_vertex.x = mid_vertex.y = (v_array[1].x + v_array[1].y) / 2; // Ponto central da figura

    for (i = 0; i < vertex_num; i++)
    {
        /* Translada os pontos para em torno da  origem */
        v_array[i].x = v_array[i].x - mid_vertex.x;
        v_array[i].y = v_array[i].y - mid_vertex.y;
        /* Rotaciona os pontos */
        v_array[i].x = (v_array[i].x * cos(angulo * (3.14 / 180))) - (v_array[i].y * sin(angulo * (3.14 / 180)));
        v_array[i].y = (v_array[i].y * cos(angulo * (3.14 / 180))) + (v_array[i].x * sin(angulo * (3.14 / 180)));
        /* Retorna os pontos para sua posição original */
        v_array[i].x = v_array[i].x + mid_vertex.x;
        v_array[i].y = v_array[i].y + mid_vertex.y;
    }

    return v_array;
}
Vertex *escala(Vertex *v_array, Vertex ev, int vertex_num, ...)
{
    va_list vertex_list;
    Vertex mid_vertex;

    va_start(vertex_list, vertex_num);

    for (int i = 0; i < vertex_num; i++)
        v_array[i] = va_arg(vertex_list, Vertex);

    mid_vertex.x = mid_vertex.y = (v_array[1].x + v_array[1].y) / 2; // Ponto central da figura

    for (int i = 0; i < vertex_num; i++)
    {
        /* Translada os pontos  */
        v_array[i].x -= mid_vertex.x;
        v_array[i].y -= mid_vertex.y;
        /* Escala os pontos */
        v_array[i].x *= ev.x;
        v_array[i].y *= ev.y;
        /* Retorna os pontos para sua posição original */
        v_array[i].x += mid_vertex.x;
        v_array[i].y += mid_vertex.y;
    }

    va_end(vertex_list);
    return v_array;
}

Vertex *escala_relacao_origem(Vertex *v_array, Vertex ev, int vertex_num, ...)
{
    va_list vertex_list;

    va_start(vertex_list, vertex_num);
    for (int i = 0; i < vertex_num; i++)
    {
        v_array[i] = va_arg(vertex_list, Vertex);
        v_array[i].x *= ev.x;
        v_array[i].y *= ev.y;
    }
    va_end(vertex_list);
    return v_array;
}

void drawPolygon(Cor *cor, int vertex_num, ...)
{
    Vertex *v_array;
    va_list vertex_list;

    va_start(vertex_list, vertex_num);
    v_array = (Vertex *)malloc(vertex_num * sizeof(Vertex));
    glBegin(GL_POLYGON);
    glColor3f((*cor).RED, (*cor).GREEN, (*cor).BLUE);
    for (int i = 0; i < vertex_num; i++)
    {
        v_array[i] = va_arg(vertex_list, Vertex);
        glVertex2d(v_array[i].x, v_array[i].y);
    }
    glEnd();
    va_end(vertex_list);
}