#include <iostream>
#include <fstream>
#include "opticalMedia.h"
#include "geometricUtils.h"

    
Prism2D::Prism2D(int x, int y, int h, float n)
{
    tipXPos = x;
    tipYPos = y;
    refractiveIndex = n;
    triangeHeight = h;

    leftBaseXPos = tipXPos-triangeHeight/2;
    rightBaseXPos = tipXPos+triangeHeight/2;
    baseYPos = tipYPos-triangeHeight;

    // midpoint coordinates of sides will be used to find the side
    // of the prism the ray is incident on.
    leftSideXMidPoint = midpointBetweenCoords(leftBaseXPos, tipXPos);
    leftSideYMidPoint = midpointBetweenCoords(baseYPos, tipYPos);
    rightSideXMidPoint = midpointBetweenCoords(rightBaseXPos, tipXPos);
    rightSideYMidPoint = midpointBetweenCoords(baseYPos, tipYPos);
    baseXMidPoint = midpointBetweenCoords(leftBaseXPos, rightBaseXPos);
    baseYMidPoint = midpointBetweenCoords(baseYPos, baseYPos);

    // We know these to start with as we know the orientation we are creating
    // the prism in our space. If we need to we can adjust these when the
    // prism rotates.
    leftSideNormalVectorAngleDegrees = 300.0;
    rightSideNormalVectorAngleDegrees = 60.0;
    baseNormalVectorAngleDegrees = 180.0;
}

void Prism2D::outputCoordinates()
{
    std::ofstream outputFile("PrismCoordinates.txt", std::ios::app);
    if(outputFile.is_open())
    {
        outputFile << leftBaseXPos << "," << baseYPos << std::endl;
        outputFile << rightBaseXPos << "," << baseYPos << std::endl;
        outputFile << tipXPos << "," << tipYPos << std::endl;
    }
    else
    {
        std::cout << "Output file could not be opened!" << std::endl;
    }
}

// friend function is defined as a non member function. The function is really acting
// on the ostream class.
std::ostream& operator << (std::ostream& output, const Prism2D prism)
{
    output << std::endl;
    output << "Prism Coordinates:" << std::endl;
    output << prism.tipXPos << "," << prism.tipYPos << std::endl;
    output << prism.leftBaseXPos << "," << prism.baseYPos << std::endl;
    output << prism.rightBaseXPos << "," << prism.baseYPos << std::endl;
    output << "Prism Height: " << prism.triangeHeight << std::endl;
    output << "Prism Refractive Index: " << prism.triangeHeight << std::endl << std::endl;
    return output;
}