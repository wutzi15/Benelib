#ifndef BENE_FILE
#define BENE_FILE
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <type_traits>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TROOT.h"

namespace bene
{
    template<typename T, size_t cols, size_t X, size_t Y, size_t Err>
    std::vector<std::tuple<T, T, T>> readToVector(const std::string & s)
    {
        static_assert(X <= cols, "X value must be < cols");
        static_assert(Y <= cols, "Y value must be < cols");
        static_assert(Err <= cols, "Y value must be < cols");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        std::ifstream in(s);
        std::string line;
        std::vector<std::tuple<T, T, T>> values;

        while(std::getline(in, line)) {
            std::stringstream sstr;
            sstr << line;
            std::array<T, cols> ary;

            for(size_t i = 0; i < cols; i++) {
                sstr >> ary[i];
            }

            values.push_back(std::make_tuple(ary[X-1], ary[Y-1], ary[Err-1]));
        }

        return values;
    }

    template<typename T, int cols, int X, int Y>
    std::vector<std::tuple<T, T>> readToVector(const std::string & s)
    {
        static_assert(X <= cols, "X value must be < cols");
        static_assert(Y <= cols, "Y value must be < cols");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        std::ifstream in(s);
        std::string line;
        std::vector<std::tuple<T, T>> values;

        while(std::getline(in, line)) {
            std::stringstream sstr;
            sstr << line;
            std::array<T, cols> ary;

            for(size_t i = 0; i < cols; i++) {
                sstr >> ary[i];
            }

            values.push_back(std::make_tuple(ary[X-1], ary[Y-1]));
        }

        return values;
    }

    TH1F plotHistFromFile(const std::string & s);
    TGraph plotTGraphFromFile(const std::string & s);
    TGraphErrors plotTGraphErrorsFromFile(const std::string & s);
}

#endif