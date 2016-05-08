#pragma once
#include <chrono>
#include "TRandom3.h"
namespace bene {

struct Rand {
    static TRandom3 rand;
};

TRandom3 Rand::rand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}