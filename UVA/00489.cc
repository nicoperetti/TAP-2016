#define WRONG_TRIES 7
#define WIN 'w'
#define LOSE 'l'
#define CHICKEN 'c'

#include <iostream>
#include <set>

using namespace std;

int main() {
    int round;
    string word, tried_letters;
    set<char> letters_of_word, accepted_letters, not_accepted_letters;
    char finish; // WIN, LOSE or CHICKEN
    while(cin >> round, round != -1) {
        // out 1
        cout << "Round " << round << endl;
        // in
        cin >> word;
        cin >> tried_letters;
        // initialize loop
        letters_of_word.clear();
        accepted_letters.clear();
        not_accepted_letters.clear();
        finish = CHICKEN;
        // behavior of loop
        for (char &letter: word) {
            letters_of_word.insert(letter);
        }
        for (char &letter: tried_letters) {
            if (letters_of_word.find(letter) != letters_of_word.end()) {
                accepted_letters.insert(letter);
            } else {
                not_accepted_letters.insert(letter);
            }
            // check if finished
            if (letters_of_word.size() == accepted_letters.size()) {
                cout << "You win." << endl;
                finish = WIN;
                break;
            } else if (not_accepted_letters.size() >= WRONG_TRIES) {
                cout << "You lose." << endl;
                finish = LOSE;
                break;
            }
        }
        if (finish == CHICKEN) {
            cout << "You chickened out." << endl;
        }
    }
    return 0;
}
