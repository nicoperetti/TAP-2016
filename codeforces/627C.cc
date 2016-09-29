#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

typedef pair <int, int> ii;
ii stations[200010];
int d, tank, n_stations;

int min_range(int dist, int index) {
    int rango = dist + tank;
    int min_index = -1;
    int min_price = INT_MAX;
    while (stations[index].first <= rango && index < n_stations + 1) {
        if (min_price > stations[index].second) {
            min_index = index;
            min_price = stations[index].second;
        }
        index++;
    } 
    return min_index;
}

long long min_cost() {
    int dist = 0;
    int index = 0;
    int fuel = tank;
    long long gasto = 0;
    int recorrido = 0;
    bool llegue = false;
    while (!llegue) {
        int new_index = min_range(dist, index+1);
        if (new_index == -1) {
            if (index == n_stations && dist+tank >= d) {
                recorrido = d - dist;
                gasto += (recorrido - fuel) * stations[index].second;
                return gasto;
            } 
            return -1;
        }
        int new_dist = stations[new_index].first;
        recorrido = new_dist - dist;
        if (stations[index].second < stations[new_index].second) {
            if (dist + tank >= d) {
                recorrido = d - dist;
                gasto += (recorrido - fuel) * stations[index].second;
                fuel = recorrido;
                llegue = true;
            }
            gasto += (tank - fuel) * stations[index].second;
            fuel = tank;
        } else {
            gasto += (recorrido - fuel) * stations[index].second;
            fuel = recorrido;
        }
        fuel -= recorrido;
        dist = new_dist;
        index = new_index;
    }
    return gasto;
}


int main() {
    scanf("%d %d %d", &d, &tank, &n_stations);
    stations[0] = ii(0,0);
    for (int i=1; i <= n_stations; i++){
        int st_dist, st_price;
        scanf("%d %d", &st_dist, &st_price);
        stations[i] = ii(st_dist, st_price);
    }
    sort(stations, stations + n_stations + 1);
    cout << min_cost() << endl;
    return 0;
}

