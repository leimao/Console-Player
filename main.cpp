#include "cplayer.h"
#include <iostream>

int main()
{
    //CPlayer player("BetterSounds.wav");
    CPlayer player;
    player.load("BetterSounds.wav");
    //CPlayer player;
    //player.load("about_time.wav");
    //player.load("sawing-wood-daniel_simon.wav");
    //player.printSoundInfo();
    //player.play();
    //player.load("BetterSounds.wav");
    player.load("ChillingMusic.wav");
    //std::cout << player.getFilename() << std::endl;
    //player.play();
    player.loop();
}