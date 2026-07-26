#include "DataPipeline.h"
#include <iostream>

int main() 
{   
    try
    {
        double dt = 0.01;
        int loop = 1000;
        createData(dt,loop);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}