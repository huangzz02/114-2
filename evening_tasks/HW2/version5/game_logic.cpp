#include "game_logic.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int get_card_suit(const Card& card) {
    if (card.get_suit() == 'S') return 4;
    else if (card.get_suit() == 'H') return 3;
    else if (card.get_suit() == 'D') return 2;
    else if (card.get_suit() == 'C') return 1;
    return 0; // Default case, should not happen
}

int get_card_value(const Card& card) {
    if (card.get_rank() == "A") return 1;
    else if (card.get_rank() == "T") return 10;
    else if (card.get_rank() == "J") return 11;
    else if (card.get_rank() == "Q") return 12;
    else if (card.get_rank() == "K") return 13;
    else return card.get_rank()[0] - '0';
}

vector<int> get_legal_cards(const vector<Card>& hand, int pile, int players_amount) {
    vector<int> legal_indices;
    for (size_t i = 0; i < hand.size(); i++) {
        const Card& card = hand[i];
        char suit = card.get_suit();
        string rank = card.get_rank();
        
        // Always legal (A of Spades, 4 in 4 players, 5, T, J, Q, K)
        if ((rank == "A" && suit == 'S') || 
            (rank == "4" && players_amount == 4) || 
             rank == "5" || rank == "T" || rank == "J" || rank == "Q" || rank == "K") {
            legal_indices.push_back(i);
        }
        // Check other conditions
        else if (pile + (rank[0] - '0') <= 99) {
            legal_indices.push_back(i);
        }
    }
    return legal_indices;
}

void apply_card_effect(const Card& card, int& pile, bool is_human, vector<pair<int, int>>& player_order, 
                      int& current_player_index, int players_amount, int& direction) {
    string rank = card.get_rank();
    if (rank == "A") {
        if (card.get_suit() == 'S') { // A of Spades
            pile = 0;
            cout << "Pile set to 0." << endl;
        } else {
            pile += 1;
            cout << "Pile +1, now " << pile << endl;
        }
    }
    else if (rank == "4") {
        if (players_amount == 4) {
            cout << "Turn order reversed." << endl;
            direction = -direction;
        } else {
            pile += 4;
            cout << "Pile +4, now " << pile << endl;
        }
    }
    else if (rank == "5") {
        vector<int> possible_players;
        int current_player_number = player_order[current_player_index].first;
        for (const auto& p : player_order) {
            if (p.first != current_player_number) {
                possible_players.push_back(p.first);
            }
        }

        int chosen_player;
        if (is_human) {
            cout << "Specify the next player (choose from ";
            for (size_t j = 0; j < possible_players.size(); j++) {
                cout << "P" << possible_players[j];
                if (j < possible_players.size() - 1) cout << ", ";
            }
            cout << "): ";
            cin >> chosen_player;
        } else {
            cout << "Specifying..." << endl;
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine engine(seed);
            uniform_int_distribution<int> dist(0, possible_players.size() - 1);
            int idx = dist(engine);
            chosen_player = possible_players[idx];
        }

        cout << "Next player is Player " << chosen_player << endl;

        size_t chosen_index = 0;
        for (size_t i = 0; i < player_order.size(); i++) {
            if (player_order[i].first == chosen_player) {
                chosen_index = i;
                break;
            }
        }

        if (direction == 1) {
            current_player_index = (chosen_index - 1 + player_order.size()) % player_order.size();
        } else {
            current_player_index = (chosen_index + 1) % player_order.size();
        }
    }
    else if (rank == "T") {
        int choice;
        if (is_human) {
            if (pile + 10 <= 99 && pile - 10 >= 0) {
                cout << "Choose 1 for +10, 2 for -10: ";
                cin >> choice;
            } else if (pile + 10 <= 99) {
                cout << "Only +10 is available." << endl;
                choice = 1;
            } else if (pile - 10 >= 0) {
                cout << "Only -10 is available." << endl;
                choice = 2;
            }
        } else {
            choice = (pile + 10 <= 99) ? 1 : 2;
        }

        if (choice == 1) {
            pile += 10;
            cout << "Pile +10, now " << pile << endl;
        } else {
            pile -= 10;
            cout << "Pile -10, now " << pile << endl;
        }
    }
    else if (rank == "J") {
        cout << "Pass, pile remains " << pile << endl;
    }
    else if (rank == "Q") {
        int choice;
        if (is_human) {
            if (pile + 20 <= 99 && pile - 20 >= 0) {
                cout << "Choose 1 for +20, 2 for -20: ";
                cin >> choice;
            } else if (pile + 20 <= 99) {
                cout << "Only +20 is available." << endl;
                choice = 1;
            } else if (pile - 20 >= 0) {
                cout << "Only -20 is available." << endl;
                choice = 2;
            }
        } else {
            choice = (pile + 20 <= 99) ? 1 : 2;
        }

        if (choice == 1) {
            pile += 20;
            cout << "Pile +20, now " << pile << endl;
        } else {
            pile -= 20;
            cout << "Pile -20, now " << pile << endl;
        }
    }
    else if (rank == "K") {
        pile = 99;
        cout << "Pile set to 99." << endl;
    }
    else if (rank >= "2" && rank <= "9") {
        int value = rank[0] - '0';
        pile += value;
        cout << "Pile +" << value << ", now " << pile << endl;
    }
}