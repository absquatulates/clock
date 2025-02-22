#include "Time.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <condition_variable>

int main()
{
    Time time{};
    std::mutex mtx;
    std::condition_variable cv;


    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(1));
        time++;

        if (time.get_second() == 0)
            time.log_time();
    }
}