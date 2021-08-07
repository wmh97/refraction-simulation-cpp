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

int main()
{

    Prism2D prism(250, 300, 50, 1.33);
    std::cout << prism;
    LightRay ray(0, 275, 90, 666);
    std::cout << ray;
    prism.outputCoordinates();
    ray.outputCoordinates();

    bool rayInPrism = false;
    while(!rayInPrism)
    {
        rayInPrism = posIsInTriangle(
            prism.leftBaseXPos, prism.baseYPos,
            prism.tipXPos, prism.tipYPos,
            prism.rightBaseXPos, prism.baseYPos,
            ray.rayHeadXPos, ray.rayHeadYPos
        );
        ray.propogate();
    }
    snellsLaw(ray, prism);
    std::cout << ray;
    ray.outputCoordinates();

    while(rayInPrism)
    {
        rayInPrism = posIsInTriangle(
            prism.leftBaseXPos, prism.baseYPos,
            prism.tipXPos, prism.tipYPos,
            prism.rightBaseXPos, prism.baseYPos,
            ray.rayHeadXPos, ray.rayHeadYPos
        );
        ray.propogate();
    }
    snellsLaw(ray, prism);
    std::cout << ray;
    ray.outputCoordinates();

    ray.propogateToEnd();
    std::cout <<"END:" << std::endl;
    std::cout << ray;
    ray.outputCoordinates();
    

    return 0;
}