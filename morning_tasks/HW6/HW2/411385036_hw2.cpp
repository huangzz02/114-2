#include "stack.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
using namespace std;

int main() {
    cout << "Enter the number of cards (1-52): ";
    int N;
    cin >> N;

    string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
    string allCards[52];
    int index = 0;
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            allCards[index++] = suit + "-" + rank;
        }
    }

    random_device rd;
    default_random_engine engine(rd());
    shuffle(allCards, allCards + 52, engine);

    string initialCards[52];
    for (int i = 0; i < N; i++) {
        initialCards[i] = allCards[i];
    }

    Stack stack(52);
    stack.initialize(initialCards, N);
    stack.display();
    cout << endl;

    while (true) {
        cout << "1. Deal one card\n2. Shuffle the cards\n3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            break;
        }

        switch (choice) {
            case 1: {
                string card = stack.pop();
                if (!card.empty()) {
                    cout << "Dealing: " << card << endl;
                } else {
                    cout << "No more cards to deal!" << endl;
                }
                break;
            }
            case 2:
                stack.shuffle();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        cout << endl;
    }

    return 0;
}