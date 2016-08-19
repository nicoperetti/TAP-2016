#include <cstdio>
#include <algorithm>
#include <stdlib.h>

using namespace std;
int morning[100];
int evening[100];

int main() {
	int n, d, r;
	int excedente;
	int total_horas, j;
	while(scanf("%d %d %d", &n, &d, &r), n != 0) {
		excedente = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &morning[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &evening[i]);
		}

		sort(morning, morning + n);
		sort(evening, evening + n);

		for (int i = 0; i < n; i++) {
			j = (n - 1) - i;
			total_horas = morning[i] + evening[j];
			if (total_horas > d) {
				excedente += total_horas - d;
			}
		}
		printf("%d\n", excedente*r);
	}
	return 0;
}