/**
 * Structs.h: Contém todas as struturas a serem usadas no trabalho
 **/

/* Struct que representará um ponto. Selecionada pelos algoritmos de rasterização */
typedef struct ponto {
    int x, y, controle; // variavel 'controle' usada apenas para construcao da circunferencia

    ponto * prox;
} tPonto;

/* Struct que representará uma fila para armazenamento de todos os pontos escolhidos para o desenho de um poligno */
typedef struct verticesPoligono {
    tPonto * vertices;

    int numeroVertices;
} tVerticesPoligono;
