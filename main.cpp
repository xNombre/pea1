#include "Menu.hpp"

#include "TimeBench.hpp"
#include "TimeBench.cpp"
#include <chrono>
#include <thread>
#include <iostream>

struct idk {

};

    using namespace std::chrono_literals;
idk wtf()
{
    for (int i = 0; i < 100; i++)
        std::this_thread::sleep_for(10ms);
    std::cout << "eo" << std::endl;
    return idk();
}

int main()
{
    std::function<idk(void)> fun = wtf;
    TimeBench<idk> test(fun);
    auto future = test.start_benchmark(900ms);

    future.wait();
    std::cout << "end" << std::endl;
    
    //std::this_thread::sleep_for(4s);
    //menu();
    return 0;
}