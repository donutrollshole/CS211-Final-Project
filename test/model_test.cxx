#include <catch.hxx>
#include "tile.cxx"
#include "model.hxx"
#include <iostream>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

TEST_CASE("one tile falls off screen: single player")
{
    Model test_model = Model(false); // singleplayer model.
    test_model.set_game_started();
    test_model.on_frame(1.5);

    //check what happens when a tile falls off the board, you should lose.
    CHECK(test_model.get_game_over() == true);

}


TEST_CASE("Check to see if reset game works: single player")
{
    Model test_model = Model(false);

    // this starts the game
    test_model.set_game_started();
    test_model.on_frame(1.5); // run the game

    //check that the bottom tile went off the map.
    CHECK(test_model.get_game_over() == true);
    CHECK(test_model.get_game_started() == true);

    // reset the game and check that the game is now not over, and awaiting
    // start.
    test_model.reset_game();
    CHECK(test_model.get_game_over() == false);
    CHECK(test_model.get_game_started() == false);

}

TEST_CASE("both tiles falls off screen: two player")
{
    Model test_model = Model(true); // multiplayer model.
    test_model.set_game_started();

    // check that BOTH players lose if BOTH of their bottom tiles falls off
    // the map at the same time.
    test_model.on_frame(2);
    CHECK(test_model.get_loser() == 2);

}

TEST_CASE("left player cannot keep up & loses") {

    Model test_model = Model(true); //multiplayer model
    test_model.set_game_started();
    test_model.mark_bottom_clicked2(); //the right player has kept up.

    test_model.on_frame(1.5);

    CHECK(test_model.get_loser() == 0); // check that the left player lost.
}

TEST_CASE("check that generate row is adding tiles") {

    Model test_model = Model(false); //singleplayer mode

    std::vector<Tile> tiles = test_model.all_tiles();
    CHECK(tiles.size() == 4); // check that the constructor added in 4 tiles
    // by default.

    // ensure that generate row adds a new Tile into the vector each time.
    for (int i = 5; i<10; i++) {
        test_model.generate_row();
        tiles = test_model.all_tiles();
        CHECK(tiles.size() == i);
    }
}

TEST_CASE("Check click bottom tile sets tiles to clicked properly") {
    Model test_model = Model(false);

    // for each tile, ensure that it is not clicked at initialization.
    std::vector<Tile> tiles = test_model.all_tiles();
    for (auto t: tiles) {
        CHECK(t.isClicked() == false);
    }

    // check that the bottom tile gets clicked.
    test_model.mark_bottom_clicked();
    tiles = test_model.all_tiles();
    CHECK(tiles.begin()->isClicked() == true);

    // click all of the tiles on the board.
    test_model.mark_bottom_clicked();
    test_model.mark_bottom_clicked();
    test_model.mark_bottom_clicked();
    tiles = test_model.all_tiles();

    //check that all of the tiles are clicked.
    for (auto t: tiles) {
        CHECK(t.isClicked() == true);
    }

}

TEST_CASE("multiplayer tiles are always synced via generation & construction")
{
    Model test_model = Model(true);

    // for all tiles on the board, check to make sure both tile vectors are
    // identical, and that the mark_bottom_clicked functions both work.
    for (int i = 0; i < 4; i++) {
        CHECK(test_model.get_bottom_tile_column() == test_model
        .get_bottom_tile_column2() - 4);
        test_model.mark_bottom_clicked();
        test_model.mark_bottom_clicked2();
    }

    // check that generate row works and puts in identical tiles to both
    // players' vectors.
    for (int i = 0; i < 4; i++) {

        test_model.generate_row();

        CHECK(test_model.get_bottom_tile_column() == test_model
        .get_bottom_tile_column2() - 4);

        test_model.mark_bottom_clicked();
        test_model.mark_bottom_clicked2();
    }
}




//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
