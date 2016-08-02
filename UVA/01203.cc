#include <cstdio>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

typedef tuple<int,int,int> tiii;

/* tuples are (qnum, period, times), where times is the number of times the query was executed.
   (a0, a1, a2) < ( b0, b1, b2) sii (a1*a2 >num b1*b2) || ((a1*a2 ==num b1*b2) && (a0 >num b0))
*/
class Compare {
public:
    bool operator() (tiii a, tiii b) {
        return ((get<1>(a) * get<2>(a)) > (get<1>(b) * get<2>(b))) ||
               (((get<1>(a) * get<2>(a)) == (get<1>(b) * get<2>(b))) && (get<0>(a) > get<0>(b)));
    }
};

int main() {
    int qnum, period;
    int k;
    tiii query;
    priority_queue<tiii, vector<tiii>, Compare> queries;
    // register
    while(scanf(" Register %d %d", &qnum, &period) != 0) {
        queries.push(tiii(qnum, period, 1));
    }
    scanf("%*s");  // truco INTERESANTE. con * se descarta lo leido.
    scanf("%d", &k);
    while(k--) {
        query = queries.top();
        queries.pop();
        printf("%d\n", get<0>(query));
        get<2>(query)++;
        queries.push(query);
    }
    return 0;
}

