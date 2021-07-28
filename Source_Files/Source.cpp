#include <iostream>
#include <math.h>

int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;
int MEDIUM_REFRACTIVE_INDEX = 1;
float PI = 3.14159;

class Prism2D
{
public:

    int tipXPos, tipYPos, refractiveIndex;
    int leftBaseXPos, rightBaseXPos;
    int baseYPos;

    int triangeHeight;
    
    Prism2D(int x, int y, int h, int n)
    {
        tipXPos = x;
        tipYPos = y;
        refractiveIndex = n;
        triangeHeight = h;

        leftBaseXPos = tipXPos-triangeHeight/2;
        rightBaseXPos = tipXPos+triangeHeight/2;
        baseYPos = tipYPos-triangeHeight;
    }

    // although friend function is not a member function it can
    // still be defined in the class scope.
    // Need to define as friend function as the operator is really acting on the
    // ostream class.
    friend std::ostream& operator << (std::ostream& output, const Prism2D prism)
    {
        output << std::endl;
        output << "********** Prism Coordinates: **********" << std::endl;
        output << prism.tipXPos << "," << prism.tipYPos << std::endl;
        output << prism.leftBaseXPos << "," << prism.baseYPos << std::endl;
        output << prism.rightBaseXPos << "," << prism.baseYPos << std::endl;
        output << "Prism Height: " << prism.triangeHeight << std::endl;
        output << "Prism Refractive Index: " << prism.triangeHeight << std::endl << std::endl;
        return output;
    }
};

class LightRay
{
public:

    int startXPos, startYPos;
    int wavelenghth;

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
        wavelenghth = lambda;
        
        // will sign of dx and dy be correct for all angles?
        headingRadians = (float) thetaDegrees * (PI/180);
        dx = sin(headingRadians);
        dy = cos(headingRadians);

    }

    void propogate()
    {
        // if we are within the window
        if(0 < startXPos < WINDOW_WIDTH-abs(dx) && 0 < startYPos < WINDOW_HEIGHT-abs(dy))
        {
            startXPos = (float) startXPos + dx;
            startYPos = (float) startYPos + dy;
        }
    }

    friend std::ostream& operator << (std::ostream& output, const LightRay ray)
    {
        output << std::endl;
        output << "********** Light Ray **********: " << std::endl;
        output << "X: " << ray.startXPos << std::endl;
        output << "Y: " << ray.startYPos << std::endl;
        output << "Ray Heading: " << ray.headingRadians << std::endl;
        output << "dx: " << ray.dx << std::endl;
        output << "dy: " << ray.dy << std::endl << std::endl;
        return output;   
    }
};

int main()
{
    // Window dimensions
    int Width = 500;
    int Height = 500;

    Prism2D prism(250, 300, 50, 2);
    LightRay ray(0, 300, 90, 666);

    std::cout << prism;

    ray.propogate();
    std::cout << ray;
    ray.propogate();

    return 0;
}