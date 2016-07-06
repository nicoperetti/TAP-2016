#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int TC;  // number of test cases
    int creatures;  // number of creatures
    int max_creature_speed;  // calculate max with this
    int aux_speed;  // aux speed to calculate max
    scanf("%d", &TC);
    for (int i = 1; i<=TC; i++) {
        max_creature_speed = 0;
        scanf("%d", &creatures);
        while(creatures--) {
            scanf("%d", &aux_speed);
            max_creature_speed = max(max_creature_speed, aux_speed);
        }
        printf("Case %d: %d\n", i, max_creature_speed);
    }
}
