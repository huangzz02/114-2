#include "skin.h"
#include <iostream>

Skin::Skin(std::string char_name, std::string sk_name, int p) {
    character_name = char_name;
    skin_name = sk_name;
    price = p;
    sold = false;
}

void Skin::set_price(int new_price) {
    price = new_price;
}

std::string Skin::get_character_name() {
    return character_name;
}

std::string Skin::get_skin_name() {
    return skin_name;
}

int Skin::get_price() {
    return price;
}

bool Skin::is_sold() {
    return sold;
}

void Skin::set_sold(bool status) {
    sold = status;
}