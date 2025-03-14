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
#include <io.h> // wcout, for special unicode characters
#include <fcntl.h> // wcout, for special unicode characters
using namespace std;

int appearance_mode = 1; // 1: default_appearance, 2: simple_appearance, 3: unicode_appearance

void display_cards(const vector<Card>& cards, int row) {
    vector<vector<wstring>> all_card_lines; // use wstring for Unicode characters
    for (const auto& card : cards) {
        if (appearance_mode == 1) {
            all_card_lines.push_back(card.default_appearance());
        } else if (appearance_mode == 2) {
            all_card_lines.push_back(card.simple_appearance());
        } else {
            all_card_lines.push_back(card.unicode_appearance());
        }
    }

    int cols_per_card;
    if (appearance_mode == 1) cols_per_card = 10;
    else if (appearance_mode == 2) cols_per_card = 4;
    else cols_per_card = 1;

    _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
    for (size_t i = 0; i < cards.size(); i += row) {
        for (int j = 0; j < cols_per_card; ++j) {
            for (size_t k = i; k < i + row && k < cards.size(); ++k) {
                wcout << all_card_lines[k][j] << L" ";
            }
            wcout << endl;
        }
        wcout << endl;
    }
    _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character
}

int main() {
    while(1) {
        string input;

        _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
        wcout << L"┌─────────────────────────┐" << endl;
        wcout << L"│ Choose options:         │" << endl;
        wcout << L"├───┬─────────────────────┤" << endl;
        wcout << L"│ 1 │  Change appearance  │" << endl;
        wcout << L"├───┼─────────────────────┤" << endl;
        wcout << L"│ 2 │    Output cards     │" << endl;
        wcout << L"├───┼─────────────────────┤" << endl;
        wcout << L"│ 3 │ Display a full deck │" << endl;
        wcout << L"├───┼─────────────────────┤" << endl;
        wcout << L"│ 4 │        Exit         │" << endl;
        wcout << L"└───┴─────────────────────┘" << endl;
        _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character
        
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

            if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
                cout << endl;
                break;
            } else {
                cout << "Invalid input, try again." << endl;
            }
        }

        if (choice == 1) {
            _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
            wcout << L"┌──────────────────────────────────────┐" << endl;
            wcout << L"│ Current appearance:                  │" << endl;
            wcout << L"├───┬──────────────────┬───────────────┤" << endl;
            wcout << L"│   │                  │ ┌───────────┐ │" << endl;
            wcout << L"│   │                  │ │A          │ │" << endl;
            wcout << L"│   │                  │ │♠          │ │" << endl;
            wcout << L"│   │                  │ │    •••    │ │" << endl;
            wcout << L"│   │                  │ │   •••••   │ │" << endl;
            wcout << L"│ " << (appearance_mode == 1 ? L"✓" : L" ");
            wcout <<    L" │   1. default     │ │  •••••••  │ │" << endl;
            wcout << L"│   │                  │ │    •••    │ │" << endl;
            wcout << L"│   │                  │ │          ♠│ │" << endl;
            wcout << L"│   │                  │ │          A│ │" << endl;
            wcout << L"│   │                  │ └───────────┘ │" << endl;
            wcout << L"│   │                  │               │" << endl;
            wcout << L"├───┼──────────────────┼───────────────┤" << endl;
            wcout << L"│   │                  │ ┌───┐ ┌───┐   │" << endl;
            wcout << L"│   │                  │ │ A │ │ 2 │   │" << endl;
            wcout << L"│ " << (appearance_mode == 2 ? L"✓" : L" ");
            wcout <<    L" │   2. simple      │ │ ♠ │ │ ♠ │   │" << endl;
            wcout << L"│   │                  │ └───┘ └───┘   │" << endl;
            wcout << L"│   │                  │               │" << endl;
            wcout << L"├───┼──────────────────┼───────────────┤" << endl;
            wcout << L"│ " << (appearance_mode == 3 ? L"✓" : L" ");
            wcout <<    L" │   3. unicode     │ 🂡 🃒 🃓 🃔 🃕 🃖   │" << endl;
            wcout << L"└───┴──────────────────┴───────────────┘" << endl;
            _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character

            int new_appearance_mode;
            while(1) {
                if (appearance_mode == 1) cout << "Enter the appearance you want (Enter 2/3): ";
                else if (appearance_mode == 2) cout << "Enter the appearance yout want (Enter 1/3): ";
                else cout << "Enter the appearance you want (Enter 1/2): ";

                cin >> new_appearance_mode;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input, try again." << endl;
                    continue;
                }

                if (new_appearance_mode <= 0 || new_appearance_mode > 3 || new_appearance_mode == appearance_mode) {
                    cout << "Invalid input, try again." << endl;
                } else {
                    appearance_mode = new_appearance_mode;
                    cout << endl;
                    break;
                }
            }

        } else if (choice == 2) {
            Picking pick(false, "", true, 0, 0);

            _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
            wcout << L"┌──────────────────────────────────────────────────────────────────────────────────────┐" << endl;
            wcout << L"│ The following are the input rules:                                                   │" << endl;
            wcout << L"├───────────────┬─────────────────┬─────────────────────┬──────────────┬───────────────┤" << endl;
            wcout << L"│ Q1.           │ Q2.             │ Q3.                 │ Q4.          │ Q5.           │" << endl;
            wcout << L"│ Specify suit  │ Enter suit code │ Draw cards randomly │ Total cards  │ Cards per row │" << endl;
            wcout << L"├───────────────┼─────────────────┼─────────────────────┼──────────────┼───────────────┤" << endl;
            wcout << L"│               │                 │          Y          │              │               │" << endl;
            wcout << L"│       Y       │  S / H / D / C  ├─────────────────────┤    1 ~ 13    │               │" << endl;
            wcout << L"│               │     [Note]      │          N          │              │ > 0, <= Total │" << endl;
            wcout << L"├───────────────┼─────────────────┼─────────────────────┼──────────────┤               │" << endl;
            wcout << L"│       N       │       N/A       │  N/A (Default to Y) │    1 ~ 52    │               │" << endl;
            wcout << L"├───────────────┴─────────────────┴─────────────────────┴──────────────┴───────────────┤" << endl;
            wcout << L"│ [Note] S = ♠, H = ♥, D = ♦, C = ♣                                                    │" << endl;
            wcout << L"└──────────────────────────────────────────────────────────────────────────────────────┘" << endl;
            _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character
            
            cout << "Q1. ";
            while(1) {
                cout << "Want to specify the suit? (Enter Y/N): ";
                cin >> input;
                if (input.length() != 1) {
                    cout << "    Invalid input, try again." << endl;
                    cout << "    ";
                    continue;
                }

                char suit_choice = input[0];
                if (suit_choice == 'Y' || suit_choice == 'y') {
                    pick.set_suit(true);

                    cout << "Q2. ";
                    while (1) {
                        cout <<"Enter the suit code (Enter S/H/D/C): ";
                        cin >> input;
                        if (input.length() != 1) {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                            continue;
                        }

                        char suit = toupper(input[0]);
                        if (suit == 'S' || suit == 'H' || suit == 'D' || suit == 'C') {
                            string suit_str(1, suit);
                            pick.set_suit_code(suit_str);
                            break;
                        } else {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                        }
                    }

                    cout << "Q3. ";
                    while(1) {
                        cout << "Want to draw cards randomly? (Enter Y/N): ";
                        cin >> input;
                        if (input.length() != 1) {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                            continue;
                        }

                        char draw_choice = input[0];
                        if (draw_choice == 'Y' || draw_choice == 'y') {
                            pick.set_draw(true);
                            break;
                        } else if (draw_choice == 'N' || draw_choice == 'n') {
                            pick.set_draw(false);
                            break;
                        } else {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                        }
                    }

                    int total;
                    cout << "Q4. ";
                    while (1) {
                        cout << "Enter the total number of cards (Enter 0 ~ 13): ";
                        cin >> total;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                            continue;
                        }

                        if (total > 0 && total <= 13) {
                            pick.set_total(total);
                            break;
                        } else {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                        }
                    }

                    break;
                } else if (suit_choice == 'N' || suit_choice == 'n') {
                    cout << "Q2. Enter the suit code (Enter S/H/D/C): N/A" << endl;
                    cout << "Q3. Want to draw cards randomly? (Enter Y/N): N/A (Default to Y)" << endl;

                    pick.set_suit(false);
                    pick.set_suit_code("N/A");
                    pick.set_draw(true);

                    int total;
                    cout << "Q4. ";
                    while (1) {
                        cout << "Enter the total number of cards (Enter 0 ~ 52): ";
                        cin >> total;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                            continue;
                        }

                        if (total > 0 && total <= 52) {
                            pick.set_total(total);
                            break;
                        } else {
                            cout << "    Invalid input, try again." << endl;
                            cout << "    ";
                        }
                    }

                    break;
                } else {
                    cout << "    Invalid input, try again." << endl;
                    cout << "    ";
                    continue;
                }
            }

            int row;
            cout << "Q5. ";
            while (1) {
                int total_limit = pick.get_total();

                cout << "Enter the number of cards you want in a row (Enter 0 ~ " << total_limit << "): ";
                cin >> row;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "    Invalid input, try again." << endl;
                    cout << "    ";
                    continue;
                }

                if (row > 0 && row <= pick.get_total()) {
                    pick.set_row(row);
                    break;
                } else {
                    cout << "    Invalid input, try again." << endl;
                    cout << "    ";
                }
            }

            cout << endl;

            bool suit_random = pick.get_suit();
            string suit_code = pick.get_suit_code();
            bool draw_random = pick.get_draw();
            int total = pick.get_total();
            row = pick.get_row();

            wstring temp_suit_random = (suit_random ? L"Y" : L"N"); // use wstring for Unicode characters

            wstring temp_suit_code(suit_code.begin(), suit_code.end()); // use wstring for Unicode characters
            if (suit_random) {
                temp_suit_code = L" " + temp_suit_code + L" ";
            }

            wstring temp_draw_random = (draw_random ? L"Y" : L"N"); // use wstring for Unicode characters

            wstring temp_total = to_wstring(total); // use wstring for Unicode characters
            if (total < 10) {
                temp_total = L" " + temp_total;
            }

            wstring temp_row = to_wstring(row); // use wstring for Unicode characters
            if (row < 10) {
                temp_row = temp_row + L" ";
            }

            _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
            wcout << L"┌──────────────────────────────────────────────────────────────────────────────────────┐" << endl;
            wcout << L"│ Here are your options:                                                               │" << endl;
            wcout << L"├───────────────┬─────────────────┬─────────────────────┬──────────────┬───────────────┤" << endl;
            wcout << L"│ Specify suit  │ Enter suit code │ Draw cards randomly │ Total cards  │ Cards per row │" << endl;
            wcout << L"├───────────────┼─────────────────┼─────────────────────┼──────────────┼───────────────│" << endl;
            wcout << L"│       " << temp_suit_random;
            wcout <<          L"       │       " << temp_suit_code;
            wcout <<                            L"       │          " << temp_draw_random;
            wcout <<                                               L"          │      " << temp_total;
            wcout <<                                                                  L"      │       " << temp_row;
            wcout <<                                                                                  L"      │" << endl;
        //  wcout << L"│       Y       │        1        │          1          │       1      │       1       │" << endl;  ->  case 1
        //  wcout << L"│       Y       │        1        │          1          │       1      │       12      │" << endl;  ->  case 2
        //  wcout << L"│       Y       │        1        │          1          │      12      │       1       │" << endl;  ->  case 3
        //  wcout << L"│       Y       │        0        │          1          │      12      │       12      │" << endl;  ->  case 4
        //  wcout << L"│       N       │       N/A       │          1          │       1      │       1       │" << endl;  ->  case 5
        //  wcout << L"│       N       │       N/A       │          1          │       1      │       12      │" << endl;  ->  case 6
        //  wcout << L"│       N       │       N/A       │          1          │      12      │       1       │" << endl;  ->  case 7
        //  wcout << L"│       N       │       N/A       │          1          │      12      │       12      │" << endl;  ->  case 8
            wcout << L"└───────────────┴─────────────────┴─────────────────────┴──────────────┴───────────────┘" << endl;
            _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character

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
                    cout << "Please re-enter your options." << endl;
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
                
                display_cards(selected_cards, row);
            }

        } else if (choice == 3) {
            cout << "Here is a full deck of cards:" << endl;

            vector<Card> deck = Card::generate_full_deck();
            
            display_cards(deck, 13);
            
        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;
        }

        cout << "Press Enter to restart...";
        cin.ignore();
        cin.get();
        _setmode(_fileno(stdout), _O_U16TEXT); // transform to wide character
        wcout << L"════════════════════════════════════════════════════════════════════════════════════════════════════" << endl;
        _setmode(_fileno(stdout), _O_TEXT); // transform back to normal character
    }

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}