#include "tile.hxx"


//constructor
Tile::Tile(bool tf, int x, double y )
    : clicked_(tf),
      x_pos_(x),
      y_pos_(y)
{}


//get_x_position
int Tile::get_x_pos() {
    return x_pos_;
}

//get_y_position
double Tile::get_y_pos() const {
    return y_pos_;
}

//isClicked
bool Tile::isClicked() {
    return clicked_;
}

void Tile::change_y(double velocity, double dt)
{
    y_pos_ += velocity * dt;
}

void Tile::mark_clicked() {
    clicked_ = true;
}