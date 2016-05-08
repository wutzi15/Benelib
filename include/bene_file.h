#pragma once
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
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
#include <iostream>
#include <limits>
#include <type_traits>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TROOT.h"

namespace bene {
template <typename T, size_t cols, size_t X, size_t Y, size_t Err>
std::vector<std::tuple<T, T, T> > readToVector(const std::string& s)
{
    static_assert(X <= cols, "X value must be < cols");
    static_assert(Y <= cols, "Y value must be < cols");
    static_assert(Err <= cols, "Y value must be < cols");
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
    std::ifstream in(s);
    std::string line;
    std::vector<std::tuple<T, T, T> > values;

    while (std::getline(in, line)) {
        std::stringstream sstr;
        sstr << line;
        std::array<T, cols> ary;

        for (size_t i = 0; i < cols; i++) {
            sstr >> ary[i];
        }

        values.push_back(std::make_tuple(ary[X - 1], ary[Y - 1], ary[Err - 1]));
    }

    return values;
}

template <typename T, size_t cols, size_t X, size_t Y>
std::vector<std::tuple<T, T> > readToVector(const std::string& s)
{
    static_assert(X <= cols, "X value must be < cols");
    static_assert(Y <= cols, "Y value must be < cols");
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
    std::ifstream in(s);
    std::string line;
    std::vector<std::tuple<T, T> > values;

    while (std::getline(in, line)) {
        std::stringstream sstr;
        sstr << line;
        std::array<T, cols> ary;

        for (size_t i = 0; i < cols; i++) {
            sstr >> ary[i];
        }

        values.push_back(std::make_tuple(ary[X - 1], ary[Y - 1]));
    }

    return values;
}

TH1F plotHistFromFile(const std::string& s);
TGraph plotTGraphFromFile(const std::string& s);
TGraphErrors plotTGraphErrorsFromFile(const std::string& s);
}
