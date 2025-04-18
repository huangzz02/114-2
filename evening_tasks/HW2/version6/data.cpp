#include "data.h"
#include "card.h"
#include <iostream>
#include <vector>

int Data::getPlayerNumber() {
    return player_number;
}

void Data::setPlayerNumber(int player_number) {
    this->player_number = player_number;
}

int Data::getId() {
    return id;
}

void Data::setId(int index) {
    id = index;
}

int Data::getScore() const {
    return score;
}

void Data::setScore(int score) {
    this->score = score;
}

void Data::addScore(int score) {
    this->score += score;
}

std::vector<Card>& Data::getCards() {
    return cards;
}

void Data::setCards(std::vector<Card> cards) {
    this->cards = cards;
}