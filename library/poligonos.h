/**
 * poligonos.h: Contém as funções responsaveis por desenhar as formas geometricas na tela
**/

/* Desenha Reta */
void fazReta(int x1, int y1, int x2, int y2) {
    brensehamCompleto(x1, y1, x2, y2);
}

void fazTriangulo(int x1, int y1, int x2, int y2, int x3, int y3){
    brensehamCompleto(x1, y1, x2, y2);
    brensehamCompleto(x2, y2, x3, y3);
    brensehamCompleto(x1, y1, x3, y3);
}

/* Desenha Quadrado */
void fazQuadrado(int x1, int y1, int x2, int y2) {
    brensehamCompleto(x1, y1, x1, y2); //Primeira coordenada
    brensehamCompleto(x1, y2, x2, y2); //Segunda coordenada
    brensehamCompleto(x2, y2, x2, y1); //Terceira coordenada
    brensehamCompleto(x2, y1, x1, y1); //Quarta coordenada
}

/** FUNÇÕES REFERENTES A CRIAÇÃO DA CIRCUNFERENCIA **/
void fazCirculo(int x1, int y1, int x2, int y2) {
    brensehamCirculo(x1, y1, x2, y2);
}

/** FUNÇÕES REFERENTES A IMPLEMENTAÇÃO DOS ALGORITMOS PARA DESENHO DE POLIGONOS DE N VERTICES **/
bool start = false; // para o controle da quantidade de pontos
tVerticesPoligono vertices; // lista que armazenará os vertices do poligono a ser desenhado

/* função responsavel por inicializar a lista */
void inicializaListaVertices() {
    vertices.vertices = NULL;
    vertices.numeroVertices = 0;
}

/* função responsavel por empilhar os vertices do poligono */
tPonto * empilharVertice(int x, int y) {
    tPonto * pnt = new ponto;

    if(pnt == NULL) {
        printf("\n=> ERRO: não foi possivel alocar espaco na memoria para o vertice.");
        return 0;
    } else {
        pnt->x = x;
        pnt->y = y;
        pnt->prox = vertices.vertices;

        vertices.vertices = pnt;
        vertices.numeroVertices++;

        return pnt;
    }
}

/* função responsavel por desempilhar os vertices do poligono */
void desempilharVertice() {
    tPonto * pnt = NULL;

    while(vertices.vertices != NULL) {
        pnt = vertices.vertices;
        vertices.vertices = pnt->prox;

        delete pnt;

        vertices.numeroVertices--;
    }
}

void fazPoligono() {
   tPonto * pnt = vertices.vertices;

   while(pnt != NULL) {
        if(pnt->prox == NULL) { // esta no ultimo ponto
            brensehamCompleto(pnt->x, pnt->y, vertices.vertices->x, vertices.vertices->y);
        } else {
            brensehamCompleto(pnt->x, pnt->y, pnt->prox->x, pnt->prox->y);
        }

        pnt = pnt->prox;
   }
   desempilharVertice();
}
