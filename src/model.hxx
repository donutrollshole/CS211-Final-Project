#pragma once

#include <ge211.hxx>
#include "tile.hxx"

class Model
{


public:

    Model(bool);

    void on_frame(double);

    void generate_row();
    void get_speed();
    std::vector<Tile> all_tiles() const;
    std::vector<Tile> all_tiles2() const;

    void check_set_game_over();
    void set_game_over();
    bool get_game_over() const;

    int get_bottom_tile_column();
    int get_bottom_tile_column2();

    double get_bottom_tile_y() const;
    double get_bottom_tile_y2() const;

    void delete_clicked_tiles();

    void mark_bottom_clicked();
    void mark_bottom_clicked2();

    void set_game_over_key(int);

    int get_game_over_key() const;

    void set_game_started();

    void reset_game();

    double get_velocity() const;

    int get_current_note_index() const;

    void increment_current_note_index();

    bool get_two_player() const;

    int get_loser() const;

    bool get_game_started();



private:

int loser_;
double velocity_;
std::vector<Tile> tiles_;
bool game_over_;
bool game_started_;
int game_over_key_;
int current_note_index_;
bool twoplayer_;

std::vector<Tile> tiles2_;

};


