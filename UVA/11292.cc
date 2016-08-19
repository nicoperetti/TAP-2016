#include <cstdio>
#include <algorithm>

using namespace std;

long heads[20000];
long knights[20000];

int main() {
	int n, m;
	long k, j;
	long gold;

	while(scanf("%d %d", &n, &m), n != 0) {
		k = 0;
		j = 0;
		gold = 0;

		for (int i = 0; i < n; i++) {
			scanf("%ld", &heads[i]);
		}
		for (int i = 0; i < m; i++) {
			scanf("%ld", &knights[i]);
		}

		if (n > m) {
			printf("Loowater is doomed!\n");
		} else {
			sort(heads, heads + n);
			sort(knights, knights + m);

			for (k = 0; k < m; k++) {
				if (j == n) {
					break;
				}
				if (knights[k] >= heads[j]) {
					gold += knights[k];
					j++;
				}
			}

			if (j == n) {
				printf("%ld\n", gold);
			} else {
				printf("Loowater is doomed!\n");
			}
		}
	}
}