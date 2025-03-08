#include "card.h"
#include <vector>

Card::Card(char s, const std::string& r) : suit(s), rank(r) {}

char Card::get_suit() const{
    return suit;
}

std::string Card::get_rank() const {
    return rank;
}

std::vector<std::string> Card::to_appearance() const{
    std::vector<std::string> appearance(10);
    std::string line1, line2, line3, line4;
    if (suit == 'S') {
        line1 = "|    +++    |";
        line2 = "|   +++++   |";
        line3 = "|  +++++++  |";
        line4 = "|    +++    |";
    } else if (suit == 'H') {
        line1 = "|   +   +   |";
        line2 = "|  +++++++  |";
        line3 = "|   +++++   |";
        line4 = "|     +     |";
    } else if (suit == 'D') {
        line1 = "|    +++    |";
        line2 = "|   +++++   |";
        line3 = "|   +++++   |";
        line4 = "|    +++    |";
    } else if (suit == 'C') {
        line1 = "|    +++    |";
        line2 = "|  +  +  +  |";
        line3 = "|  +++++++  |";
        line4 = "|    +++    |";
    }

    appearance[0] = " ----------- ";
    appearance[1] = "|" + rank + "          |";
    appearance[2] = "|" + std::string(1, suit) + "          |";
    appearance[3] = line1;
    appearance[4] = line2;
    appearance[5] = line3;
    appearance[6] = line4;
    appearance[7] = "|          " + std::string(1, suit) + "|";
    appearance[8] = "|          " + rank + "|";
    appearance[9] = " ----------- ";

    return appearance;
}

std::vector<Card> Card::generate_suit_deck(char suit) {
    std::vector<Card> suit_deck;
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
   
    for (const auto& r : ranks) {
        suit_deck.emplace_back(Card(suit, r));
    }
    return suit_deck;
}

std::vector<Card> Card::generate_full_deck() {
    std::vector<Card> full_deck;
    std::vector<char> suits = {'S', 'H', 'D', 'C'};

    for (const auto& s : suits) {
        auto suit_deck = generate_suit_deck(s);
        full_deck.insert(full_deck.end(), suit_deck.begin(), suit_deck.end());
    }
    return full_deck;
}