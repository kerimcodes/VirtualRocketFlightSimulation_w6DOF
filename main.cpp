#include "DataPipeline.h"
#include <iostream>

int main() 
{   
    try
    {
        double dt = 0.01;
        startSimulation(dt);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}