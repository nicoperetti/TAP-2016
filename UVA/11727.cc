#define ALL(v) v.begin(), v.end()
#include <algorithm>
#include <cstdio>
#include <array>

using namespace std;

int main() {
    array<int, 3> empl;
    int TC;
    scanf("%d", &TC);
    for (int i=1; i<=TC; i++) {
        scanf("%d %d %d", &empl[0], &empl[1], &empl[2]);
        sort(ALL(empl));
        printf("Case %d: %d\n", i, empl[1]);
    }
}
