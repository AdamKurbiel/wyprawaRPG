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
};
