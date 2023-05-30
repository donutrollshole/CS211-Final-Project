#pragma once
#include <ge211.hxx>

class Tile {

    public:

    Tile(bool, int, double) ;

    int get_x_pos();
    double get_y_pos() const;

    void change_y(double velocity, double dt);

    bool isClicked();

    void mark_clicked();


    private:

    bool clicked_;
    int x_pos_;
    double y_pos_;

};
