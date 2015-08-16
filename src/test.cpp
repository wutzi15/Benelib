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
#include <thread>


struct Hello
{
    Hello(){std::cout << "Hello!\n";};
    ~Hello(){std::cout << "Goodbye!\n";};    
};

void run()
{
    Hello& hello = bene::Singleton<Hello>::instance();
    Hello& hello2 = bene::Singleton<Hello>::instance();
    std::cout << "Thread 2: " << &hello << " : " << &hello2 << std::endl;
}

int main(int argc, char const *argv[])
{
	std::cout <<"Beginning of main\n";
    std::thread thread = std::thread(&run);
    Hello& hello = bene::Singleton<Hello>::instance();
    Hello& hello2 = bene::Singleton<Hello>::instance();
    std::cout << "Thread 1: " << &hello << " : " << &hello2 << std::endl;
    thread.join();
    return 0;
}