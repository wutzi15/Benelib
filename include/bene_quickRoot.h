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
#ifndef BENE_QUICKROOT
#define BENE_QUICKROOT
#include "bene_algorithm.h"
#include "boost/lexical_cast.hpp"
#include "bene_file.h"
#include "TCanvas.h"
#include <tuple>

namespace bene
{


    template<typename T, size_t X, size_t Y>
    TGraph quickTGraph(const std::vector<std::tuple<T,T>> & v)
    {
        static_assert(X >= 1, "X must be >= 1. We start counting at 1 for columns!");
        static_assert(Y >= 1, "Y must be >= 1. We start counting at 1 for columns!");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        TGraph g(num_elem);

        for (size_t i = 0; i < num_elem; ++i) {
            g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]));
        }

        return g;
    }

    template<typename T, size_t X, size_t Y>
    TGraph quickTGraph(const  std::vector<std::tuple<T,T,T>> & v)
    {
        static_assert(X >= 1, "X must be >= 1. We start counting at 1 for columns!");
        static_assert(Y >= 1, "Y must be >= 1. We start counting at 1 for columns!");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        TGraph g(num_elem);

        for (size_t i = 0; i < num_elem; ++i) {
            g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]) );
        }

        return g;
    }

    template<typename T, size_t X, size_t Y, size_t Err>
    TGraphErrors quickTGraphError(const  std::vector<std::tuple<T,T,T>> & v)
    {
        static_assert(X >= 1, "X must be >= 1. We start counting at 1 for columns!");
        static_assert(Y >= 1, "Y must be >= 1. We start counting at 1 for columns!");
        static_assert(Err >= 1, "Err must be >= 1. We start counting at 1 for columns!");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        TGraphErrors g(num_elem);

        for (size_t i = 0; i < num_elem; ++i) {
            g.SetPoint(i, std::get<X-1>(v[i]), std::get<Y-1>(v[i]) );
            g.SetPointError(i,0, std::get<Err-1>(v[i]));
        }

        return g;
    }

    template<typename T, size_t bins>
    TH1F quickHist(const std::vector<T> & v)
    {
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        double min_v = min(v);
        double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
        double max_v = max(v);
        double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
        TH1F h("", "", bins, min, max);

        for(const auto & e : v) {
            h.Fill(e);
        }
    }

    template<typename T, size_t bins, size_t col>
    TH1F quickHist(const std::vector<std::tuple<T,T>> & v)
    {
        static_assert(col >= 1, "col must be >= 1. We start counting at 1 for columns!");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        double min_v = min<T,col-1>(v);
        double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
        double max_v = max<T,col-1>(v);
        double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
        TH1F h("", "", bins, min, max);

        for(const auto & e : v) {
            h.Fill(std::get<col-1>(e));
        }

        return h;
    }

    template<typename T, size_t bins, size_t col>
    TH1F quickHist(const std::vector<std::tuple<T,T,T>> & v)
    {
        static_assert(col >= 1, "col must be >= 1. We start counting at 1 for columns!");
        static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "vector type must be interger or float");
        const size_t num_elem = v.size();
        double min_v = min<T,col-1>(v);
        double min = min_v < 0 ? min_v * 1.1 : min_v * 0.9;
        double max_v = max<T,col-1>(v);
        double max = max_v < 0 ? max_v * 0.9 : max_v * 1.1;
        TH1F h("", "", bins, min, max);

        for(const auto & e : v) {
            h.Fill(std::get<col-1>(e));
        }

        return h;
    }

    template<size_t deg>
    TGraphErrors fit(TGraphErrors &g)
    {
        g.Fit(("pol"+boost::lexical_cast<std::string>(deg)).c_str(),"EMFSQ");
        g.Draw("AL");
    }

    template<size_t deg>
    TGraph fit(TGraph &g)
    {
        g.Fit(("pol"+boost::lexical_cast<std::string>(deg)).c_str(),"EMFSQ");
        g.Draw("AL");
    }

    template<size_t deg>
    TH1F fit(TH1F &g)
    {
        g.Fit(("pol"+boost::lexical_cast<std::string>(deg)).c_str(),"EMFSQ");
        g.Draw();
    }

    TGraphErrors fit(TGraphErrors &g);
    TGraph fit(TGraph &g);
    TH1F fit(TH1F &g);

}
#endif