#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <math.h>

using namespace std;

int main() {
    int N, totalOfTree;
    float percentage;
    string species, line;
    map<string, int> hardwood;
    getline(cin, line);
    N = stoi(line);
    getline(cin, species);
    for (int i = 0; i < N; i++) {
        totalOfTree = 0;
        hardwood.clear();
        while(getline(cin, species), !species.empty()) {
            totalOfTree += 1;
            if (hardwood.find(species) == hardwood.end()) {
                hardwood.insert(pair<string,int>(species, 1));
            } else {
                hardwood[species] += 1;
            }
            if (cin.eof()) {
                break;
            }
        }
        for (const auto &p : hardwood) {
            percentage = (float) 100 * p.second / totalOfTree;
            cout << p.first << " ";
            cout << fixed << setprecision(4) << percentage << '\n';
        }
        if (i < N-1) {
            cout << "\n";
        }
    }
    return 0;
}
