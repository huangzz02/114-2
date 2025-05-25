#include "skin.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    cout << "Enter the account amount: ";
    int account;
    cin >> account;
    cout << endl;

    Skin skins[6] = {
        Skin("C1", "S1", 0),
        Skin("C1", "S2", 0),
        Skin("C1", "S3", 0),
        Skin("C2", "S4", 0),
        Skin("C2", "S5", 0),
        Skin("C2", "S6", 0)
    };

    skins[0].set_price(100);
    skins[1].set_price(200);
    skins[2].set_price(300);
    skins[3].set_price(400);
    skins[4].set_price(700);
    skins[5].set_price(800);

    while(1) {
        cout << "-----------------------------------------------" << endl << endl;
        cout << "Enter 1 to buy a skin, 2 to exit: ";
        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 2) {
            break;
        }

        cout << "===============Skin Shop===============" << endl << endl;
        cout << skins[0].get_character_name() << ":" << endl << "  ";
        for (int i = 0; i < 3; i++) {
            if (skins[i].is_sold()) {
                cout << skins[i].get_skin_name() << ": Sold Out  ";
            } else {
                cout << skins[i].get_skin_name() << ": " << skins[i].get_price() << "  ";
            }
        }
        cout << endl;
        cout << skins[3].get_character_name() << ":" << endl << "  ";
        for (int i = 3; i < 6; i++) {
            if (skins[i].is_sold()) {
                cout << skins[i].get_skin_name() << ": Sold Out  ";
            } else {
                cout << skins[i].get_skin_name() << ": " << skins[i].get_price() << "  ";
            }
        }
        cout << endl;
        cout << endl << "=======================================" << endl << endl;
        cout << "Account balance: " << account << endl << endl;

        cout << "Enter the character you want to choose: ";
        string character;
        cin >> character;
        cout << "Enter the skin you want to purchase: ";
        string skin;
        cin >> skin;
        cout << endl;

        int selected_index = -1;
        for (int i = 0; i < 6; i++) {
            if (skins[i].get_character_name() == character && skins[i].get_skin_name() == skin) {
                selected_index = i;
                break;
            }
        }

        if (skins[selected_index].is_sold()) {
            cout << "Sold out!" << endl << endl;
        } else if (account < skins[selected_index].get_price()) {
            cout << "Sorry! Insufficient account balance." << endl << endl;
        } else {
            skins[selected_index].set_sold(true);
            account -= skins[selected_index].get_price();

            cout << "Congratulation! You have skin \"" << skin << "\" now." << endl;
            cout << "Account balance: " << account << endl << endl;
        }
    }

    cout << "Thanks for coming. Hope to see you again soon!" << endl << endl;

    cout << "Press Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    std::getchar();

    return 0;
}