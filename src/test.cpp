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
#include "bene.h"
#include <iostream>
#include "TCanvas.h"

int main(int argc, char const *argv[])
{
	auto v = bene::readToVector<double,3,1,2,3>(argv[1]);
    auto g = bene::quickTGraphError<double, 1,2,3>(v);
    bene::fit<1>(g);
    return 0;
}