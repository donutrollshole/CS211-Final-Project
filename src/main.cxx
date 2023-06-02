#include "controller.hxx"

ge211::Dims<int> screen_dimensions {415, 4 * 175 + 9};
ge211::Dims<int> screen_dimensions2 {880, 4 * 175 + 9};


int main(int argc, char *argv[])
{
    switch(argc) {
    case 1:
        Controller(screen_dimensions, false).
        run();

    case 2:
        std::string input = (argv[1]);
        if ("-c" == input) {
            Controller(screen_dimensions2, true).
            run();
        }
        else {
            Controller(screen_dimensions, false).
            run();
        }

    }

    return 0;
}
