/**
 * manipulaPilha.h; Contém as funções responsaveis por manipular a pilha de pontos. Funções de empilhamento e desempilhamento
 **/

/* Função para armazenamento de um ponto na lista. Armazena como uma PILHA (EMPILHAR) */
tPonto * empilharPonto(int x, int y) {
    tPonto * pnt;

    pnt = new ponto;
    // inicializa novo ponto a ser inserido na pilha
    pnt->x = x;
    pnt->y = y;
    pnt->prox = pontos; // faz novo ponto apontar par o topo da pilha atual;

    // atualiza topo da pilha
    pontos = pnt;

    return pnt;
}

/* Função para armazenamento de um ponto na lista. Armazena como uma PILHA (EMPILHAR) */
tPonto * empilharPontoCirculo(int x, int y) {
    tPonto * pnt;

    pnt = new ponto;
    // inicializa novo ponto a ser inserido na pilha
    pnt->x = x;
    pnt->y = y;
    pnt->controle = controleCirculo;
    pnt->prox = pontos; // faz novo ponto apontar par o topo da pilha atual;

    // atualiza topo da pilha
    pontos = pnt;

    return pnt;
}

/* Função de desarmazenamento de um ponto na lista. Desarmazena como uma PILHA (DESEMPILHAR) */
tPonto * desempilharPonto() {
    tPonto * pnt = NULL;

    // verifica se a lista não  vazia
    if(pontos != NULL) {
        pnt = pontos->prox;
        delete pontos; // remove topo da pilha
        pontos = pnt;
    }

    return pnt;
}

/* Função responsavel por limpar a lista encadeada (PILHA), ou seja, apaga-la da memoria */
void limparPilha() {
    tPonto * pnt;
    while(pontos != NULL) {
        pnt = pontos->prox;

        free(pontos); // limpa ponto da memoria

        pontos = pnt;
    }
}
