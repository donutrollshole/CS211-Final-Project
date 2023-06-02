#include "view.hxx"
#include <iostream>

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
int multiplayer_margin = 50;

static std::string const A_sound_filename {"A.mp3"};
static std::string const B_sound_filename {"B.mp3"};
static std::string const C_sound_filename {"C.mp3"};
static std::string const D_sound_filename {"D.mp3"};
static std::string const E_sound_filename {"E.mp3"};
static std::string const F_sound_filename {"F.mp3"};
static std::string const G_sound_filename {"G.mp3"};
static std::string const wrong_note_sound_filename {"wrong.mp3"};

View::View(Model const& model, ge211::Mixer& mixer)
        : model_(model),
          notes_(),
          unclicked_tile({tile_width,tile_height}, black),
          clicked_tile({tile_width,tile_height}, gray),
          background_track({tile_width,window_height}, white),
          red_tile({tile_width,tile_height}, red),
          mixer_(mixer)
{
    ge211::Text_sprite::Builder word_builder(sans60_);
    word_builder.color(purple);
    word_builder.message("Game Over");
    game_over_sprite_.reconfigure(word_builder);

    // load audio
    load_audio_();

    // add in Mary Had a Little Lamb
    notes_.push_back(E_);
    notes_.push_back(D_);
    notes_.push_back(C_);
    notes_.push_back(D_);
    notes_.push_back(E_);
    notes_.push_back(E_);
    notes_.push_back(E_);
    notes_.push_back(D_);
    notes_.push_back(D_);
    notes_.push_back(D_);
    notes_.push_back(E_);
    notes_.push_back(G_);
    notes_.push_back(G_);
    notes_.push_back(E_);
    notes_.push_back(D_);
    notes_.push_back(C_);
    notes_.push_back(D_);
    notes_.push_back(E_);
    notes_.push_back(E_);
    notes_.push_back(E_);
    notes_.push_back(D_);
    notes_.push_back(D_);
    notes_.push_back(E_);
    notes_.push_back(D_);
    notes_.push_back(C_);

    //This code can be used to create the winner and loser text sprites
    word_builder.font(sans60_);
    word_builder.color(purple);
    word_builder.message("Winner");
    winner_sprite_.reconfigure(word_builder);

    word_builder.font(sans60_);
    word_builder.color(purple);
    word_builder.message("Loser");
    loser_sprite_.reconfigure(word_builder);
}

