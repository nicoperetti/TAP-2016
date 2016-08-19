#include <cstdio>

using namespace std;
char field[100];

int main() {
	int TC, count, crops;
	char type;
	int j;

	scanf("%d", &TC);
	for (int i = 0; i < TC; i++) {
		count = 0;
		crops = 0;
		j = 0;

		scanf("%d", &crops);
		for (int i = 0; i < crops; i++) {
			scanf(" %c", &field[i]);
		}

		j = 0;
		while (j < crops) {
			if (field[j] == '#') {
				j++;
			} else if (field[j] == '.') {
				count++;
				j += 3;
			}
		}

		printf("Case %d: %d\n", i+1, count);
	}

	return 0;
}