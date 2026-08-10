#include "rng.hpp"
#include <random>
#include <iostream>

Rng::Rng(){
    seed = 1;
    std::mt19937 generating(seed);
    std::uniform_int_distribution<int> dist(1,10);
    
    std::cout << "Control gen: " << dist(generating) << std::endl;
}