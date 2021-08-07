#include <iostream>
#include <fstream>
#include "math.h"
#include "light.h"
#include "geometricUtils.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

LightRay::LightRay(int x, int y, int thetaDegrees, int lambda)
{
    // To simplify things, accept only L-->R direction
    if (thetaDegrees < 0 || thetaDegrees > 180) throw;     
    
    startXPos = x;
    startYPos = y;
    rayHeadXPos = x;
    rayHeadYPos = y;

    wavelenghth = lambda;
    
    // will sign of dx and dy be correct for all angles?
    this->setNewHeading(thetaDegrees);

}

void LightRay::setNewHeading(float newHeadingDegrees)
{
    headingDegrees = newHeadingDegrees;
    headingRadians = degreesToRadians(newHeadingDegrees);
    dx = sin(headingRadians);
    dy = cos(headingRadians);
}

void LightRay::propogate()
{
    if(
        0 <= rayHeadXPos && rayHeadXPos <= WINDOW_WIDTH 
        && 
        0 <= rayHeadYPos && rayHeadYPos <= WINDOW_HEIGHT
    ){
        rayHeadXPos = rayHeadXPos + dx;
        rayHeadYPos = rayHeadYPos + dy;
    }         
}

void LightRay::propogateToEnd()
{
    while(
        0 <= rayHeadXPos && rayHeadXPos <= WINDOW_WIDTH 
        && 
        0 <= rayHeadYPos && rayHeadYPos <= WINDOW_HEIGHT
    ){
        rayHeadXPos = rayHeadXPos + dx;
        rayHeadYPos = rayHeadYPos + dy;
    } 
}

void LightRay::outputCoordinates()
{
    std::ofstream outputFile("RayCoordinates.txt", std::ios::app);
    if(outputFile.is_open())
    {
        outputFile << rayHeadXPos << "," << rayHeadYPos << std::endl;
    }
    else
    {
        std::cout << "Output file could not be opened!" << std::endl;
    }
}

std::ostream& operator << (std::ostream& output, const LightRay ray)
{
    output << std::endl;
    output << "Light Ray: " << std::endl;
    output << "startX: " << ray.startXPos << std::endl;
    output << "startY: " << ray.startYPos << std::endl;
    output << "currentX: " << ray.rayHeadXPos << std::endl;
    output << "currentY: " << ray.rayHeadYPos << std::endl;
    output << "Ray Heading (Deg): " << ray.headingDegrees << std::endl;
    output << "Ray Heading (Rad): " << ray.headingRadians << std::endl;
    output << "dx: " << ray.dx << std::endl;
    output << "dy: " << ray.dy << std::endl << std::endl;
    return output;   
}