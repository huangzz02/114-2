#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    int parentheses = 0, par_count = 0,
        sq_brackets = 0, sq_count = 0,
        braces = 0, br_count = 0;
    
    while(1) {
        cout << "Input a string or 0 to exit: ";
        getline(cin, input);

        if (input == "0") {
            break;
        }

        parentheses = 0, par_count = 0;
        sq_brackets = 0, sq_count = 0;
        braces = 0, br_count = 0;

        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '(') {
                parentheses++;
            } else if (input[i] == ')') {
                parentheses--;
                if (parentheses < 0) {
                    par_count++;
                    parentheses = 0;
                }
            }

            if (input[i] == '[') {
                sq_brackets++;
            } else if (input[i] == ']') {
                sq_brackets--;
                if (sq_brackets < 0) {
                    sq_count++;
                    sq_brackets = 0;
                }
            }

            if (input[i] == '{') {
                braces++;
            } else if (input[i] == '}') {
                braces--;
                if (braces < 0) {
                    br_count++;
                    braces = 0;
                }
            }
        }

        par_count += parentheses;
        sq_count += sq_brackets;
        br_count += braces;

        cout << "Parentheses: " << par_count;
        cout << ", Square Brackets: " << sq_count;
        cout << ", Braces: " << br_count << endl << endl;
    }

    return 0;
}