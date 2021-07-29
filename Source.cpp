#include <iostream>
#include <math.h>
#include "opticalMedia.h"
#include "geometricUtils.h"

int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;
int MEDIUM_REFRACTIVE_INDEX = 1;
float PI = 3.14159;

class LightRay
{
public:

    float startXPos, startYPos;
    float rayHeadXPos, rayHeadYPos;
    int wavelenghth;

    float headingDegrees;
    float headingRadians = 0.0f;

    // incremental change in x and y for a unit vector at
    // angle 'headingRadians' from vertical.
    float dx = 0.0f;
    float dy = 0.0f;

    LightRay(int x, int y, int thetaDegrees, int lambda)
    {
        // To simplify things, accept only L-->R direction
        if (thetaDegrees < 0 || thetaDegrees > 180) throw;     
        
        startXPos = x;
        startYPos = y;
        rayHeadXPos = x;
        rayHeadYPos = y;

        wavelenghth = lambda;
        
        // will sign of dx and dy be correct for all angles?
        headingDegrees = thetaDegrees;
        headingRadians = (float) thetaDegrees * (PI/180);
        dx = sin(headingRadians);
        dy = cos(headingRadians);

    }

    void propogate()
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

    void propogateToEnd()
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

    friend std::ostream& operator << (std::ostream& output, const LightRay ray)
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
};

float snellsLaw(LightRay ray, Prism2D prism)
{
    /*
        Light travels from medium1 to medium2:
        n1 = refractive index of medium 1
        n2 = refractive index of medium 2
        theta1 = angle of incident light wrt normal to boundary
        theta2 = angle of refracted light wrt normal to boundary

        Calculating the side we hit the prism on by seeing which midpoint is closest to the
        ray and using the pre-calculated value for its normal vector angle to calculate the angle
        of incidence. NOTE this will need to be tested close to corners of the prism.
    */

    float distances[3] = {
        distanceBetweenTwoPoints(ray.rayHeadXPos, ray.rayHeadYPos, prism.leftSideXMidPoint, prism.leftSideYMidPoint),
        distanceBetweenTwoPoints(ray.rayHeadXPos, ray.rayHeadYPos, prism.rightSideXMidPoint, prism.rightSideYMidPoint),
        distanceBetweenTwoPoints(ray.rayHeadXPos, ray.rayHeadYPos, prism.baseXMidPoint, prism.baseYMidPoint)
    };

    float shortestDistance = -1.0f;
    std::cout << "uninitialised: " << shortestDistance << std::endl;
    for (int i = 0; i < 3; i++)
    {
        if (shortestDistance == -1.0)
        {
            shortestDistance = distances[i];
        }
        else if (shortestDistance)
        {
            if(distances[i] < shortestDistance)
            {
                shortestDistance = distances[i];
            }
        }

        std::cout << "distances[i]: " << distances[i] << std::endl;
        std::cout << "shortest: " << shortestDistance <<std::endl;
    }

    // finding the angle from vertical the normal to the surface is.
    float normalVectorAngleDegrees;
    if (shortestDistance == distances[0]) normalVectorAngleDegrees = prism.leftSideNormalVectorAngleDegrees;
    if (shortestDistance == distances[1]) normalVectorAngleDegrees = prism.rightSideNormalVectorAngleDegrees;
    if (shortestDistance == distances[2]) normalVectorAngleDegrees = prism.baseNormalVectorAngleDegrees;

    // finding the angle of incidence
    //float angleOfIncidence = std::abs(normalVectorAngleDegrees - ray.headingDegrees);
    float angleOfIncidence = std::abs(
        normalVectorAngleDegrees - addAnglesDregreesWrapAround(ray.headingDegrees, 180)
    );

    // putting values into rearranged snells law to give angle or refraction (wrt vertical).
    // assuming we are going from MEDIUM to prism.
    // Converting from degrees to randians and back on the go.
    float angleOfRefraction = (
        (   asin( ((float)MEDIUM_REFRACTIVE_INDEX/(float)prism.refractiveIndex) * sin(angleOfIncidence * (PI/180.0)) )   ) 
        * (180.0/PI)
    );

    return angleOfRefraction; //angleOfRefractionDegrees;
}

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
    ray.headingDegrees = angleOfRefractionDegrees;
    ray.headingRadians = angleOfRefractionDegrees * (PI/180);

    std::cout << ray;

    return 0;
}