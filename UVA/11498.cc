#include <cstdio>
#include <string>

using namespace std;

/* k: num of test cases
 * dx: division x
 * dy: division y
 * hx: house x
 * hy: house y
*/
int main() {
    int k, dx, dy, hx, hy;
    string s;
    while(scanf("%d", &k), k != 0) {
        scanf("%d %d", &dx, &dy);
        while (k--) {
            scanf("%d %d", &hx, &hy);
            if (hy == dy || hx == dx) {
                printf("divisa\n");
            } else {
                if (hy > dy) {
                    s += "N";
                } else {
                    s += "S";
                }
                if (hx > dx) {
                    s += "E";
                } else {
                    s += "O";
                }
                printf("%s\n", s.c_str());
                s.clear();
            }
        }
    }
}
