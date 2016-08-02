#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int main() {
	int n, m;
	int aux;
	int k, v;
	map<int, vector<int> > adj_list;

	while (scanf("%d %d", &n, &m) != EOF) {
		adj_list.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d", &aux);
			if (adj_list.find(aux) != adj_list.end()) {
				adj_list[aux].push_back(i+1);
			} else {
				adj_list.insert(pair<int, vector<int> >(aux, vector<int>(1, i+1)));
			}
		}
		while (m--) {
			scanf("%d %d", &k, &v);
			if (adj_list.find(v) != adj_list.end()) {
				if (adj_list[v].size() < k) {
					printf("0\n");
				} else {
					printf("%d\n", adj_list[v][k-1]);
				}
			} else {
				printf("0\n");
			}
		}
	}

	return 0;
}