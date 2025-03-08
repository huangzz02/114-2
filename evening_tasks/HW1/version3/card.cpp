#include "card.h"
#include <vector>

Card::Card(char s, const std::string& r) : suit(s), rank(r) {}

char Card::get_suit() const{
    return suit;
}

std::string Card::get_rank() const {
    return rank;
}

std::vector<std::wstring> Card::default_appearance() const{ // use wstring for Unicode characters
    std::wstring wide_rank(rank.begin(), rank.end());
    std::wstring wide_suit;
    std::vector<std::wstring> appearance(10);
    std::wstring line1, line2, line3, line4;
    if (suit == 'S') {
        wide_suit = L"♠";
        line1 = L"│    •••    │";
        line2 = L"│   •••••   │";
        line3 = L"│  •••••••  │";
        line4 = L"│    •••    │";
    } else if (suit == 'H') {
        wide_suit = L"♥";
        line1 = L"│   •   •   │";
        line2 = L"│  •••••••  │";
        line3 = L"│   •••••   │";
        line4 = L"│     •     │";
    } else if (suit == 'D') {
        wide_suit = L"♦";
        line1 = L"│    •••    │";
        line2 = L"│   •••••   │";
        line3 = L"│   •••••   │";
        line4 = L"│    •••    │";
    } else if (suit == 'C') {
        wide_suit = L"♣";
        line1 = L"│    •••    │";
        line2 = L"│  •  •  •  │";
        line3 = L"│  •••••••  │";
        line4 = L"│    •••    │";
    }

    appearance[0] = L"┌───────────┐";
    appearance[1] = L"│" + wide_rank + L"          │";
    appearance[2] = L"│" + wide_suit + L"          │";
    appearance[3] = line1;
    appearance[4] = line2;
    appearance[5] = line3;
    appearance[6] = line4;
    appearance[7] = L"│          " + wide_suit + L"│";
    appearance[8] = L"│          " + wide_rank + L"│";
    appearance[9] = L"└───────────┘";

    return appearance;
}

std::vector<std::wstring> Card::simple_appearance() const { // use wstring for Unicode characters
    std::wstring wide_rank(rank.begin(), rank.end());
    std::wstring wide_suit;
    std::vector<std::wstring> appearance(4);
    if (suit == 'S') {
        wide_suit = L"♠";
    } else if (suit == 'H') {
        wide_suit = L"♥";
    } else if (suit == 'D') {
        wide_suit = L"♦";
    } else if (suit == 'C') {
        wide_suit = L"♣";
    }

    appearance[0] = L"┌───┐";
    appearance[1] = L"│ " + wide_rank + L" │";
    appearance[2] = L"│ " + wide_suit + L" │";
    appearance[3] = L"└───┘";

    return appearance;
}

std::vector<std::wstring> Card::unicode_appearance() const { // use wstring for Unicode characters
    std::wstring card_char;
    if (suit == 'S') {
        if (rank == "A") card_char = L"🂡";
        else if (rank == "2") card_char = L"🂢";
        else if (rank == "3") card_char = L"🂣";
        else if (rank == "4") card_char = L"🂤";
        else if (rank == "5") card_char = L"🂥";
        else if (rank == "6") card_char = L"🂦";
        else if (rank == "7") card_char = L"🂧";
        else if (rank == "8") card_char = L"🂨";
        else if (rank == "9") card_char = L"🂩";
        else if (rank == "T") card_char = L"🂪";
        else if (rank == "J") card_char = L"🂫";
        else if (rank == "Q") card_char = L"🂭";
        else if (rank == "K") card_char = L"🂮";
    } else if (suit == 'H') {
        if (rank == "A") card_char = L"🂱";
        else if (rank == "2") card_char = L"🂲";
        else if (rank == "3") card_char = L"🂳";
        else if (rank == "4") card_char = L"🂴";
        else if (rank == "5") card_char = L"🂵";
        else if (rank == "6") card_char = L"🂶";
        else if (rank == "7") card_char = L"🂷";
        else if (rank == "8") card_char = L"🂸";
        else if (rank == "9") card_char = L"🂹";
        else if (rank == "T") card_char = L"🂺";
        else if (rank == "J") card_char = L"🂻";
        else if (rank == "Q") card_char = L"🂽";
        else if (rank == "K") card_char = L"🂾";
    } else if (suit == 'D') {
        if (rank == "A") card_char = L"🃁";
        else if (rank == "2") card_char = L"🃂";
        else if (rank == "3") card_char = L"🃃";
        else if (rank == "4") card_char = L"🃄";
        else if (rank == "5") card_char = L"🃅";
        else if (rank == "6") card_char = L"🃆";
        else if (rank == "7") card_char = L"🃇";
        else if (rank == "8") card_char = L"🃈";
        else if (rank == "9") card_char = L"🃉";
        else if (rank == "T") card_char = L"🃊";
        else if (rank == "J") card_char = L"🃋";
        else if (rank == "Q") card_char = L"🃍";
        else if (rank == "K") card_char = L"🃎";
    } else if (suit == 'C') {
        if (rank == "A") card_char = L"🃑";
        else if (rank == "2") card_char = L"🃒";
        else if (rank == "3") card_char = L"🃓";
        else if (rank == "4") card_char = L"🃔";
        else if (rank == "5") card_char = L"🃕";
        else if (rank == "6") card_char = L"🃖";
        else if (rank == "7") card_char = L"🃗";
        else if (rank == "8") card_char = L"🃘";
        else if (rank == "9") card_char = L"🃙";
        else if (rank == "T") card_char = L"🃚";
        else if (rank == "J") card_char = L"🃛";
        else if (rank == "Q") card_char = L"🃝";
        else if (rank == "K") card_char = L"🃞";
    }
    return {card_char};
}

std::vector<Card> Card::generate_suit_deck(char suit) {
    std::vector<Card> suit_deck;
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
   
    for (const auto& r : ranks) {
        suit_deck.emplace_back(Card(suit, r));
    }
    return suit_deck;
}

std::vector<Card> Card::generate_full_deck() {
    std::vector<Card> full_deck;
    std::vector<char> suits = {'S', 'H', 'D', 'C'};

    for (const auto& s : suits) {
        auto suit_deck = generate_suit_deck(s);
        full_deck.insert(full_deck.end(), suit_deck.begin(), suit_deck.end());
    }
    return full_deck;
}