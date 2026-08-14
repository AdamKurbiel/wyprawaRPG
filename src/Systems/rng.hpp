/*
TBD.

RNG class contains random number generator function with set seed on the
start of the program.
in future seed is stored and loaded in the save file.
*/
#pragma once

#include <random>
#include <iostream>

class Rng
{
    private:
        unsigned seed;
    public:
        Rng();
        
        template <typename T>
        T range(T min, T max) {
            std::mt19937 generating(seed);
            std::uniform_int_distribution<T> dist(min, max);
            return dist(generating);
        }
};
