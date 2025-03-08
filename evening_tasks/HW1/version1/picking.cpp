#include "picking.h"
#include <string>

Picking::Picking(bool suit_random, const std::string& suit_code, bool draw_random, int total, int row)
    : suit_random(suit_random), suit_code(suit_code), draw_random(draw_random), total(total), row(row) {}

void Picking::set_suit(bool suit_random) {
    this->suit_random = suit_random;
}

void Picking::set_suit_code(std::string suit_code) {
    this->suit_code = std::move(suit_code);
}

void Picking::set_draw(bool draw_random) {
    this->draw_random = draw_random;
}

void Picking::set_total(int total) {
    this->total = total;
}

void Picking::set_row(int row) {
    this->row = row;
}

bool Picking::get_suit() {
    return suit_random;
}

const std::string& Picking::get_suit_code() const {
    return suit_code;
}

bool Picking::get_draw() {
    return draw_random;
}

int Picking::get_total() {
    return total;
}

int Picking::get_row() {
    return row;
}