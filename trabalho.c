#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* Struct Vertex para implementar uma estrutura de dados de ponto */
typedef struct vertex Vertex;
struct vertex
{
    double x;
    double y;
};

void display(void);
void keyboard(unsigned char key, int x, int y);
void drawPolygon(int vertex_num, ...);
Vertex* translate(Vertex *v_array, Vertex dv, int vertex_num, ...);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
    glOrtho(0, 1, 0, 1, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
void display(void)
{
    int i;
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
    }, dv = {.x = 0.5, .y = 0.5}, *v_array_t = (Vertex*) malloc(4 * sizeof(Vertex)); 

    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawPolygon(4, v_array[0], v_array[1], v_array[2], v_array[3]);                             // Desenha o polígono antes de transladar
    v_array_t = translate(v_array_t, dv, 4, v_array[0], v_array[1], v_array[2], v_array[3]);    // Translada
    drawPolygon(4, v_array_t[0], v_array_t[1], v_array_t[2], v_array_t[3]);                     // Desenha o polígono transladado
    
    /* @ Debug para ver se os pontos foram transladados */
    for(i = 0; i < 4; i++)
        printf("@ v_array_t[%d] = %lf\n", i, v_array_t[i]);                                     

    /*
    glBegin(GL_POLYGON);
        glVertex2f(0.25, 0.25);
        glVertex2f(0.75, 0.25);
        glVertex2f(0.75, 0.75);
        glVertex2f(0.25, 0.75);

    glEnd();
    */

    glFlush();
}

Vertex* translate(Vertex *v_array, Vertex dv, int vertex_num, ...)
{
    
    int i;
    va_list vertex_list;

    va_start(vertex_list, vertex_num);
    for(i = 0; i < vertex_num; i++)
    {
        v_array[i] = va_arg(vertex_list, Vertex);
        v_array[i].x += dv.x;
        v_array[i].y += dv.y;
    }

    return v_array;
}

void drawPolygon(int vertex_num, ...)
{
    Vertex *v_array;
    int i;
    va_list vertex_list;

    va_start(vertex_list, vertex_num);
    v_array = (Vertex*) malloc(vertex_num * sizeof(Vertex));
    glBegin(GL_POLYGON);
        for(i = 0; i < vertex_num; i++)
        {
            v_array[i] = va_arg(vertex_list, Vertex);
            glVertex2d(v_array[i].x, v_array[i].y);
        }
    glEnd();
}