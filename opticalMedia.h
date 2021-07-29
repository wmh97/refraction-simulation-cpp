#ifndef OPTICAL_MEDIA_H
#define OPTICAL_MEDIA_H

class Medium
{
public:
    float refractiveIndex;
};

class Prism2D : public Medium
{
public:
 
    float tipXPos, tipYPos;
    float leftBaseXPos, rightBaseXPos;
    float baseYPos;

    float leftSideXMidPoint;
    float leftSideYMidPoint;
    float leftSideNormalVectorAngleDegrees;
    
    float rightSideXMidPoint;
    float rightSideYMidPoint;
    float rightSideNormalVectorAngleDegrees;

    float baseXMidPoint;
    float baseYMidPoint;
    float baseNormalVectorAngleDegrees;

    int triangeHeight;
    
    Prism2D(int x, int y, int h, float n);

    // although friend function is not a member function it can
    // still be defined in the class scope.
    friend std::ostream& operator << (std::ostream& output, const Prism2D prism);
};

#endif