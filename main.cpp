/**
  * @author: José Reis Ribeiro Santiago
  * @description: Trabalho de Rasterização, que tem por objetivo implementar as tecnicas e algoritmos usados para rasterizar objetos
 **/

/* Bibliotecas usadas pelo OpenGL */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Bibliotecas que implementam funções matemáticas */
#include <cmath>
#include <cstdio>
#include <cstdlib>

/* Biblioteca que contem as estruturas (struct's) a serem usadas no trabalho */
#include "library/structs.h"
/* Bblioteca (arquivo) que contém todas as variaveis globlais usadas no trabalho */
#include "library/constantesDefines.h"
/* Biblioteca que contém as funções responsaveis por manipulação dos pontos na pilha */
#include "library/manipulaPilha.h"
/* Biblioteca que contém as funções referêntes as transformações geometricas */
#include "library/transformacoes.h"
/* Biblioteca que comtém as funções que implementam os algoritmos de rasterização */
#include "library/algoritmosRasterizacao.h"
/* Biblioteca que cóntém as funções referentes a criação de poligonos*/
#include "library/poligonos.h"

/* Declaração das funções utilizadas pelo OpenGL */
void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

/* Funcao que percorre a lista de pontos desenhando-os na tela */
void drawPontos();

int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // passagens de parametro C para o glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // selecao do Modo do Display e do Sistema de cor utilizado
    glutInitWindowSize(width, heigth);             // tamanho da janela do OpenGL
    glutInitWindowPosition (100, 100);              // posicao inicial da janela do OpenGL
    glutCreateWindow("Trabalho de Rasterizacao");  // da nome para uma janela OpenGL

    init();                                         // Chama funcao init();
    glutReshapeFunc(reshape);                       // funcao callback para redesenhar a tela
    glutKeyboardFunc(keyboard);                     // funcao callback do teclado
    glutMouseFunc(mouse);                           // funcao callback do mouse
    glutDisplayFunc(display);                       // funcao callback de desenho
    glutMainLoop();                                 // executa o loop do OpenGL

    return 0;
}

/* Função com comando para inicialização do OpwnGL */
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

/*  */
void reshape(int w, int h) {
    // define o ViewPort para o tamanho da janela
    glViewport(0, 0, w, h);

    // reinicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    heigth = h;
    width = w;
    glOrtho(0, w, 0, h, -1, 1);

    // muda para o modo GL_MODELVIEW (não se pretende alterar a projeção quando quando estiver desenhando na tela)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(op == RETA || op == QUADRADO || op == CIRCUFERENCIA) {
        click1 = true;
        click2 = true;
    } else if(op == TRIANGULO) {
        click1 = true;
        click2 = true;
        click3 = true;
    }

}

/* função responsavel por limpar a tela e a pilha*/
void atualizaTela() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);; //Limpa o Buffer de Cores
    glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto

    drawPontos();

    glutSwapBuffers(); // manda o OpenGl renderizar as primitivas
}

/* Função usada para utilização das teclas normais do teclado */
void keyboard(unsigned char key, int x, int y) {
    //fflush(stdin);
    switch(key) { // key - variavel que possui o valor ASCII da tecla precionada
        case 48: // código ASCII para tecla '0'
            {
                start = !start; // usado para saber quantos pontos capturar como vertices
                printf("\n=> start <=\n");
            }
            break;
        case 49: // código ASCII para tecla '1'
            {
                transformacaoGeometrica(key);
                atualizaTela();
            }
            break;
        case 50: // código ASCII para tecla '2'
            {
                transformacaoGeometrica(key);
                atualizaTela();
            }
            break;
        case 51: // código ASCII para tecla '3'
            {
                transformacaoGeometrica(key);
                atualizaTela();
            }
            break;
        case 52: // código ASCII para tecla '4'
            {
                transformacaoGeometrica(key);
                atualizaTela();
            }
            break;
        case 53: // código ASCII para tecla '5'
            {
                transformacaoGeometrica(key);
                atualizaTela();
            }
            break;
        case 99: // código ASCII para tecla 'c'
            {
                click1 = false;
                click2 = false;
                op = CIRCUFERENCIA;
                printf("\nCIRCUNFERENCIA...\n");
            }
            break;
        case 112: // código ASCII para tecla 'p'
            {
                op = POLIGONO;
                click1 = false;
                printf("\nPOLIGONO\n");
            }
            break;
        case 113: // código ASCII tecla 'q'
            {
                op = QUADRADO;
                click1 = false;
                click2 = false;
                printf("\nQUADRADO\n");
            }
            break;
        case 114: // código ASCII tecla 'r'
            {
                op = RETA;
                click1 = false;
                click2 = false;
                printf("\nRETA\n");
            }
            break;
        case 116: // código ASCII para a tecla 't'
            {
                op = TRIANGULO;
                click1 = false;
                click2 = false;
                click3 = false;
                printf("\nTRIANGULO\n");
            }
            break;
        case 108: // código ASCII tecla 'l'
            { // para limpar a tela
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);; //Limpa o Buffer de Cores
                glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto
                glutSwapBuffers(); // manda o OpenGl renderizar as primitivas

                // limpar a pilha
                limparPilha();
            }
            break;
        case 27: // código ASCIIda tecla ESC
            {
                limparPilha();
                exit(0);
            }
            break;
        default:
            break;
    }
}

