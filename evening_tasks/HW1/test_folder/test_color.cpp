#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

#define RED "\033[31;1m"
#define DEFAULT "\033[0m"
#define WHITE "\033[1;37m"

int main() {
#ifdef _WIN32
    // 取得標準輸出控制台的句柄
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    // 取得當前模式
    if (GetConsoleMode(hOut, &dwMode)) {
        // 啟用虛擬終端機處理
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

    std::cout << RED << "這是紅色文字" << DEFAULT << std::endl;
    std::cout << WHITE << "這是白色文字" << DEFAULT << std::endl;

    std::cout << "按 Enter 鍵退出..." << std::endl;
    std::cin.get();

    return 0;
}