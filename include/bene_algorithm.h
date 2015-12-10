/*
Copyright Benedikt Bergenthal <b.bergenthal@cern.ch> 2015
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BENE_ALGORITHM
#define BENE_ALGORITHM
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TROOT.h"

namespace bene {

template <typename T>
inline T min(const std::vector<T>& v)
{
    return *std::min_element(v.begin(), v.end());
}

template <typename T, int col>
inline T min(const std::vector<std::tuple<T, T> >& v)
{
    T min = std::numeric_limits<T>::max();

    for (const auto& e : v) {
        min = std::get<col>(e) < min ? std::get<col>(e) : min;
    }

    return min;
}

template <typename T, int col>
inline T min(const std::vector<std::tuple<T, T, T> >& v)
{
    T min = std::numeric_limits<T>::max();

    for (const auto& e : v) {
        min = std::get<col>(e) < min ? std::get<col>(e) : min;
    }

    return min;
}

template <typename T, int col>
inline T max(const std::vector<std::tuple<T, T> >& v)
{
    T max = std::numeric_limits<T>::min();

    for (const auto& e : v) {
        max = std::get<col>(e) > max ? std::get<col>(e) : max;
    }

    return max;
}

template <typename T, int col>
inline T max(const std::vector<std::tuple<T, T, T> >& v)
{
    T max = std::numeric_limits<T>::min();

    for (const auto& e : v) {
        max = std::get<col>(e) > max ? std::get<col>(e) : max;
    }

    return max;
}

template <typename T>
inline T max(const std::vector<T>& v)
{
    return *std::max_element(v.begin(), v.end());
}
}

#endif