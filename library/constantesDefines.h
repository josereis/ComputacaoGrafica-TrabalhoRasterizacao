/**
 * Contem todas as variaveis globais e definições utilizadas no trabalho
 **/
#define RETA 1
#define QUADRADO 2
#define TRIANGULO 3
#define POLIGONO 4
#define CIRCUFERENCIA 5
#define EIXO_X 100
#define EIXO_Y 101

 /* Variaveis Globais*/
int controleCirculo = 0; // variavel responsavel por fazer o controle da translação do circulo criado
int width = 512, heigth = 512;
double x_1, y_1, x_2, y_2, x_3, y_3;
bool click1 = false, click2 = false, click3 = false, transformacao = false;

/* VARIAVEL QUE GUARDA A OPÇÃO DESEJADA ('r' -> desenha reta | 'q' -> desenha quadrado. e as constantes de cada opcao*/
int op;

/* Lista encadeada de pontos (funciona como uma PILHA): indica o topo da pilha */
tPonto * pontos = NULL;
