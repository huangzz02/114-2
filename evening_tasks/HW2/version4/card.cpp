#include "card.h"
#include <vector>

Card::Card() : suit('S'), rank("A") {} // Default constructor

Card::Card(char s, const std::string& r) : suit(s), rank(r) {}

char Card::get_suit() const{
    return suit;
}

std::string Card::get_rank() const {
    return rank;
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