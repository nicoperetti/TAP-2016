#include <cstdio>
#include <algorithm>

using namespace std;

/* 
 * part: Number of participants
 * budget: total budget
 * hotels: Number of hotels
 * weeks: number of different weeks
 */
int main() {
    int parts, budget, hotels, weeks;
    int hotel_price;
    int available_beds;  // calculate max with this
    int min_price;  // calculate min with this
    int aux_beds;  // used to calculate max.
    bool found_place;
    while (scanf("%d %d %d %d", &parts, &budget, &hotels, &weeks) != EOF) {
        found_place = false;
        min_price = 200 * 10000;  // initialize with MAX posible price
        while(hotels--) {
            scanf("%d", &hotel_price);
            // max available beds of hotel
            available_beds = 0;
            for (int i=0; i<weeks; i++) {
                scanf("%d", &aux_beds);
                available_beds = max(available_beds, aux_beds);
            }
            if (available_beds >= parts) {
                found_place = true;
                min_price = min(min_price, parts * hotel_price);
            }
        }
        if (found_place && min_price <= budget) {
            printf("%d\n", min_price);
        } else {
            printf("stay home\n");
        }
    }
}
