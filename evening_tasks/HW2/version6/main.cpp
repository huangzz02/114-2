#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "data.h"
#include "card.h"
#include "game_logic.h"
using namespace std;

int main() {
    // Show the rules of the game
    cout << "The objective of the game is to elimanate all other players." << endl;
    cout << "If the value of any card in the player's hand plus the card pile is greater than 99," << endl;
    cout << "and there is no suitable functional card, will be eliminated." << endl << endl;

    cout << "Here's how special cases are calculated:" << endl;
    cout << "A of Spade: -> 0" << endl;
    cout << "4 when 4 players: Turn around" << endl;
    cout << "5: Specify" << endl;
    cout << "10: +10 or -10" << endl;
    cout << "J: Pass" << endl;
    cout << "Q: +20 or -20" << endl;
    cout << "K: -> 99" << endl << endl;

    cout << "----------------------------------------------------------" << endl << endl;

    // Presetation of the game
    int players_amount, round, place;
    cout << "Enter the number of players (Enter 2~5): ";
    cin >> players_amount;
    cout << "Enter the number of rounds: ";
    cin >> round;
    cout << endl;

    vector<Data> data(players_amount);
    for (int i = 0; i < players_amount; i++) {
        data[i].setPlayerNumber(i + 1);
        data[i].setScore(0);
    }
    
    for (int rd = 1; rd <= round; rd++) {
        cout << "----------------------------------------------------------" << endl << endl;

        // Step 0: Get the place of the game, and clear the cards from the previous round
        cout << "Round " << rd << " (" << round - rd <<" rounds left):" << endl;
        cout << "Enter the place you want of the game (Enter 1~" << players_amount << "): ";
        cin >> place;
        cout << endl;

        for (int i = 0; i < players_amount; i++) {
            data[i].getCards().clear();
        }

        // Step 1: Create a deck of cards, set the order(id) by choosing the card randomly
        vector<Card> deck = Card::generate_full_deck();
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

        vector<Card> first_n_cards(deck.begin(), deck.begin() + players_amount); // Get the first n cards for each player
        for (int i = 0; i < players_amount; i++) {
            cout << "Player " << i + 1 << " drew: ";
            cout << first_n_cards[i].get_rank() << " of " << first_n_cards[i].get_suit();
            if (i + 1 == place) cout << " (You)";
            cout << endl;
        }

        int decide_order[players_amount];
        for (int i = 0; i < players_amount; i++) {
            int suit = get_card_suit(first_n_cards[i]);
            int rank = get_card_value(first_n_cards[i]);
            decide_order[i] = (rank - 1) * 4 + suit;
        }

        vector<pair<int, int>> player_order; // Store player number and id
        for (int i = 1; i <= players_amount; i++) {
            player_order.emplace_back(i, decide_order[i - 1]);
        }

        sort(player_order.begin(), player_order.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });

        cout << "The order of the game is: ";
        for (size_t i = 0; i < player_order.size(); i++) {
            cout << "P" << player_order[i].first;
            if (player_order[i].first == place) cout << "(You)";
            if (i != player_order.size() - 1) cout << " -> ";

            data[player_order[i].first - 1].setId(i + 1);
        }
        cout << endl << endl;

        // Step 2: Reshuffle the deck and distribute 5 cards to each players
        cout << "Reshuffling the deck..." << endl << endl;
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

        for (int i = 0; i < 5; i++) { // Get 5 cards for each player
            for (int j = 0; j < players_amount; j++) {
                data[j].getCards().push_back(deck.front());
                deck.erase(deck.begin()); // Vector cannot use pop_front
            }
        }

        // Step 3: play until the game ends
        int direction = 1; // 1 for clockwise, -1 for counterclockwise
        int remaining_players = players_amount;
        int pile = 0;
        int promoted_score = players_amount, eliminated_score = 1;
        int current_player, current_player_index = 0;

        while(remaining_players > 1) {
            cout << "Deck remaining: " << deck.size() << " card";
            if (deck.size() > 1) cout << "s";
            cout << endl;
            cout << "Current pile: " << pile << endl;
            current_player = player_order[current_player_index].first;
            cout << "Current player: Player " << current_player;
            if (current_player == place) cout << " (You)";
            cout << endl;
            
            int player_index = current_player - 1;
            Card chosen_card;

            vector<int> legal_indices = get_legal_cards(data[player_index].getCards(), pile, players_amount);
            bool player_removed = false;

            if (legal_indices.empty()) {
                cout << "No legal cards to play." << endl;
                cout << "Player " << current_player;
                if (current_player == place) cout << " (You)";
                cout << " is eliminated!" << endl;

                cout << "Score: " << eliminated_score << endl;
                data[player_index].addScore(eliminated_score);
                eliminated_score++;
                player_removed = true;
            } else {
                if (player_index + 1 == place) { // Player's turn
                    cout << "[Your deck : ";
                    for (size_t j = 0; j < data[player_index].getCards().size(); j++) {
                        const Card& card = data[player_index].getCards()[j];
                        cout << card.get_rank() << " of " << card.get_suit();
                        if (find(legal_indices.begin(), legal_indices.end(), j) != legal_indices.end()) {
                            cout << " (legal)";
                        }
                        if (j < data[player_index].getCards().size() - 1) cout << ", ";
                    }
                    cout << "]";

                    cout << " (Choose from legal cards: ";
                    for (size_t k = 0; k < legal_indices.size(); k++) {
                        cout << legal_indices[k] + 1;
                        if (k < legal_indices.size() - 1) cout << ", ";
                    }
                    cout << "): ";

                    int choice;
                    cin >> choice;

                    int card_index = choice - 1;
                    chosen_card = data[player_index].getCards()[card_index];

                    cout << "You chose: " << chosen_card.get_rank() << " of " << chosen_card.get_suit() << endl;
                    data[player_index].getCards().erase(data[player_index].getCards().begin() + card_index);
                } else { //TODO (temporary AI logic): AI chooses the first legal card
                    /* For debugging: Show the cards of current player
                    cout << "\033[31m";
                    cout << "Player " << current_player << "'s cards: ";
                    for (size_t j = 0; j < data[player_index].getCards().size(); j++) {
                        const Card& card = data[player_index].getCards()[j];
                        cout << card.get_rank() << " of " << card.get_suit();
                        if (j < data[player_index].getCards().size() - 1) cout << ", ";
                    }
                    cout << "\033[0m" << endl;
                    */

                    int card_index = legal_indices[0];
                    chosen_card = data[player_index].getCards()[card_index];

                    cout << "Player " << current_player << " chose: " << chosen_card.get_rank() << " of " << chosen_card.get_suit() << endl;
                    data[player_index].getCards().erase(data[player_index].getCards().begin() + card_index);
                }

                // apply_card_effect(const Card& card, int& pile, bool is_human, vector<pair<int, int>>& player_order, int current_player_index, int players_amount, int& direction)
                int specified_player = apply_card_effect(chosen_card, pile, player_index + 1 == place, player_order, current_player_index, players_amount, direction);

                // Check if the player has cards left
                if (data[player_index].getCards().empty()) {
                    cout << "No cards left to play." << endl;
                    cout << "Player " << current_player;
                    if (current_player == place) cout << " (You)";
                    cout << " is promoted!" << endl;

                    cout << "Score: " << promoted_score << endl;
                    data[player_index].addScore(promoted_score);
                    promoted_score--;
                    player_removed = true;
                }

                // Handles logic for players to remove or move to the next player
                if (player_removed) {
                    player_order.erase(player_order.begin() + current_player_index);
                    remaining_players--;
                    if (remaining_players > 0) {
                        if (specified_player != -1) {
                            // Locate the location of the assigned player in the updated player_order
                            for (size_t i = 0; i < player_order.size(); i++) {
                                if (player_order[i].first == specified_player) {
                                    current_player_index = i;
                                    break;
                                }
                            }
                        } else {
                            // If no player is specified, move in the normal order
                            current_player_index = (current_player_index + direction + remaining_players) % remaining_players;
                        }
                    }
                } else {
                    if (specified_player != -1) {
                        // Locate the location of the assigned player in the updated player_order
                        for (size_t i = 0; i < player_order.size(); i++) {
                            if (player_order[i].first == specified_player) {
                                current_player_index = i;
                                break;
                            }
                        }
                    } else {
                        // If no player is specified, move in the normal order
                        current_player_index = (current_player_index + direction + remaining_players) % remaining_players;
                    }
                }
            }

            if (!player_removed && !deck.empty()) {
                Card new_card = deck.front();
                deck.erase(deck.begin());
                data[player_index].getCards().push_back(new_card);
                cout << "Player " << current_player;
                if (current_player == place) cout << " (You)";
                cout << " drew a card." << endl;

                // For debugging: Show the drawn card
                //cout << "\033[31mDrew: " << new_card.get_rank() << " of " << new_card.get_suit() << "\033[0m" << endl;
            } else if (!player_removed) {
                cout << "Deck is empty now. No more cards to draw." << endl;
            }
            cout << endl;

            if (player_removed) {
                player_order.erase(player_order.begin() + current_player_index);
                remaining_players--;
                if (remaining_players > 0) {
                    current_player_index = (current_player_index + direction + remaining_players) % remaining_players;
                }
            } else { // Move to next player, according to direction
                current_player_index = (current_player_index + direction + remaining_players) % remaining_players;
            }
        }

        if (remaining_players == 1) {
            int last_player_index = player_order[0].first - 1;
            cout << "Player " << player_order[0].first;
            if (player_order[0].first == place) cout << " (You)";
            cout << " is the last one." << endl;

            cout << "Score: " << promoted_score << endl;
            data[last_player_index].addScore(promoted_score);

            cout << endl;
        }

        cout << "Round " << rd << " ended." << endl << endl;
        cout << "Current scores:" << endl;
        for (int i = 0; i < players_amount; i++) {
            cout << "Player " << i + 1 << ": " << data[i].getScore();
            if (i + 1 == place) cout << " (You)";
            cout << endl;
        }

        cout << endl;
    }
    cout << "----------------------------------------------------------" << endl << endl;
    cout << "Game ended." << endl << endl;
    
    sort(data.begin(), data.end(), [](const Data& a, const Data& b) {
        return a.getScore() > b.getScore();
    });

    cout << "Final rank:" << endl;
    int rank = 1;
    int previous_score = -1;
    int tie_count = 0;

    for (size_t i = 0; i < data.size(); i++) {
        if (i > 0 && data[i].getScore() < previous_score) { // Different score, update ranking
            rank += tie_count;
            tie_count = 1;
        } else if (i > 0 && data[i].getScore() == previous_score) { // Same score
            tie_count++;
        } else { // 1st player (initialization)
            tie_count = 1;
        }
        previous_score = data[i].getScore();  // Update previous score

        cout << "Rank " << rank << ": Player " << data[i].getPlayerNumber() << " (" << data[i].getScore() << ")";
        if (data[i].getPlayerNumber() == place) cout << " (You)";
        cout << endl;
    }
    cout << endl;

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
/*
    1. Fixing the problem below: // TODO haven't been fixed yet
        Assume there are three players: P1, P2, and P3, and the game proceeds in the order P1 -> P2 -> P3, with direction = 1 (clockwise):

        Currently, it's P1's turn. P1 plays a "5" card and designates P3 as the next player.
        After playing the "5" card, P1 has no cards left, so P1 wins and leaves the game.
        Once P1 leaves, the player_order changes from [P1, P2, P3] to [P2, P3].
        At this point, current_player_index should point to P3, but since player_order has changed, failing to adjust the index correctly may result in it pointing to the wrong player (e.g., P2).
*/