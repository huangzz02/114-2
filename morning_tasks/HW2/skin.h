#ifndef SKIN_H
#define SKIN_H

#include <string>

class Skin {
    private:
        std::string character_name;
        std::string skin_name;
        int price;
        bool sold;
    public:
        Skin(std::string char_name, std::string sk_name, int p);
        void set_price(int new_price);
        std::string get_character_name();
        std::string get_skin_name();
        int get_price();
        bool is_sold();
        void set_sold(bool status);
};

#endif