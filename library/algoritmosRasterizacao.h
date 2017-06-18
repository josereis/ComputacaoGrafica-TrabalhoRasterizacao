/**
 * algoritmosRasterizacao.h: Contém os algoritmos de rasterização usados no trabalho
 **/

/* ALGORITMO DA RETA IMEDIATO */
void retaImediata(double x1, double y1, double x2, double y2) {
    double m, b, yd, xd;
    double xmin, ymin, xmax, ymax;

    // armazena os pontos extremos para desenho
    pontos = empilharPonto((int)x1, (int)y1);
    pontos = empilharPonto((int)x2, (int)y2);

    // evita divisão por zero
    if(x2 - x1 != 0) {
        m = (y2 - y1)/(x2 - x1);
        b = y1 - (m*x1);

        // verifica se o declive da reta tem tangente entre os valores -1 e 1, caso VERDADEIRO calcula incrementando x
        if(m >= -1 && m <= 1) {
            xmin = (x1 < x2)? x1 : x2;
            xmax = (x1 > x2)? x1 : x2;

            for(int x = (int)xmin+1; x < xmax; x++){
                yd = (m*x) + b;
                yd = floor(0.5 + yd);
                pontos = empilharPonto(x, (int)yd);
            }
        } else { // caso menor que -1 ou maior que 1, calcula incrementando valor de y
            ymin = (y1 < y2)? y1 : y2;
            ymax = (y1 > y2)? y1 : y2;

            for(int y = (int)ymin + 1; y < ymax; y++){
                xd = (y - b)/m;
                xd = floor(0.5 + xd);
                pontos = empilharPonto((int)xd, y);
            }
        }
    } else { // se x2 - x1 == 0, a reta é perpendicular ao eixo x
        ymin = (y1 < y2)? y1 : y2;
        ymax = (y1 > y2)? y1 : y2;

        for(int y = (int)ymin + 1; y < ymax; y++){
            pontos = empilharPonto((int)x1, y);
        }
    }
}

/* ALGORITMO DE BRENSEHAM PARA RETAS NO PRIMEIRO OCTANTE*/
void brensehamPrimeiroOctante(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1;
    double d = 2*dy - dx;

    int x, y;
    if(x1 > x2) {
        x = (int)x2;
        y = (int)y2;
    } else {
        x = (int)x1;
        y = (int)y1;
    }

    pontos = empilharPonto(x, y);
    while(x < x2) {
        x++;
        if(d < 0) {
            d += 2*dy;
        } else {
            y++;
            d += 2*(dy - dx);
        }

        pontos = empilharPonto(x, y);
    }
}

/* ALGORITMO DE REDUÇÃO AO PRIMEIRO OCTANTE */
void brensehamCompleto(double x1, double y1, double x2, double y2) {
    double x = x1, y = y1, c, m, d, dx, dy, incX, incY;

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx < 0) {
        dx = -dx;
        incX = -1;
    } else {
        incX = 1;
    }

    if(dy < 0) {
        dy = -dy;
        incY = -1;
    } else {
        incY = 1;
    }

    if(dy <= dx) {
        c = 2*dx;
        m = 2*dy;

        if(incX < 0) {
            dx++;
        }

        while(!(x == x2)) {
            empilharPonto(x, y);

            d += m;
            x += incX;

            if(d >= dx) {
                d -= c;
                y += incY;
            }
        }
    } else {
        c = 2*dy;
        m = 2*dx;

        if(incY < 0) {
            dy++;
        }

        while(!(y == y2)) {
            empilharPonto(x, y);

            d += m;
            y += incY;

            if(d >= dy) {
                d -= c;
                x += incX;
            }
        }
    }
}

/** Implementações para o desenho do Circulo **/

/* função para salvar os pontos do circulo no ponteiro */
void salvaP(double x, double y) {
    empilharPontoCirculo(x, y);
    empilharPontoCirculo(y, x);

    empilharPontoCirculo(y, -x);
    empilharPontoCirculo(x, -y);

    empilharPontoCirculo(-x, -y);
    empilharPontoCirculo(-y, -x);

    empilharPontoCirculo(-y, x);
    empilharPontoCirculo(-x, y);
}

void brensehamCirculo (double x1, double y1, double x2, double y2) {
    int raio;
    double d, dE, dSe, xc, yc;

    // calcula raio a partir dos dois pontos pegos pelo mouse
    raio = sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));

    xc = 0;
    yc = raio;
    d = 1 - raio;
    dE = 3;
    dSe = ((-2)*raio) + 5;

    empilharPontoCirculo(raio, 0);
    empilharPontoCirculo(0, raio);
    empilharPontoCirculo(-raio, 0);
    empilharPontoCirculo(0, -raio);

    while(xc < yc) {
        if(d < 0) {
            d += dE;
            dE += 2;
            dSe += 2;
        } else {
            d += dSe;
            dE += 2;
            dSe += 4;
            yc--;
        }

        xc++;
        salvaP(xc, yc);
    }
    fazTranslacao(x1, y1);
    controleCirculo++;
}

/** Implementa funções de rasterização de poligonos de forma a preencher as formas geometricas rasterizadas, com excessão da circunferencia **/
