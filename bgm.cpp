#include "cplayer.h"
#include <thread>
#include <iostream>
#include <future>

#include <chrono>

void playBGM(const char* filename, int& i)
{
    CPlayer player;
    player.load(filename);
    player.play();
}


void playStoppableBGM(CPlayer* player, int& i)
{
    (*player).play();
}

int main(int argc, char** argv)
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " sound_file [loop]" << std::endl;
        return 1;
    }

    /* Several ways of playing sound asynchronously */

    /* Thread passed by member function and instance */
    int i = 0;
    CPlayer player;
    player.load(argv[1]);
    std::thread t1(&CPlayer::play, &player);
    for (i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
    }
    t1.join();

    /* Thread passed by function */
    i = 0;
    std::thread t2(playBGM, argv[1], std::ref(i));
    for (i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
    }
    t2.join();

    /* Async passed by function */
    i = 0;
    auto handle = std::async(std::launch::async, playBGM, argv[1], std::ref(i));
    for (i = 0; i < 1000; i ++)
    {
        std::cout << i << std::endl;
    }
    handle.get();

    /*
     * To interrupt asynchronous process, we can implement APIs in the functions to kill.
     * In our case, we want to make things simple without implementing additional APIs.
     */

    return 0;
}



void threadFunction(std::future<void> future){
   std::cout << "Starting the thread" << std::endl;
   while (future.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout){
      std::cout << "Executing the thread....." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500)); //wait for 500 milliseconds
   }
   std::cout << "Thread Terminated" << std::endl;
}
main(){
   std::promise<void> signal_exit; //create promise object
   std::future<void> future = signal_exit.get_future();//create future objects
   std::thread my_thread(&threadFunction, std::move(future)); //start thread, and move future
   std::this_thread::sleep_for(std::chrono::seconds(7)); //wait for 7 seconds
   std::cout << "Threads will be stopped soon...." << std::endl;
   signal_exit.set_value(); //set value into promise
   my_thread.join(); //join the thread with the main thread
   std::cout << "Doing task in main function" << std::endl;
}