void View::draw(ge211::Sprite_set& set)
{
    for (int i = 0; i < 4; i++) { // 4 columns in the background.
        set.add_sprite(background_track,
                       board_to_screen(i, 0.0), 0);
    }

    if (model_.get_two_player()) {
        for (int i = 4; i < 8; i++) { // right 4 columns in the background.
            set.add_sprite(background_track,
                           board_to_screen(i, 0.0).right_by
            (multiplayer_margin),0);
        }
    }

    for (auto t: model_.all_tiles()) {
        if (t.isClicked()) {
            set.add_sprite(clicked_tile,
                           board_to_screen(t.get_x_pos(),t
            .get_y_pos()), 1);
        }
        if (!t.isClicked()) {
            set.add_sprite(unclicked_tile,
                           board_to_screen(t.get_x_pos(),t
                           .get_y_pos()), 1);
        }

    }

    if (model_.get_two_player()) {
        for (auto t: model_.all_tiles2()) {

            if (t.isClicked()) {
                set.add_sprite(clicked_tile,
                               board_to_screen(t.get_x_pos(),t
                .get_y_pos()).right_by(multiplayer_margin), 1);
            }
            if (!t.isClicked()) {
                set.add_sprite(unclicked_tile,
                               board_to_screen(t.get_x_pos(),t
                .get_y_pos()).right_by(multiplayer_margin),1);
            }
        }
    }



    // this adds velocity to the screen
    ge211::Text_sprite::Builder count_builder(sans28_);
    count_builder << "Speed:  " << model_.get_velocity();
    count_builder.color(purple);
    velocity_sprite_.reconfigure(count_builder);

    if (!model_.get_two_player()) {
        // int velocity_sprite_x = 210 - velocity_sprite_.dimensions().width/2;
        set.add_sprite(velocity_sprite_, {112, 0}, 3);
    }
    else if (model_.get_two_player()) {
        set.add_sprite(velocity_sprite_, {350, 0}, 3);
    }

    if (!model_.get_two_player()) {
        if (model_.get_game_over()) {

            set.add_sprite(red_tile, board_to_screen(
                    model_.get_game_over_key(),model_
                    .get_bottom_tile_y()),1 );

            // this adds the game over text to the screen
            int game_over_x = 210 - game_over_sprite_.dimensions().width / 2;
            int game_over_y = 100 - game_over_sprite_.dimensions().height / 2;
            ge211::Posn<int> posn = {game_over_x, game_over_y};
            set.add_sprite(game_over_sprite_, posn, 2);
        }
    }
        else if (model_.get_two_player()) {
            if (model_.get_game_over()) {

                if (model_.get_loser() == 0) {
                    set.add_sprite(red_tile,
                                   board_to_screen(
                                           model_.get_game_over_key(),
                                           model_.get_bottom_tile_y()),
                                   1);
                }
                else if (model_.get_loser() == 1) {
                    set.add_sprite(red_tile, board_to_screen(
                            model_.get_game_over_key(),
                            model_.get_bottom_tile_y2()).
                            right_by(multiplayer_margin),1);
                }

                // this adds the game over text to the screen
                if (model_.get_loser() == 0) {
                    int loser_x = 210 - loser_sprite_.dimensions().width
                            / 2;
                    int loser_y = 100 - loser_sprite_.dimensions().height
                            / 2;
                    ge211::Posn<int> posn = {loser_x, loser_y};
                    set.add_sprite(loser_sprite_, posn, 2);

                    int winner_x = 675 - winner_sprite_.dimensions().width
                                        / 2;
                    int winner_y = 100 - winner_sprite_.dimensions().height
                                        / 2;
                    ge211::Posn<int> posn2 = {winner_x, winner_y};
                    set.add_sprite(winner_sprite_, posn2, 2);
                }
                else if (model_.get_loser() == 1) {
                    int loser_x = 675 - loser_sprite_.dimensions().width
                                        / 2;
                    int loser_y = 100 - loser_sprite_.dimensions().height
                                        / 2;
                    ge211::Posn<int> posn = {loser_x, loser_y};
                    set.add_sprite(loser_sprite_, posn, 2);

                    int winner_x = 210 - winner_sprite_.dimensions().width
                                        / 2;
                    int winner_y = 100 - winner_sprite_.dimensions().height
                                        / 2;
                    ge211::Posn<int> posn2 = {winner_x, winner_y};
                    set.add_sprite(winner_sprite_, posn2, 2);
                }
                else if (model_.get_loser() == 2) {
                    int loser_x = 675 - loser_sprite_.dimensions().width
                                        / 2;
                    int loser_y = 100 - loser_sprite_.dimensions().height
                                        / 2;
                    ge211::Posn<int> posn = {loser_x, loser_y};
                    set.add_sprite(loser_sprite_, posn, 2);

                    int loser2_x = 210 - loser_sprite_.dimensions().width
                                        / 2;
                    int loser2_y = 100 - loser_sprite_.dimensions().height
                                        / 2;
                    ge211::Posn<int> posn2 = {loser2_x, loser2_y};
                    set.add_sprite(loser_sprite_, posn2, 2);
                }
            }
        }

}

ge211::Posn<int> View::board_to_screen(int x, double y) {

    int x_new = x * (tile_width + track_margin);
    int y_new = y * (tile_height + tile_spacing);

    return ge211::Posn<int>(x_new,y_new);
}

void View::load_audio_() {
    A_.try_load(A_sound_filename, mixer_);
    B_.try_load(B_sound_filename, mixer_);
    C_.try_load(C_sound_filename, mixer_);
    D_.try_load(D_sound_filename, mixer_);
    E_.try_load(E_sound_filename, mixer_);
    F_.try_load(F_sound_filename, mixer_);
    G_.try_load(G_sound_filename, mixer_);
    wrong_note_.try_load(wrong_note_sound_filename, mixer_);
}

void View::play_note() {
    mixer_.try_play_effect(notes_[model_.get_current_note_index() %
    (notes_.size())]);
}

void View::play_wrong_note() {
    mixer_.try_play_effect(wrong_note_);
}