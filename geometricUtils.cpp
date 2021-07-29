#include <iostream>
#include <math.h>
#include "geometricUtils.h"

float midpointBetweenCoords(float coord1, float coord2)
{
    return (coord1 + coord2)/2;
}

float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2)
{
    float dx = abs(x1-x2);
    float dy = abs(y1-y2);
    return pow(((dx*dx) + (dy*dy)), 0.5);
}

bool posIsInTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py)
{
    /*
        Calculating if the position P is in the triangle ABC by the use of vector
        coordinates representing the position of P relative to A, and the weights
        w1 and w2 which represent the distance along lines AB and AC.

        The further P is from A the larger these vectors and hence the large the
        weights w1 and w2. P can be written in terms of A,B,C,w1,w2. This splits
        into two eqns Px and Py with two unknowns w1 and w2, which can be
        solved for.

        When we take into account the fact that Ay==Cy in our case (equilateral triangle)
        w1 and w2 expressions can be derived as:
    */

    double w1 = (Py-Ay)/(By-Ay);
    double w2 = ((Px-Ax)/(Cx-Ax))-(((Py-Ay)*(Bx-Ax))/((By-Ay)*(Cx-Ax)));

    //std::cout << "w1: " << w1 << " w2: " << w2 << std::endl;

    if (0 <= w1 && 0 <= w2 && (w1+w2) <= 1)
    {
        return true;
    }
    return false;
}

float addAnglesDregreesWrapAround(float a1, float a2)
{
    /*
        Simply adds two angles together, but makes sure that if it goes over
        360deg, it wraps around to start from 0deg again.;
    */

    float addedAngle = a1 + a2;
    if (addedAngle > 360)
    {
        return addedAngle - 360;
    }
    return addedAngle;
    
}

float degreesToRadians(float deg)
{
    return deg * (3.14159 / 180.0);
}

float radiansToDegrees(float rad)
{
    return rad * (180.0 / 3.14159);
}