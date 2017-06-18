
/**
 *
 **/

/* função responsavel por fazer a translacao de um objeto */
void fazTranslacao(int translacaoX, int translacaoY) {
    tPonto * pnt = pontos;

    while(pnt != NULL) {
        pnt->x = pnt->x + translacaoX;
        pnt->y = pnt->y + translacaoY;

        pnt = pnt->prox;
    }
}

/* função responsavel por receber o valor das transalações em X e Y e chamar a função 'fazTranslacao(int translacaoX, int translacaoY) */
void translacao() {
    int translacaoX, translacaoY;

    printf("\n=> INFORME O VALOR DA TRANSLACAO EM X (VALOR INTEIRO): ");
    scanf("%d", &translacaoX);
    printf("\n=> INFORME O VALOR DA TRANSLACAO EM Y (VALOR INTEIRO): ");
    scanf("%d", &translacaoY);

    fazTranslacao(translacaoX, translacaoY);
}

/* função responsavel por fazer a escala no objetos geometricos */
void escala() {
    tPonto * pnt = pontos;
    int escala, translacaoX = pnt->x, translacaoY = pnt->y;

    printf("\n=> INFORME A ESCALA DESEJADA (VALOR INTEIRO): ");
    scanf("%d", &escala);

    // translada o primeiro ponto para a origem para fazer a escala
    fazTranslacao(-translacaoX, -translacaoY);

    // aplica a escala
    while(pnt != NULL) {
        pnt->x = pnt->x*escala;
        pnt->y = pnt->y*escala;

        pnt = pnt->prox;
    }

    // translada o primeiro ponto para a posicao inicial
    fazTranslacao(translacaoX, translacaoY);

}

/* função responsavel por fazer o cisalhamento da forma geometrica */
void fazCisalhamento(int eixo, int fator) {
    tPonto * pnt = pontos;
    int maiorX = pnt->x, maiorY = pnt->y;

    while(pnt != NULL) {
        if((maiorX < pnt->x)&&(maiorY < pnt->y)) {
            maiorX = pnt->x;
            maiorY = pnt->y;
        }

        pnt = pnt->prox;
    }

    // translada para a origem
    fazTranslacao(-maiorX, -maiorY);

    // faz o cisalhamento
    pnt = pontos;
    while(pnt != NULL) {
        if(eixo == EIXO_X) {
            pnt->x += pnt->y*fator;
        } else if(eixo == EIXO_Y) {
            pnt->y += pnt->x*fator;
        }

        pnt = pnt->prox;
    }

    // translada para ponto anterior;
    fazTranslacao(maiorX, maiorY);
}

/* função responsavel por receber os dados para realização do cisalhamento */
void cisalhamento() {
    char eixo;
    int fator;

    printf("\n=>EIXO DE CISALHAMENTO (X ou Y): ");
    scanf(" %c", &eixo);
    printf("\n=>FATOR DE CISALHAMENTO (VALOR INTEIRO): ");
    scanf("%d", &fator);

    switch(eixo) {
        case 'x': fazCisalhamento(EIXO_X, fator);
            break;
        case 'X': fazCisalhamento(EIXO_X, fator);
            break;
        case 'y': fazCisalhamento(EIXO_Y, fator);
            break;
        case 'Y': fazCisalhamento(EIXO_Y, fator);
            break;
    }
}

/* função responsavel por fazer a reflexão */
void fazReflexao(int eixo) {
    tPonto * pnt = pontos;

    fazTranslacao(-x_1, -y_1);
    if(eixo == EIXO_X) {
        while(pnt != NULL) {
            pnt->y = pnt->y*-1;
            pnt = pnt->prox;
        }
    } else if(eixo == EIXO_Y) {
        while(pnt != NULL) {
            pnt->x = pnt->x*-1;
            pnt = pnt->prox;
        }
    }
    fazTranslacao(x_1, y_1);
}

/* função que recebe qual o eixo de reflexo*/
void reflexao() {
    char eixo;

    printf("\n=>EIXO DE REFLEXAO (X ou Y): ");
    scanf(" %c", &eixo);

    switch(eixo) {
        case 'x': fazReflexao(EIXO_X);
            break;
        case 'X': fazReflexao(EIXO_X);
            break;
        case 'y': fazReflexao(EIXO_Y);
            break;
        case 'Y': fazReflexao(EIXO_Y);
            break;
    }
}

/* função que faz a rotação */
void fazRotacao(double angulo) {
    tPonto * pnt = pontos;
    int x = pnt->x, y = pnt->y, xTem, yTem;

    fazTranslacao(-x, -y);
    while(pnt != NULL) {
        xTem = pnt->x;
        yTem = pnt->y;

        pnt->x = (int)((xTem*cos(angulo)) - (yTem*sin(angulo)));
        pnt->y = (int)((xTem*sin(angulo)) + (yTem*cos(angulo)));

        pnt = pnt->prox;
    }
    fazTranslacao(x, y);
}

/* Função que recebe o angulo para rotação */
void rotacao() {
    double angulo;
    printf("Angulo de rotacao(EM GRAUS):");
    scanf("%lf", &angulo);

    fazRotacao(angulo);
}

/* função que chama a tranformação requerida */
void transformacaoGeometrica(int key) {
    if(op == QUADRADO || op == TRIANGULO || op == CIRCUFERENCIA || op == POLIGONO) {
        switch(key) {
            case 49: {printf("\nTranslacao\n"); translacao();}
                break;
            case 50: {printf("\nEscala\n"); escala();}
                break;
            case 51: {printf("\nCisalhamento\n"); cisalhamento();}
                break;
            case 52: {printf("\nReflexao\n"); reflexao();} // <= ajeitar
                break;
            case 53: {printf("\nRotacaao\n"); rotacao();}
                break;
        }
    }
}
