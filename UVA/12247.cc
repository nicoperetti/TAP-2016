#define ALL(a) a.begin(), a.end()

#include <cstdio>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;


/* FALLA, pero está bueno para tener una idea */

/* Devuelve el indice de la mejor carta ganadora, si existe.
    Caso contrario, devuelve -1 */
int puede_ganar(array<int,3> princesa, int carta_principe) {
    int indice = -1;
    int carta = 53;  // numero más grande
    for (int i=0; i<3; i++) {
        if (princesa[i] > carta_principe && princesa[i] < carta) {
            indice = i;
            carta = princesa[i];
        }
    }
    return indice;
}


/* Devuelve el indice de la carta con la que la princesa pierde mejor.
   Se llama siempre despues de puede_ganar */
int perder_bien(array<int,3> princesa) {
    int indice = -1;
    int carta = 53;
    for (int i=0; i<3; i++) {
        if (princesa[i] != -1 && princesa[i] < carta) {
            indice = i;
            carta = princesa[i];
        }
    }
    return indice;
}


// Devuelve el valor de la carta restante
int carta_restante(array<int, 3> princesa) {
    for (int i=0; i<3; i++) {
        if (princesa[i] != -1) {
            return princesa[i];
        }
    }
}

int main() {
    array<int,3> princesa;
    array<int,2> principe;
    vector<int> cartas_jugadas;
    int puntaje_princesa, puntaje_principe;
    int pg, pb, cr;  // puede_ganar, perder_bien, carta_restante
    while(scanf("%d %d %d %d %d", &princesa[0], &princesa[1], &princesa[2], &principe[0], &principe[1]),
          princesa[0] != 0) {
        puntaje_princesa = 0;
        puntaje_principe = 0;
        cartas_jugadas.clear();
        sort(ALL(princesa));
        sort(ALL(principe));
        for (int ronda=0; ronda<2; ronda++) {
            cartas_jugadas.push_back(principe[ronda]);
            pg = puede_ganar(princesa, principe[ronda]);
            if (pg == -1) {
                puntaje_principe++;
                pb = perder_bien(princesa);
                cartas_jugadas.push_back(princesa[pb]);
                princesa[pb] = -1;
            } else {
                puntaje_princesa++;
                cartas_jugadas.push_back(princesa[pg]);
                princesa[pg] = -1;
            }
        }
        if (puntaje_princesa == 2) {
            printf("-1\n");
        }
        else if (puntaje_principe == 2) {
            printf("1\n");
        } else {
            cr = carta_restante(princesa);
            cr++;
            while(find(cartas_jugadas.begin(), cartas_jugadas.end(), cr) != cartas_jugadas.end()) {
                cr++;
            }
            if (cr == 53) {
                printf("-1\n");
            } else {
                printf("%d\n", cr);
            }
        }
    }
    return 0;
}
