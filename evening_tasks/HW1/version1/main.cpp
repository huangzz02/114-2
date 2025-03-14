#include "picking.h"
#include "card.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <vector>
#include <algorithm> // Shuffle deck
#include <chrono> // Seed for shuffle deck
#include <random>
using namespace std;

int main() {
    while(1) {
        string input;

        cout << "Choose options: " << endl;
        cout << "--------------------" << endl;
        cout << "| 1 | Output cards |" << endl;
        cout << "|--- --------------|" << endl;
        cout << "| 2 |     Exit     |" << endl;
        cout << "--------------------" << endl << endl;
        
        int choice;
        while(1) {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, try again." << endl;
                continue;
            }

            if (choice == 1 || choice == 2) {
                cout << endl;
                break;
            } else {
                cout << "Invalid input, try again." << endl;
            }
        }

        if (choice == 1) {
            Picking pick(false, "", true, 0, 0);

            cout << "The following are the input rules:" << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            cout << "| Specify suit  | Enter suit code | Draw cards randomly | Total cards  | Cards per row |" << endl;
            cout << "|--------------- ----------------- --------------------- -------------- ---------------|" << endl;
            cout << "|               |                 |          Y          |              |               |" << endl;
            cout << "|       Y       |     S/H/D/C     |---------------------|    1 ~ 13    |               |" << endl;
            cout << "|               |     [Note]      |          N          |              | > 0, <= Total |" << endl;
            cout << "|--------------- ----------------- --------------------- --------------|               |" << endl;
            cout << "|       N       |       N/A       |  N/A (Default to Y) |    1 ~ 52    |               |" << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            cout << "[Note] S = Spare, H = Heart, D = Diamond, C = Club" << endl << endl;
            
            while(1) {
                cout << "Want to specify the suit? (Enter Y/N): ";
                cin >> input;
                if (input.length() != 1) {
                    cout << "Invalid input, try again." << endl;
                    continue;
                }

                char suit_choice = input[0];
                if (suit_choice == 'Y' || suit_choice == 'y') {
                    pick.set_suit(true);
                    cout << endl;
                    while (1) {
                        cout <<"Enter the suit code (Enter S/H/D/C): ";
                        cin >> input;
                        if (input.length() != 1) {
                            cout << "Invalid input, try again." << endl;
                            continue;
                        }

                        char suit = toupper(input[0]);
                        if (suit == 'S' || suit == 'H' || suit == 'D' || suit == 'C') {
                            string suit_str(1, suit);
                            pick.set_suit_code(suit_str);
                            cout << endl;    
                            break;
                        } else {
                            cout << "Invalid input, try again." << endl;
                        }
                    }

                    while(1) {
                        cout << "Want to draw cards randomly? (Enter Y/N): ";
                        cin >> input;
                        if (input.length() != 1) {
                            cout << "Invalid input, try again." << endl;
                            continue;
                        }

                        char draw_choice = input[0];
                        if (draw_choice == 'Y' || draw_choice == 'y') {
                            pick.set_draw(true);
                            cout << endl;
                            break;
                        } else if (draw_choice == 'N' || draw_choice == 'n') {
                            pick.set_draw(false);
                            cout << endl;
                            break;
                        } else {
                            cout << "Invalid input, try again." << endl;
                        }
                    }

                    int total;
                    while (1) {
                        cout << "Enter the total number of cards (Enter 0 ~ 13): ";
                        cin >> total;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input, try again." << endl;
                            continue;
                        }

                        if (total > 0 && total <= 13) {
                            pick.set_total(total);
                            cout << endl;
                            break;
                        } else {
                            cout << "Invalid input, try again." << endl;
                        }
                    }

                    break;
                } else if (suit_choice == 'N' || suit_choice == 'n') {
                    pick.set_suit(false);
                    pick.set_suit_code("N/A");
                    pick.set_draw(true);
                    cout << endl;
                    int total;
                    while (1) {
                        cout << "Enter the total number of cards (Enter 0 ~ 52): ";
                        cin >> total;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input, try again." << endl;
                            continue;
                        }

                        if (total > 0 && total <= 52) {
                            pick.set_total(total);
                            cout << endl;
                            break;
                        } else {
                            cout << "Invalid input, try again." << endl;
                        }
                    }

                    break;
                } else {
                    cout << "Invalid input, try again." << endl;
                    continue;
                }
            }

            int row;
            while (1) {
                int total_limit = pick.get_total();
                cout << "Enter the number of cards you want in a row (Enter 0 ~ " << total_limit << "): ";
                cin >> row;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input, try again." << endl;
                    continue;
                }

                if (row > 0 && row <= pick.get_total()) {
                    pick.set_row(row);
                    cout << endl;
                    break;
                } else {
                    cout << "Invalid input, try again." << endl;
                }
            }

            bool suit_random = pick.get_suit();
            string suit_code = pick.get_suit_code();
            bool draw_random = pick.get_draw();
            int total = pick.get_total();
            row = pick.get_row();

            string temp_suit_random = (suit_random ? "Y" : "N");

            string temp_suit_code = suit_code;
            if (suit_random) {
                temp_suit_code = " " + suit_code + " ";
            }

            string temp_draw_random = (draw_random ? "Y" : "N");

            string temp_total = to_string(total);
            if (total < 10) {
                temp_total = " " + temp_total;
            }

            string temp_row = to_string(row);
            if (row < 10) {
                temp_row = temp_row + " ";
            }
            cout << "Here are your options:" << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            cout << "| Specify suit  | Enter suit code | Draw cards randomly | Total cards  | Cards per row |" << endl;
            cout << "|--------------- ----------------- --------------------- -------------- ---------------|" << endl;
            cout << "|       " << temp_suit_random;
            cout <<          "       |       " << temp_suit_code;
            cout <<                            "       |          " << temp_draw_random;
            cout <<                                               "          |      " << temp_total;
            cout <<                                                                  "      |       " << temp_row;
            cout <<                                                                                  "      |" << endl;
        //  cout << "|       Y       |        1        |          1          |       1      |       1       |" << endl;  ->  case 1
        //  cout << "|       Y       |        1        |          1          |       1      |       12      |" << endl;  ->  case 2
        //  cout << "|       Y       |        1        |          1          |      12      |       1       |" << endl;  ->  case 3
        //  cout << "|       Y       |        0        |          1          |      12      |       12      |" << endl;  ->  case 4
        //  cout << "|       N       |       N/A       |          1          |       1      |       1       |" << endl;  ->  case 5
        //  cout << "|       N       |       N/A       |          1          |       1      |       12      |" << endl;  ->  case 6
        //  cout << "|       N       |       N/A       |          1          |      12      |       1       |" << endl;  ->  case 7
        //  cout << "|       N       |       N/A       |          1          |      12      |       12      |" << endl;  ->  case 8
            cout << "----------------------------------------------------------------------------------------" << endl << endl;
            bool re_enter = false;
            while(1) {
                cout << "Confirm your options? (Enter Y/N): ";
                cin >> input;
                if (input.length() != 1) {
                    cout << "Invalid input, try again." << endl;
                    continue;
                }

                char confirm_choice = input[0];
                if (confirm_choice == 'Y' || confirm_choice == 'y') {
                    cout << endl;
                    break;
                } else if (confirm_choice == 'N' || confirm_choice == 'n') {
                    cout << endl;
                    cout << "Please re-enter your options." << endl << endl;
                    re_enter = true;
                    break;
                } else {
                    cout << "Invalid input, try again." << endl;
                }
            }

            if (!re_enter) {
                cout << "Here are your cards:" << endl; // check line 184 ~ 188

                vector<Card> deck;
                if (suit_random) {
                    deck = Card::generate_suit_deck(suit_code[0]); // 13 cards
                } else {
                    deck = Card::generate_full_deck(); // 52 cards
                }

                if (draw_random) { // shuffle deck
                    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
                    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
                }

                vector<Card> selected_cards;
                selected_cards = vector<Card>(deck.begin(), deck.begin() + total);

                vector<vector<string>> all_card_lines;
                for (const auto& card : selected_cards) {
                    all_card_lines.push_back(card.to_appearance());
                }

                for (int i = 0; i < total; i += row) {
                    for (int j = 0; j < 10; ++j) {
                        for (int k = i; k < i + row && k < total; ++k) {
                            cout << all_card_lines[k][j] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }
            }

        } else {
            cout << "Goodbye!" << endl << endl;
            break;
        }

        cout << "Press Enter to restart...";
        cin.ignore();
        cin.get();
        cout << endl << "---------------------------------------------------------------------------------------------------" << endl << endl;
    }

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}