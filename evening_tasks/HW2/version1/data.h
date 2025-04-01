#ifndef DATA_H
#define DATA_H

#include <vector>
#include "card.h"

class Data {
    private:
        int id;
        int score;
        std::vector<Card> cards;

    public:
        Data() : id(0), score(0), cards() {}
        Data(int id, int score, std::vector<Card> cards) : id(id), score(score), cards(cards) {}

        int getId();
        void setId(int index);

        int getScore() const;
        void setScore(int score);
        void addScore(int score);

        std::vector<Card>& getCards();
        void setCards(std::vector<Card> cards);
};


#endif