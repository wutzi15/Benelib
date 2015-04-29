#include "bene.h"
#include <iostream>
#include "TCanvas.h"

int main(int argc, char const *argv[])
{
    auto v = bene::readToVector<double, 3,1,2,3>(argv[1]);
    return 0;
}