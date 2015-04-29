#ifndef BENE_ALGORITHM
#define BENE_ALGORITHM
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TROOT.h"


namespace bene
{

    template<typename T>
    inline T min(const std::vector<T> &v)
    {
        return *std::min_element(v.begin(), v.end());
    }

    template<typename T, int col>
    inline T min(const std::vector<std::tuple<T,T>> &v)
    {
        T min = std::numeric_limits<T>::max();

        for(const auto & e: v) {
            min = std::get<col>(e) < min ? std::get<col>(e) : min;
        }

        return min;
    }

    template<typename T, int col>
    inline T min(const std::vector<std::tuple<T,T,T>> &v)
    {
        T min = std::numeric_limits<T>::max();

        for(const auto & e: v) {
            min = std::get<col>(e) < min ? std::get<col>(e) : min;
        }

        return min;
    }

    template<typename T, int col>
    inline T max(const std::vector<std::tuple<T,T>> &v)
    {
        T max = std::numeric_limits<T>::min();

        for(const auto & e: v) {
            max = std::get<col>(e) > max ? std::get<col>(e) : max;
        }

        return max;
    }

    template<typename T, int col>
    inline T max(const std::vector<std::tuple<T,T,T>> &v)
    {
        T max = std::numeric_limits<T>::min();

        for(const auto & e: v) {
            max = std::get<col>(e) > max ? std::get<col>(e) : max;
        }

        return max;
    }

    template<typename T>
    inline T max(const std::vector<T> &v)
    {
        return *std::max_element(v.begin(), v.end());
    }

}

#endif