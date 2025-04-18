#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <string>
#include "card.h"
#include "data.h"

int get_card_suit(const Card& card);
int get_card_value(const Card& card);
std::vector<int> get_legal_cards(const std::vector<Card>& hand, int pile, int players_amount);
void apply_card_effect(const Card& card, int& pile, bool is_human, std::vector<std::pair<int, int>>& player_order, 
                      int& current_player_index, int players_amount, int& direction);

#endif