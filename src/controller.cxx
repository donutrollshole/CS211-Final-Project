#include "controller.hxx"

Controller::Controller(ge211::Dims<int> window_dimensions, bool twoplayer)
        : model_(twoplayer),
          view_(model_, mixer()),
          screen_dimensions_(window_dimensions)
{ }

void Controller::on_key(ge211::Key key) {

    int bottom_key_column = model_.get_bottom_tile_column();
    int bottom_key_column2 = model_.get_bottom_tile_column2();

    // stopping here!!!

    // quit on q
    if (key == ge211::Key::code('q')) {
        quit();
    }

    // if the game is not over (aka normal game functionality)
    if (!model_.get_game_over()) {
        if (key == ge211::Key::code('a')) {
            if (bottom_key_column == 0) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
                view_.play_note();
                model_.increment_current_note_index();
            } else {
                model_.set_game_over_key(0);
                model_.set_game_over();
                view_.play_wrong_note();
            }
        }

        if (key == ge211::Key::code('s')) {
            if (bottom_key_column == 1) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
                view_.play_note();
                model_.increment_current_note_index();

            } else {
                model_.set_game_over_key(1);
                model_.set_game_over();
                view_.play_wrong_note();
            }
        }

        if (key == ge211::Key::code('d')) {
            if (bottom_key_column == 2) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
                view_.play_note();
                model_.increment_current_note_index();
            } else {
                model_.set_game_over_key(2);
                model_.set_game_over();
                view_.play_wrong_note();
            }
        }

        if (key == ge211::Key::code('f')) {
            if (bottom_key_column == 3) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
                view_.play_note();
                model_.increment_current_note_index();
            } else {
                model_.set_game_over_key(3);
                model_.set_game_over();
                view_.play_wrong_note();
            }
        }

        if (model_.get_two_player()) {
            if (key == ge211::Key::code('j')) {
                if (bottom_key_column2 == 4) {
                    model_.mark_bottom_clicked2();
                    model_.set_game_started();
                    view_.play_note();
                    model_.increment_current_note_index();
                } else {
                    model_.set_game_over_key(4);
                    model_.set_game_over();
                    view_.play_wrong_note();
                }
            }

            if (key == ge211::Key::code('k')) {
                if (bottom_key_column2 == 5) {
                    model_.mark_bottom_clicked2();
                    model_.set_game_started();
                    view_.play_note();
                    model_.increment_current_note_index();

                } else {
                    model_.set_game_over_key(5);
                    model_.set_game_over();
                    view_.play_wrong_note();
                }
            }

            if (key == ge211::Key::code('l')) {
                if (bottom_key_column2 == 6) {
                    model_.mark_bottom_clicked2();
                    model_.set_game_started();
                    view_.play_note();
                    model_.increment_current_note_index();

                } else {
                    model_.set_game_over_key(6);
                    model_.set_game_over();
                    view_.play_wrong_note();
                }
            }

            if (key == ge211::Key::code(';')) {
                if (bottom_key_column2 == 7) {
                    model_.mark_bottom_clicked2();
                    model_.set_game_started();
                    view_.play_note();
                    model_.increment_current_note_index();

                } else {
                    model_.set_game_over_key(7);
                    model_.set_game_over();
                    view_.play_wrong_note();
                }
            }
        }
    }

    // if the game is over, allow the game to reset.
    if (model_.get_game_over()) {
        if (key == ge211::Key::code('r')) {
            model_.reset_game();
        }
    }
}

ge211::Dims<int> Controller::initial_window_dimensions() const {
    return screen_dimensions_;
}

void Controller::on_frame(double dt) {
    model_.on_frame(dt);
}
void Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
