#include <cstdio>

using namespace std;

int main() {
    int cuotas, cant_depr;
    int mes_actual;
    int mes_depr;
    double adelanto, monto_cuota, valor_auto, valor_deuda;
    double old_porc_depr, new_porc_depr;
    bool found;
    while (scanf("%d %lf %lf %d", &cuotas, &adelanto, &valor_deuda, &cant_depr), cuotas > 0) {
        valor_auto = valor_deuda + adelanto;
        monto_cuota = valor_deuda / cuotas;
        mes_actual = 0;
        found = false;
        while (cant_depr--) {
            scanf("%d %lf", &mes_depr, &new_porc_depr);
            while ((mes_actual <= mes_depr || cant_depr == 0) && !found) {
                if (mes_actual == mes_depr) {
                    old_porc_depr = new_porc_depr;
                }
                if (mes_actual != 0) {
                    valor_deuda -= monto_cuota;
                }
                valor_auto -= valor_auto * old_porc_depr;
                if (valor_auto > valor_deuda) {
                    found = true;
                    if (mes_actual == 1) {
                        printf("1 month\n");
                    } else {
                        printf("%d months\n", mes_actual);
                    }
                }
                mes_actual++;
            }
        }
    }
}

