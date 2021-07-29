#include <iostream>
#include <math.h>
#include "geometricUtils.h"
#include "opticalMedia.h"
#include "light.h"

const int MEDIUM_REFRACTIVE_INDEX = 1;

float snellsLaw(LightRay &ray, Prism2D prism)
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
    
    float reverseNormalVectorAngleDegrees = addAnglesDregreesWrapAround(normalVectorAngleDegrees, 180);

    // finding the angle of incidence
    // float angleOfIncidence = std::abs(normalVectorAngleDegrees - ray.headingDegrees);
    float angleOfIncidenceDegrees = std::abs(
        normalVectorAngleDegrees - addAnglesDregreesWrapAround(ray.headingDegrees, 180)
    );

    // If we have identified we are meeting the prism on a certain side, but the angle of incidence
    // is greater than a right angle, we must be approaching the inside, therefore flip the normal
    // vector to the surface to the opposite direction.
    bool exitingMedium = false;
    if(angleOfIncidenceDegrees > 90.0 )
    {
        exitingMedium = true;
        
        float temp = normalVectorAngleDegrees;
        normalVectorAngleDegrees = reverseNormalVectorAngleDegrees;
        reverseNormalVectorAngleDegrees = temp;
        
        // recalculate angle of incidence based on the new normal vector.
        angleOfIncidenceDegrees = std::abs(
            normalVectorAngleDegrees - addAnglesDregreesWrapAround(ray.headingDegrees, 180)
        );
    }

    if(round(angleOfIncidenceDegrees) == 90.0)
    {
        // if angle of incidence rounds to 90 then it is the critical angle.
        // TODO.
    }

    // putting values into rearranged snells law to give angle or refraction (wrt vertical).
    // assuming we are going from MEDIUM to prism.
    // Converting from degrees to randians and back on the go.
    float angleOfRefractionDegrees = (
        radiansToDegrees(
            asin( ((float)MEDIUM_REFRACTIVE_INDEX/(float)prism.refractiveIndex) * sin(degreesToRadians(angleOfIncidenceDegrees)) )   
        ) 
    );

    float newRayHeadingDegrees;
    if(exitingMedium)
    {
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees > 0) 
        { 
            ray.headingDegrees = reverseNormalVectorAngleDegrees - angleOfRefractionDegrees;
            ray.headingRadians = degreesToRadians(ray.headingDegrees);
        }
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees < 0) 
        { 
            ray.headingDegrees = reverseNormalVectorAngleDegrees + angleOfRefractionDegrees;
            ray.headingRadians = degreesToRadians(ray.headingDegrees);
        }
    } 
    else
    {
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees > 0) 
        { 
            ray.headingDegrees = reverseNormalVectorAngleDegrees + angleOfRefractionDegrees;
            ray.headingRadians = degreesToRadians(ray.headingDegrees);
        }
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees < 0) 
        { 
            ray.headingDegrees = reverseNormalVectorAngleDegrees - angleOfRefractionDegrees;
            ray.headingRadians = degreesToRadians(ray.headingDegrees);
        }
    }

    std::cout << "Angle Refrac: " << angleOfRefractionDegrees << std::endl;
    std::cout << "Reverse Normal: " << reverseNormalVectorAngleDegrees << std::endl;

    return angleOfRefractionDegrees; //angleOfRefractionDegrees;
}