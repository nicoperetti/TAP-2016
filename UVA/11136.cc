#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

#define ALL(v) v.begin(), v.end()

int main() {
    int days;
    int num_bills;
    int bill;
    multiset<int>::iterator max_bill, min_bill;
    unsigned long long cost;
    multiset<int> bills;
    while(scanf("%d", &days), days != 0) {
        cost = 0;
        bills.clear();
        while(days--) {
            scanf("%d", &num_bills);
            while(num_bills--) {
                scanf("%d", &bill);
                bills.insert(bill);
            }
            // end of day
            max_bill = bills.end();
            max_bill--;
            min_bill = bills.begin();
            cost += *max_bill - *min_bill;
            bills.erase(max_bill);
            bills.erase(min_bill);
        }
        printf("%llu\n", cost);
    }
    return 0;
}

