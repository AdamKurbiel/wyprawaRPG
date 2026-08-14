#include "rng.hpp"
#include <random>
#include <iostream>

Rng::Rng(){
    seed = 1;
    std::mt19937 generating(seed);
    std::uniform_int_distribution<int> dist(1,10);
}

template <typename T>
T Rng::range(T min, T max){
    std::mt19937 generating(seed);
    std::uniform_int_distribution<T> dist(min,max);

    return dist(generating);
}