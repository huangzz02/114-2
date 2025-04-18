#ifndef DATA_H
#define DATA_H

#include <vector>
#include "card.h"

class Data {
    private:
        int player_number;
        int id;
        int score;
        std::vector<Card> cards;

    public:
        Data() : player_number(0), id(0), score(0), cards() {}
        Data(int num, int id, int score, std::vector<Card> cards) : player_number(num), id(id), score(score), cards(cards) {}

        int getPlayerNumber();
        void setPlayerNumber(int player_number);

        int getId();
        void setId(int index);

        int getScore() const;
        void setScore(int score);
        void addScore(int score);

        std::vector<Card>& getCards();
        void setCards(std::vector<Card> cards);
};


#endif