#include "model.hxx"
#include "tile.hxx"

Model::Model(bool twoplayer)
    : loser_(-1),
      velocity_(1.0),
      tiles_(),
      game_over_(false),
      game_started_(false),
      game_over_key_(0),
      current_note_index_(0),
      twoplayer_(twoplayer)
{
    // push stuff into tiles_()
    tiles_.push_back(Tile(false, rand() % 4, 3.0));
    tiles_.push_back(Tile(false, rand() % 4, 2.0));
    tiles_.push_back(Tile(false, rand() % 4, 1.0));
    tiles_.push_back(Tile(false, rand() % 4, 0.0));

    if (twoplayer_) {
        for (auto tile: tiles_) {
            tile.change_x(4);
            tiles2_.push_back(tile);
        }
    }

}


std::vector<Tile>
Model::all_tiles() const {
    return tiles_;
}

std::vector<Tile>
Model::all_tiles2() const {
    return tiles2_;
}

void Model::generate_row() {
    double y = tiles_.back().get_y_pos() - 1.0;
    int x = rand() % 4;

    tiles_.push_back(Tile(false, x,y));

    if (twoplayer_) {
        Tile equiv_tile = tiles_.back();
        equiv_tile.change_x(4);
        tiles2_.push_back(equiv_tile);
    }
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

            if (twoplayer_) {
                for (auto& t: tiles2_) {
                    t.change_y(velocity_, dt);
                }
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
            loser_ = 0;
        }
    }

    if (twoplayer_) {
        for (auto t: tiles2_) {
            if (!t.isClicked() && t.get_y_pos() > 4.0) {
                if (game_over_) {
                    loser_ = 2;
                }
                else {
                game_over_ = true;
                loser_ = 1;
                }
            }
        }
    }
}

void Model::set_game_over() {
    game_over_ = true;

    if (game_over_key_ <= 3) {
        loser_ = 0;
    }
    else if (game_over_key_ >= 4) {
        loser_ = 1;
    }
}

void Model::delete_clicked_tiles()
{
    for (auto &t: tiles_) {
        if (t.get_y_pos() > 5.0 && t.isClicked()) {
            tiles_.erase(tiles_.begin());
        }
    }

    if (twoplayer_) {
        for (auto &t: tiles2_) {
            if (t.get_y_pos() > 5.0 && t.isClicked()) {
                tiles2_.erase(tiles2_.begin());
            }
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

int Model::get_bottom_tile_column2() {
    for (auto t: tiles2_) {
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
    return tiles_.back().get_y_pos();

}

double Model::get_bottom_tile_y2() const {
    for (auto t : tiles2_) {
        if (!t.isClicked()) {
            return t.get_y_pos();
        }
    }
    return tiles2_.back().get_y_pos();

}


void Model::mark_bottom_clicked() {
    for (auto &t: tiles_) {
        if (!t.isClicked()) {
            t.mark_clicked();
            return;
        }
    }
}

void Model::mark_bottom_clicked2() {
    for (auto &t: tiles2_) {
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

    if (twoplayer_) {
        tiles2_.clear();
        for (auto tile: tiles_) {
            tile.change_x(4);
            tiles2_.push_back(tile);;
        }
    }
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

bool Model::get_two_player() const {
    return twoplayer_;
}

int Model::get_loser() const {
    return loser_;
}

bool Model::get_game_started() {
    return game_started_;
}