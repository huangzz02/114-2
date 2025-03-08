#include <iostream>
#include <io.h>      // 僅限 Windows
#include <fcntl.h>   // 僅限 Windows
using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"♤" << endl;
    _setmode(_fileno(stdout), _O_TEXT);
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}