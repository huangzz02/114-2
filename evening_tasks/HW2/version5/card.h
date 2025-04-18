#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card {
    private:
        char suit;
        std::string rank;
    public:
        Card();
        Card(char suit, const std::string& rank);

        char get_suit() const;
        std::string get_rank() const;

        static std::vector<Card> generate_suit_deck(char suit);
        static std::vector<Card> generate_full_deck();
};

#endif