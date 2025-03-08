#ifndef PICKING_H
#define PICKING_H

#include <string>

class Picking {
    private:
        bool suit_random;
        std::string suit_code;
        bool draw_random;
        int total;
        int row;
    public:
        Picking(bool suit_random, const std::string& suit_code, bool draw_random, int total, int row);
        
        void set_suit(bool suit_random);
        void set_suit_code(std::string suit_code);
        void set_draw(bool draw_random);
        void set_total(int total);
        void set_row(int row);

        bool get_suit();
        const std::string& get_suit_code() const;
        bool get_draw();
        int get_total();
        int get_row();
};

#endif