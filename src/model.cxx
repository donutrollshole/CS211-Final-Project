#include "model.hxx"
#include <cstdlib>
#include <iostream>

Model::Model()
    : velocity_(1.0),
      tiles_(),
      game_over_(false),
      game_started_(false),
      game_over_key_(0),
      current_note_index_(0)
{
    // push stuff into tiles_()
    tiles_.push_back(Tile(false, rand() % 4, 3.0));
    tiles_.push_back(Tile(false, rand() % 4, 2.0));
    tiles_.push_back(Tile(false, rand() % 4, 1.0));
    tiles_.push_back(Tile(false, rand() % 4, 0.0));

}


std::vector<Tile>
Model::all_tiles() const {
    return tiles_;
}

void Model::generate_row() {
    double y = tiles_.back().get_y_pos() - 1.0;
    int x = rand() % 4;

    tiles_.push_back(Tile(false, x,y));
}


void Model::on_frame(double dt)
{

    if (!game_over_) {
        if (game_started_) {
            if (tiles_.back().get_y_pos() >= 0) {
                generate_row();
            }

            for (auto& t: tiles_) {
                t.change_y(velocity_, dt);
            }

            velocity_ += 0.001;

            check_set_game_over(); // checks if game is over & sets true if so
            delete_clicked_tiles();
        }
    }
}

void Model::check_set_game_over() {
    for (auto t: tiles_) {
        if (!t.isClicked() && t.get_y_pos() > 4.0) {
            game_over_ = true;
        }
    }
}

void Model::set_game_over() {
    game_over_ = true;
}

void Model::delete_clicked_tiles()
{
    for (auto &t: tiles_) {
        if (t.get_y_pos() > 5.0 && t.isClicked()) {
            tiles_.erase(tiles_.begin());
        }
    }
}

int Model::get_bottom_tile_column() {
    for (auto t: tiles_) {
        if (!t.isClicked()) {
            return t.get_x_pos();
        }
    }
    return -1;
}

double Model::get_bottom_tile_y() const {
    for (auto t : tiles_) {
        if (!t.isClicked()) {
            return t.get_y_pos();
        }
    }
    return tiles_.back().get_y_pos(); //look at this later, also consider the case where
    // its
    // game
    // over and its not because you messed up the key
}


void Model::mark_bottom_clicked() {
    for (auto &t: tiles_) {
        if (!t.isClicked()) {
            t.mark_clicked();
            return;
        }
    }
}

bool Model::get_game_over() const {
    return game_over_;
}

void Model::set_game_over_key(int key) {
    game_over_key_ = key;
}

int Model::get_game_over_key() const {
    return game_over_key_;
}

void Model::set_game_started() {
    game_started_ = true;
}

void Model::reset_game() { // basically I just copied the constructor.
    game_started_ = false;
    game_over_ = false;
    velocity_ = 1.0;
    game_over_key_ = 0;
    tiles_.clear();
    tiles_.push_back(Tile(false, rand() % 4, 3.0));
    tiles_.push_back(Tile(false, rand() % 4, 2.0));
    tiles_.push_back(Tile(false, rand() % 4, 1.0));
    tiles_.push_back(Tile(false, rand() % 4, 0.0));
    current_note_index_ = 0;
}

double Model::get_velocity() const {
    return velocity_;
}

int Model::get_current_note_index() const {
    return current_note_index_;
}

void Model::increment_current_note_index() {
    current_note_index_ += 1;
}