/* Função usada para utilização do mouse */
void mouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            {
                if(state == GLUT_DOWN) {
                    if(op == TRIANGULO) {
                        if(click1 && !click2) {
                            click2 = true;
                            x_2 = x;
                            y_2 = heigth - y;
                            printf("x2y2(%.0f,%.0f)\n",x_2,y_2);
                        } else if(click2) {
                            click3 = true;
                            x_3 = x;
                            y_3 = heigth - y;
                            printf("x3y3(%.0f,%.0f)\n",x_3,y_3);

                            glutPostRedisplay();
                        } else {
                            click1 = true;

                            x_1 = x;
                            y_1 = heigth - y;
                            printf("x1y1(%.0f,%.0f)\n",x_1,y_1);
                        }
                    } else if(op == RETA || op == QUADRADO || op == CIRCUFERENCIA) {
                        if(click1) {
                            click2 = true;
                            x_2 = x;
                            y_2 = heigth - y;
                            printf("x2y2(%.0f,%.0f)\n",x_2,y_2);

                            glutPostRedisplay();
                        } else {
                            click1 = true;

                            x_1 = x;
                            y_1 = heigth - y;
                            printf("x1y1(%.0f,%.0f)\n",x_1,y_1);
                        }
                    } else if(op == POLIGONO) {
                        if(start) {
                            click1 = true;

                            x_1 = x;
                            y_1 = heigth - y;
                            printf("xy(%.0f,%.0f)\n", x_1, y_1);

                            glutPostRedisplay();
                        } else {
                            click1 = true;
                            glutPostRedisplay();
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
}

/* Funcao usada para desenhar na tela */
void display(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpa o Bbffer de cores
    glColor3f (0.0, 0.0, 0.0); // seleciona a cor default como preto


    if(op == RETA || op == QUADRADO || op == CIRCUFERENCIA) {
        if(click1 && click2) {
            if(op == RETA) {
                fazReta(x_1, y_1, x_2, y_2);
            } else if(op == QUADRADO) {
                fazQuadrado(x_1, y_1, x_2, y_2);
            } else if(op == CIRCUFERENCIA) {
                fazCirculo(x_1, y_1, x_2, y_2);
            }

            drawPontos();

            click1 = false;
            click2 = false;
        }
    } else if(op == TRIANGULO) {
        if(click1 && click2 && click3) {
            fazTriangulo(x_1, y_1, x_2, y_2, x_3, y_3);

            drawPontos();

            click1 = false;
            click2 = false;
            click3 = false;
        }
    } else if(op == POLIGONO) {
        // implementar funções referentes ao desenho de poligonos
        if(click1) {
            if(start) {
                empilharVertice(x_1, y_1);
                click1 = false;
            } else {
                fazPoligono();

                drawPontos();

                click1 = false;
            }
        }
//        if(start) {
//            if(click1) {
//                empilharVertice(x_1, y_1);
//                click1 = false;
//            }
//        } else {
//            fazPoligono();
//
//            drawPontos();
//
//            click1 = false;
//        }
    }

    transformacao = true; // habilita transformações

    glutSwapBuffers(); // manda o OpenGl renderizar as primitivas
}

/* Funcao que desenha os pontos contidos em uma lista de pontos */
void drawPontos(){
    tPonto * pnt;
    pnt = pontos;
    glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar

    while(pnt != NULL){
        glVertex2i(pnt->x,pnt->y);
        pnt = pnt->prox;
    }

    glEnd();  // indica o fim do desenho
}
