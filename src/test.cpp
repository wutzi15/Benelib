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


int main(int argc, char const *argv[])
{
	/*std::tuple<int, long> t1{ 1, 2 };
    std::tuple<> t2;
    std::tuple<float, double, long double> t3{ 3, 4, 5 };
    std::pair<void const*, char const*> t4{ "pv", "test" };

    using expected = std::tuple<int, long, float, double, long double,
        void const*, char const*>;

    auto result = ::tuple_cat( t1, t2, t3, t4 );

    static_assert( std::is_same<decltype(result), expected>::value, "" );

    print_tuple( result );*/
    bene::plotTGraphErrorsFromFile(argv[1]);
    return 0;
}