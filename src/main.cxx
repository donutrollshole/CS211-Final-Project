#include "controller.hxx"

ge211::Dims<int> screen_dimensions {415, 4 * 175 + 9};

int main()
{
    Controller(screen_dimensions).run();

    return 0;
}
