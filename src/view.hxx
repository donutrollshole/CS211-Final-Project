#pragma once

#include "model.hxx"
#include "tile.hxx"

class View
{
public:
    explicit View(Model const& model, ge211::Mixer& mixer);

    void draw(ge211::Sprite_set& set);

    ge211::Posn<int> board_to_screen(int x, double y);

    // ge211::Dims<int> initial_window_dimensions() const;

private:
    Model const& model_;

    ge211::Rectangle_sprite unclicked_tile;
    ge211::Rectangle_sprite clicked_tile;
    ge211::Rectangle_sprite background_track;
    ge211::Rectangle_sprite red_tile;

    ge211::Font sans28_{"sans.ttf", 28};
    ge211::Font sans60_{"sans.ttf", 60};
    ge211::Text_sprite velocity_sprite_;
    ge211::Text_sprite game_over_sprite_;

    ge211::Mixer& mixer_;
    ge211::Sound_effect A_;
    ge211::Sound_effect B_;
    ge211::Sound_effect C_;
    ge211::Sound_effect D_;
    ge211::Sound_effect E_;
    ge211::Sound_effect F_;
    ge211::Sound_effect G_;
    ge211::Sound_effect wrong_note_;
};
