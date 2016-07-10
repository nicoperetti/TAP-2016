#define ALL(a) a.begin(), a.end()

#include <cstdio>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

int carta_para_el_principe(array<int,3> princesa, array<int,2> principe, int carta_princesa) {
    int carta = carta_princesa + 1;
    while(find(ALL(princesa), carta) != princesa.end() || find(ALL(principe), carta) != principe.end()) {
        carta++;
    }
    return carta;
}

int main() {
    array<int,3> princesa;
    array<int,2> principe;
    array<int,3> princesa_indices = {0,1,2};
    array<int,2> principe_indices = {0,1};
    int puntaje_princesa, puntaje_principe;
    int carta_principe;
    while(scanf("%d %d %d %d %d", &princesa[0], &princesa[1], &princesa[2], &principe[0], &principe[1]),
            princesa[0] != 0) {
        carta_principe = 0;  // calcular max con esto entre todas las posibles rondas.
        do {
            do {
                puntaje_princesa = 0;
                puntaje_principe = 0;
                for (int ronda = 0; ronda < 2; ronda++) {
                    if (princesa[princesa_indices[ronda]] > principe[principe_indices[ronda]]) {
                        puntaje_princesa++;
                    } else {
                        puntaje_principe++;
                    }
                }
                if (puntaje_princesa == 2) {
                    carta_principe = 53;  // 53 para que el max de 53. El print sera -1.
                } else if (puntaje_princesa == 1 && puntaje_principe == 1) {
                    carta_principe = max(carta_principe, carta_para_el_principe(princesa, principe, 
                        princesa[princesa_indices[2]]));
                } else if (puntaje_principe == 2) {
                    carta_principe = max(carta_principe, carta_para_el_principe(princesa, principe, 0));
                }
            } while (next_permutation(ALL(principe_indices)));
        } while(next_permutation(ALL(princesa_indices)));

        if (carta_principe == 53) {
            printf("-1\n");
        } else {
            printf("%d\n", carta_principe);
        }
    }
    return 0;
}
