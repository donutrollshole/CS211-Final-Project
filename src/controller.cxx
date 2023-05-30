#include "controller.hxx"

Controller::Controller(ge211::Dims<int> window_dimensions)
        : model_(),
          view_(model_),
          screen_dimensions_(window_dimensions)
{ }

void Controller::on_key(ge211::Key key) {

    int bottom_key_column = model_.get_bottom_tile_column();

    if (!model_.get_game_over()) {

        if (key == ge211::Key::code('j')) {
            if (bottom_key_column == 0) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
            } else {
                model_.set_game_over();
                model_.set_game_over_key(0);
            }
        }

        if (key == ge211::Key::code('k')) {
            if (bottom_key_column == 1) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
            } else {
                model_.set_game_over();
                model_.set_game_over_key(1);
            }
        }

        if (key == ge211::Key::code('l')) {
            if (bottom_key_column == 2) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
            } else {
                model_.set_game_over();
                model_.set_game_over_key(2);
            }
        }

        if (key == ge211::Key::code(';')) {
            if (bottom_key_column == 3) {
                model_.mark_bottom_clicked();
                model_.set_game_started();
            } else {
                model_.set_game_over();
                model_.set_game_over_key(3);
            }
        }
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const {
    return screen_dimensions_;
}

void Controller::on_frame(double dt) {
    model_.on_frame(dt);
}
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

