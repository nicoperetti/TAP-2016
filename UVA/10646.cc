#define toDigit(c) c-'0'

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int value(string card) {
    if (isdigit(card[0])) {
        return toDigit(card[0]);
    } else {
        return 10;
    }
}

int main() {
    int TC;
    int i;  // iterator
    int index_pile;
    int Y, X;
    string card;
    vector<string> v, h;
    cin >> TC;
    for (int j=0; j<TC; j++) {
        cout << "Case " << j+1 << ": ";
        Y = 0;
        index_pile = 51;
        v.clear();
        for (i=0; i <= index_pile; i++) {
            cin >> card;
            v.push_back(card);
        }

        index_pile -= 25;

        for(i=0; i < 3; i++) {
            X = value(v[index_pile]);
            Y += X;
            index_pile -= (11 - X);
        }

        Y--;

        if (Y <= index_pile) {
           cout << v[Y] << endl;
        } else {
           cout << v[(52-25)+Y-(index_pile+1)] << endl;
        }

    }
}
