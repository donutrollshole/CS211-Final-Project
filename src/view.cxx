#include "view.hxx"

static ge211::Color const black {0, 0, 0};
static ge211::Color const gray {172, 172, 172};
static ge211::Color const white {255, 255, 255};
static ge211::Color const red {255, 0, 0};
static ge211::Color const blue {0, 0, 255};
static ge211::Color const purple {129, 88, 209};

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
{
    ge211::Text_sprite::Builder word_builder(sans60_);
    word_builder.color(purple);
    word_builder.message("Game Over");
    game_over_sprite_.reconfigure(word_builder);

    // This code can be used to create the winner and loser text sprites
    // Still must define color blue & initiate sprites in .hxx
    // word_builder.font(sans36_);
    // word_builder.color(blue);
    // word_builder.message("Winner");
    // winner_sprite_.reconfigure(word_builder);

    // word_builder.font(sans36_);
    // word_builder.color(red);
    // word_builder.message("Loser");
    // loser_sprite_.reconfigure(word_builder);


}

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

    // this adds velocity to the screen
    ge211::Text_sprite::Builder count_builder(sans28_);
    count_builder << "Speed:  " << model_.get_velocity();
    count_builder.color(purple);
    velocity_sprite_.reconfigure(count_builder);
    //int velocity_sprite_x = 210 - velocity_sprite_.dimensions().width/2;
    set.add_sprite(velocity_sprite_, {112, 0}, 3);

    if (model_.get_game_over()) {
        set.add_sprite(red_tile, board_to_screen(model_.get_game_over_key(),
                                                 model_.get_bottom_tile_y()),
                       1);
        // this adds the game over text to the screen
        int game_over_x = 210 - game_over_sprite_.dimensions().width/2;
        int game_over_y = 100 - game_over_sprite_.dimensions().height/2;
        ge211::Posn<int> posn = {game_over_x, game_over_y};
        set.add_sprite(game_over_sprite_, posn, 2);
    }

}

ge211::Posn<int> View::board_to_screen(int x, double y) {

    int x_new = x * (tile_width + track_margin);
    int y_new = y * (tile_height + tile_spacing);

    return ge211::Posn<int>(x_new,y_new);
}