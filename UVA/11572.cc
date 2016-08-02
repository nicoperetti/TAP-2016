#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	int TC;
	int n;
	int elem;
	int index, max_total, max_aux;
	map<int, int> snowflakes;

	scanf("%d", &TC);
	while (TC--) {
		snowflakes.clear();
		max_total = 0;
		max_aux = 0;
		index = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &elem);
			if (snowflakes.find(elem) != snowflakes.end()) {
				if (snowflakes[elem] < index) {
					snowflakes[elem] = i;
					max_aux++;
				} else {
					max_total = max(max_total, max_aux);
					index = snowflakes[elem] + 1;
					max_aux = i - snowflakes[elem];
					snowflakes[elem] = i;
				}
			} else {
				snowflakes.insert(pair<int, int> (elem, i));
				max_aux++;
			}
		}
		max_total = max(max_total, max_aux);
		printf("%d\n", max_total);
	}
	return 0;
}