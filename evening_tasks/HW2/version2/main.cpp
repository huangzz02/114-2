#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "data.h"
#include "card.h"
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

void apply_card_effect(const Card& card, int& pile, bool is_human, vector<pair<int, int>>& player_order, int current_player_index, int players_amount) {
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
            reverse(player_order.begin(), player_order.end());
        } else {
            pile += 4;
            cout << "Pile +4, now " << pile << endl;
        }
    }
    else if (rank == "5") { // Temporary code, it has some problems
        int value = rank[0] - '0';
        pile += value;
        cout << "Pile +" << value << ", now " << pile << endl;
        /*
        int next_player;
        if (is_human) {
            cout << "Specify the next player (choose from ";
            for (size_t j = 0; j < player_order.size(); j++) {
                if (j != current_player_index) {
                    cout << "P" << player_order[j].first;
                    if (j < player_order.size() - 1 && j + 1 != current_player_index) cout << ", ";
                }
            }
            cout << "): ";

            cin >> next_player;
        } else { // Choose the next player randomly
            cout << "Specifying..." << endl;

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle(player_order.begin(), player_order.end(), std::default_random_engine(seed));
            next_player = player_order[1].first;
        }

        // Find the index of the specified player in the player_order vector
        auto it = find_if(player_order.begin(), player_order.end(), [next_player](const pair<int, int>& p) {
            return p.first == next_player;
        });
        int next_index = distance(player_order.begin(), it);

        // Rotate the player_order vector to set the next player
        rotate(player_order.begin(), player_order.begin() + next_index, player_order.end());

        cout << "Next player is Player " << next_player << endl;
        */
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
            //TODO temporary AI logic: if (pile + 10 <= 99), choose +10, else -10
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
            //TODO temporary AI logic: if (pile + 20 <= 99), choose +20, else -20
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
        int remaining_players = players_amount;
        int pile = 0;
        int promoted_score = players_amount, eliminated_score = 1;
        while(remaining_players > 1) {
            for (int i = 0; i < remaining_players; i++) {
                cout << "Deck remaining: " << deck.size() << " card";
                if (deck.size() > 1) cout << "s";
                cout << endl;
                cout << "Current pile: " << pile << endl;
                cout << "Current player: Player " << player_order[i].first;
                if (player_order[i].first == place) cout << " (You)";
                cout << endl;
                
                int player_index = player_order[i].first - 1;
                Card chosen_card;

                vector<int> legal_indices = get_legal_cards(data[player_index].getCards(), pile, players_amount);
                if (legal_indices.empty()) {
                    cout << "No legal cards to play." << endl;
                    cout << "Player " << player_order[i].first << " is eliminated!" << endl;

                    cout << "Score: " << eliminated_score << endl;
                    data[player_index].addScore(eliminated_score);
                    eliminated_score++;

                    remaining_players--;
                    player_order.erase(player_order.begin() + i);
                    i--; // Adjust index after removal

                    cout << endl;
                    continue;
                }

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

                    cout << "] (Choose from legal cards: ";
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
                    int card_index = legal_indices[0];
                    chosen_card = data[player_index].getCards()[card_index];

                    cout << "Player " << player_order[i].first << " chose: " << chosen_card.get_rank() << " of " << chosen_card.get_suit() << endl;
                    data[player_index].getCards().erase(data[player_index].getCards().begin() + card_index);
                }

                // apply_card_effect(const Card& card, int& pile, bool is_human, vector<pair<int, int>>& player_order, int current_player_index)
                apply_card_effect(chosen_card, pile, player_index + 1 == place, player_order, i, players_amount);

                // Check if the player has cards left
                if (data[player_index].getCards().empty()) {
                    cout << "No cards left to play." << endl;
                    cout << "Player " << player_order[i].first << " is promoted!" << endl;

                    cout << "Score: " << promoted_score << endl;
                    data[player_index].addScore(promoted_score);
                    promoted_score--;

                    remaining_players--;
                    player_order.erase(player_order.begin() + i);
                    i--; // Adjust index after removal

                    cout << endl;
                    continue;
                }

                if (!deck.empty()) {
                    Card new_card = deck.front();
                    deck.erase(deck.begin());
                    data[player_index].getCards().push_back(new_card);
                    cout << "Player " << player_order[i].first;
                    if (player_order[i].first == place) cout << " (You)";
                    cout << " drew a card." << endl;
                } else {
                    cout << "Deck is empty now. No more cards to draw." << endl;
                }

                cout << endl;
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
    1. Fix the issue with the final ranking output order.
    2. Fix the issue where the second-round hand cards were not cleared.
    3. Fix the issue with the index of the card selected by the user.
    4. Fix the issue with the prompt displaying the available card codes when the user selects a card.
*/