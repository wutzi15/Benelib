#include "bene.h"
#include <iostream>
#include "TCanvas.h"

int main(int argc, char const *argv[])
{
    bene::plotHistFromFile(argv[1]);
    return 0;
}