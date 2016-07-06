#include <cstdio>
#include <string>

using namespace std;

/*
 * h: height
 * u: up
 * d: down
 * f: fatigue
*/
int main() {
    int h, u, d, f;
    int day;  // current day
    double position, u_day;  // current position, and how much will up this day.
    bool finish;  // success or faiulre
    while (scanf("%d %d %d %d", &h, &u, &d, &f), h > 0) {
        finish = false;
        day = 1;
        position = 0;
        while (!finish) {
            u_day = u * (1 - (day-1) * f / 100.0);
            if (u_day > 0)
                position += u_day;
            if (position > h) {
                printf("success on day %d\n", day);
                finish = true;
            } else {
                position -= d;
                if (position < 0) {
                    finish = true;
                    printf("failure on day %d\n", day);
                }
            }
            day++;
        }
    }
}
