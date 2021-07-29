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

        //std::cout << "distances[i]: " << distances[i] << std::endl;
        //std::cout << "shortest: " << shortestDistance <<std::endl;
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

        std::cout << "Angle of incidence: " << angleOfIncidenceDegrees << std::endl;
    }

    if(round(angleOfIncidenceDegrees) == 90.0)
    {
        // if angle of incidence rounds to 90 then it is the critical angle.
        // TODO.
    }

    /*
        NOTE: Our formula seems to break down at the point of exiting the medium for refractive index
              of that medium of at least n=>2 - We get 'nan'. With n=1.33 for glass we get the expected
              direction of diversion of the ray, but this needs testing.

        ************************************************************************************************
        ALSO not sure of the conditions below... it seems they are the same here, but actually depend on direction
        of travel (L->R vs R->L) instead. That is, while the prism is oriented point up. We may actually need to
        depend these conditions upon the gradient of the sides of the prism (+ve/-ve) instead as this may be what
        gives any difference in LR/RL behaviour
        ************************************************************************************************
    */

    float angleOfRefractionDegrees;
    if(exitingMedium)
    {

        // putting values into rearranged snells law to give angle or refraction (wrt vertical).
        // assuming we are going from MEDIUM to prism.
        // Converting from degrees to randians and back on the go.
        angleOfRefractionDegrees = (
            radiansToDegrees(
                asin( ((float)prism.refractiveIndex/(float)MEDIUM_REFRACTIVE_INDEX) * sin(degreesToRadians(angleOfIncidenceDegrees)) )   
            )
        );

        // on exit, bend ray away from the normal to the outside of the medium

        // if the normal on exit is greater
        if(ray.headingDegrees < reverseNormalVectorAngleDegrees) 
        { 
            ray.setNewHeading(reverseNormalVectorAngleDegrees - angleOfRefractionDegrees);
        }
        if(ray.headingDegrees > reverseNormalVectorAngleDegrees) 
        {   
            ray.setNewHeading(reverseNormalVectorAngleDegrees + angleOfRefractionDegrees);
        }

        std::cout << "EXITING PRISM" << std::endl;
    } 
    else
    {
        // putting values into rearranged snells law to give angle or refraction (wrt vertical).
        // assuming we are going from MEDIUM to prism.
        // Converting from degrees to randians and back on the go.
        angleOfRefractionDegrees = (
            radiansToDegrees(
                asin( ((float)MEDIUM_REFRACTIVE_INDEX/(float)prism.refractiveIndex) * sin(degreesToRadians(angleOfIncidenceDegrees)) )   
            ) 
        );        
        
        // on entry, bend ray towards normal on the inside of the medium.
        
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees > 0) 
        { 
            ray.setNewHeading(reverseNormalVectorAngleDegrees - angleOfRefractionDegrees);
        }
        if(reverseNormalVectorAngleDegrees - ray.headingDegrees < 0) 
        { 
            ray.setNewHeading(reverseNormalVectorAngleDegrees + angleOfRefractionDegrees);
        }

        std::cout << "ENTERING PRISM" << std::endl;
    }

    std::cout << "Angle Refrac: " << angleOfRefractionDegrees << std::endl;
    std::cout << "Reverse Normal: " << reverseNormalVectorAngleDegrees << std::endl;

    return angleOfRefractionDegrees; //angleOfRefractionDegrees;
}