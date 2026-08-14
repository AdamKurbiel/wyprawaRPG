#include "rng.hpp"
#include <random>
#include <iostream>

Rng::Rng(){
    std::random_device rd;
    seed = rd();
    std::mt19937 generating(seed);
    std::uniform_int_distribution<int> dist(1,10);
}