#include "cplayer.h"
#include <iostream>

int main(int argc, char** argv)
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " sound_file [loop]" << std::endl;
        return 1;
    }
    CPlayer player;
    player.load(argv[1]);
    if (argv[2] && (strcmp(argv[2], "loop") == 0))
    {
        player.loop();
    }
    else
    {
        player.play();
    }
}