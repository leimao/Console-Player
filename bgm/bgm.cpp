#include "cplayer.h"
#include <thread>
#include <iostream>
#include <future>

#include <chrono>

void playBGM(const char* filename)
{
    CPlayer player;
    player.load(filename);
    player.play();
}

void playKillableBGM(const char* filename, bool& killSignal)
{
    CPlayer player;
    player.load(filename);
    player.loopAsync(killSignal);
}


int main(int argc, char** argv)
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " sound_file" << std::endl;
        return 1;
    }

    /* 
     * Several ways of playing sound asynchronously 
     */

    // Thread passed by member function and instance
    CPlayer player;
    player.load(argv[1]);
    std::thread t1(&CPlayer::play, &player);
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    t1.join();

    // Thread passed by function
    std::thread t2(playBGM, argv[1]);
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    t2.join();

    // Async passed by function
    auto handle = std::async(std::launch::async, playBGM, argv[1]);
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    handle.get();

    /*
     * To interrupt asynchronous process, we use the APIs to kill.
     */
    bool killSignal = false;

    std::thread t3(&CPlayer::loopAsync, &player, std::ref(killSignal));
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        if (i == 500)
        {
            killSignal = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    t3.join();

    killSignal = false;
    std::thread t4(playKillableBGM, argv[1], std::ref(killSignal));
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        if (i == 500)
        {
            killSignal = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    t4.join();

    killSignal = false;
    handle = std::async(std::launch::async, playKillableBGM, argv[1], std::ref(killSignal));
    for (int i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
        if (i == 500)
        {
            killSignal = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    handle.get();

    return 0;
}

