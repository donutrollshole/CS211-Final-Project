#pragma once

#include <ge211.hxx>
#include "tile.hxx"

class Model
{


public:

    Model();

    void on_frame(double);

    void generate_row();
    void get_speed();
    std::vector<Tile> all_tiles() const;

    void check_set_game_over();
    void set_game_over();
    bool get_game_over() const;

    int get_bottom_tile_column();
    double get_bottom_tile_y() const;

    void delete_clicked_tiles();

    void mark_bottom_clicked();

    void set_game_over_key(int);

    int get_game_over_key() const;

    void set_game_started();

    void reset_game();



private:

double velocity_;
std::vector<Tile> tiles_;
bool game_over_;
bool game_started_;
int game_over_key_;

};


