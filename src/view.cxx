#include "view.hxx"

static ge211::Color const black {0, 0, 0};
static ge211::Color const gray {172, 172, 172};
static ge211::Color const white {255, 255, 255};
static ge211::Color const red {255, 0, 0};

int tile_height = 175;
int tile_width = 100;
int track_margin = 5;
int window_height = 4 * tile_height + 9;
int tile_spacing = 3;

View::View(Model const& model)
        : model_(model),
          unclicked_tile({tile_width,tile_height}, black),
          clicked_tile({tile_width,tile_height}, gray),
          background_track({tile_width,window_height}, white),
          red_tile({tile_width,tile_height}, red)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    for (int i = 0; i < 4; i++) { // 4 columns in the background.
        set.add_sprite(background_track, board_to_screen(i, 0.0), 0);
    }

    for (auto t: model_.all_tiles()) {
        if (t.isClicked()) {
            set.add_sprite(clicked_tile, board_to_screen(t.get_x_pos(),t
            .get_y_pos()), 1);
        }
        if (!t.isClicked()) {
            set.add_sprite(unclicked_tile, board_to_screen(t.get_x_pos(),t
            .get_y_pos()), 1);
        }

    }

    if (model_.get_game_over()) {
        set.add_sprite(red_tile, board_to_screen(model_.get_game_over_key(),
                                                 model_.get_bottom_tile_y()),
                       1);
    }

}

ge211::Posn<int> View::board_to_screen(int x, double y) {

    int x_new = x * (tile_width + track_margin);
    int y_new = y * (tile_height + tile_spacing);

    return ge211::Posn<int>(x_new,y_new);
}