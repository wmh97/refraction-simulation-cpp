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

    Prism2D prism(250, 300, 50, 2);
    std::cout << prism;
    LightRay ray(0, 275, 90, 666);
    std::cout << ray;
    
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
    std::cout << ray;

    // set refracted ray heading
    float angleOfRefractionDegrees = snellsLaw(ray, prism);

    std::cout << ray;

    return 0;
}