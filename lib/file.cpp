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
#include "bene_file.h"
#include "bene_quickRoot.h"
#include "TCanvas.h"
#include "boost/filesystem.hpp"

TH1F bene::plotHistFromFile(const std::string & s)
{
    if(!boost::filesystem::exists(boost::filesystem::path(s))) {
        std::cerr <<  __PRETTY_FUNCTION__ << std::endl;
        std::cerr << "File to open (" << s << ") does not exist\n";
        return TH1F();
    }
    auto v = bene::readToVector<double, 3, 1, 2>(s);
    auto h = bene::quickHist<double, 100,2>(v);
    TCanvas c("","", 500, 500);
    h.Draw();
    c.Print((s+".pdf").c_str());
}

TGraph bene::plotTGraphFromFile(const std::string & s)
{
    if(!boost::filesystem::exists(boost::filesystem::path(s))) {
        std::cerr <<  __PRETTY_FUNCTION__ << std::endl;
        std::cerr << "File to open (" << s << ") does not exist\n";
        return TGraph();
    }
    auto v = bene::readToVector<double, 3, 1, 2>(s);
    auto g = bene::quickTGraph<double, 1,2>(v);
    TCanvas c("","", 500, 500);
    g.Draw("AL");
    c.Print((s+".pdf").c_str());
}

TGraphErrors bene::plotTGraphErrorsFromFile(const std::string & s)
{
    if(!boost::filesystem::exists(boost::filesystem::path(s))) {
        std::cerr <<  __PRETTY_FUNCTION__ << std::endl;
        std::cerr << "File to open (" << s << ") does not exist\n";
        return TGraphErrors();
    }
    auto v = bene::readToVector<double, 3, 1, 2,3>(s);
    auto g = bene::quickTGraphError<double, 1,2,3>(v);
    TCanvas c("","", 500, 500);
    g.Draw("AL");
    c.Print((s+".pdf").c_str());
}