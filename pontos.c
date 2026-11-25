#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

typedef struct {
    float pontos[3];
} tPonto;

tPonto SomaPontos(tPonto p1, tPonto p2) {
    tPonto p3 = {{0}};
    for (int i = 0; i < 3; i++) {
        p3.pontos[i] = p1.pontos[i] + p2.pontos[i];
    }
    return p3;
}

tPonto SubtracaoPontos(tPonto p1, tPonto p2) {
    tPonto p3 = {{0}};
    for (int i = 0; i < 3; i++) {
        p3.pontos[i] = p1.pontos[i] - p2.pontos[i];
    }
    return p3;
}

void plotarPontos3D(tPonto p1, tPonto p2, tPonto soma, tPonto sub) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Erro ao abrir o Gnuplot.\n");
        return;
    }

    fprintf(gp, "set title 'Operacoes com Pontos 3D'\n");
    fprintf(gp, "set xlabel 'X'\n");
    fprintf(gp, "set ylabel 'Y'\n");
    fprintf(gp, "set zlabel 'Z'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set zeroaxis\n"); // Mostra os eixos X, Y, Z passando pela origem (0,0,0)

    // 1º bloco: vetores (setas) da origem até cada ponto
    // 2º bloco: linhas tracejadas ligando P1 -> Soma -> P2 (regra do paralelogramo)
    // 3º bloco: bolinhas nos pontos
    // 4º bloco: nomes dos pontos
    fprintf(gp, "splot '-' using 1:2:3:4:5:6 with vectors lw 2 lc rgb 'blue' title 'Vetores', "
                "'-' using 1:2:3 with lines dt 2 lw 1.5 lc rgb 'gray' title 'Paralelogramo', "
                "'-' using 1:2:3 with points pt 7 ps 1.5 lc rgb 'red' notitle, "
                "'-' using 1:2:3:4 with labels offset char 1,1 notitle\n");

    // 1. Vetores saindo de (0,0,0) até cada ponto (x0 y0 z0 dx dy dz)
    fprintf(gp, "0 0 0 %f %f %f\n", p1.pontos[0], p1.pontos[1], p1.pontos[2]);
    fprintf(gp, "0 0 0 %f %f %f\n", p2.pontos[0], p2.pontos[1], p2.pontos[2]);
    fprintf(gp, "0 0 0 %f %f %f\n", soma.pontos[0], soma.pontos[1], soma.pontos[2]);
    fprintf(gp, "0 0 0 %f %f %f\n", sub.pontos[0], sub.pontos[1], sub.pontos[2]);
    fprintf(gp, "e\n");

    // 2. Traços tracejados fechando a soma (P1 -> Soma -> P2)
    fprintf(gp, "%f %f %f\n", p1.pontos[0], p1.pontos[1], p1.pontos[2]);
    fprintf(gp, "%f %f %f\n", soma.pontos[0], soma.pontos[1], soma.pontos[2]);
    fprintf(gp, "%f %f %f\n", p2.pontos[0], p2.pontos[1], p2.pontos[2]);
    fprintf(gp, "e\n");

    // 3. Coordenadas dos pontos
    fprintf(gp, "%f %f %f\n", p1.pontos[0], p1.pontos[1], p1.pontos[2]);
    fprintf(gp, "%f %f %f\n", p2.pontos[0], p2.pontos[1], p2.pontos[2]);
    fprintf(gp, "%f %f %f\n", soma.pontos[0], soma.pontos[1], soma.pontos[2]);
    fprintf(gp, "%f %f %f\n", sub.pontos[0], sub.pontos[1], sub.pontos[2]);
    fprintf(gp, "e\n");

    // 4. Rótulos
    fprintf(gp, "%f %f %f \"P1\"\n", p1.pontos[0], p1.pontos[1], p1.pontos[2]);
    fprintf(gp, "%f %f %f \"P2\"\n", p2.pontos[0], p2.pontos[1], p2.pontos[2]);
    fprintf(gp, "%f %f %f \"Soma\"\n", soma.pontos[0], soma.pontos[1], soma.pontos[2]);
    fprintf(gp, "%f %f %f \"Sub\"\n", sub.pontos[0], sub.pontos[1], sub.pontos[2]);
    fprintf(gp, "e\n");

    pclose(gp);
}

int main() {
    tPonto ponto1;
    tPonto ponto2;

    puts("De as coordenadas (x y z) do primeiro ponto:");
    for (int i = 0; i < 3; i++) {
        scanf("%f", &ponto1.pontos[i]);
    }

    puts("De as coordenadas (x y z) do segundo ponto:");
    for (int i = 0; i < 3; i++) {
        scanf("%f", &ponto2.pontos[i]);
    }

    tPonto soma = SomaPontos(ponto1, ponto2);
    tPonto sub = SubtracaoPontos(ponto1, ponto2);

    plotarPontos3D(ponto1, ponto2, soma, sub);

    return 0;
}
