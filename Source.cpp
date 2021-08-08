#include <iostream>
#include <math.h>
#include "opticalMedia.h"
#include "geometricUtils.h"
#include "light.h"
#include "opticalFormulae.h"

// int WINDOW_WIDTH = 500;
// int WINDOW_HEIGHT = 500;
//int MEDIUM_REFRACTIVE_INDEX = 1;
float PI = 3.14159;

bool rayIsInPrism(LightRay ray, Prism2D prism)
{
    return posIsInTriangle(
                prism.leftBaseXPos, prism.baseYPos,
                prism.tipXPos, prism.tipYPos,
                prism.rightBaseXPos, prism.baseYPos,
                ray.rayHeadXPos, ray.rayHeadYPos
    );    
}

void runSimulation(LightRay ray, Prism2D prism)
{
    std::cout << prism;
    std::cout << ray;
    prism.outputCoordinates();
    ray.outputCoordinates();

    bool lastRayPositionInPrism = false;
    bool exitingPrism = false;
    while(
            posIsInScreen(ray.rayHeadXPos, ray.rayHeadYPos)
    ){
        bool rayInPrism = false;
        rayInPrism = rayIsInPrism(ray, prism);
        ray.propogate();

        if(lastRayPositionInPrism != rayInPrism)
        {
            if(lastRayPositionInPrism)
            {
                exitingPrism = true;
            }
            else
            {
                exitingPrism = false;
            }
            lastRayPositionInPrism = rayInPrism;

            snellsLaw(ray, prism, exitingPrism);
            std::cout << ray;
            ray.outputCoordinates();
        }
    }

    std::cout <<"END:" << std::endl;
    std::cout << ray;
    ray.outputCoordinates();    
}

int main()
{

    Prism2D prism(250, 300, 50, 1.33);
    LightRay ray(240, 350, 180, 666);

    runSimulation(ray, prism);

    return 0;
}