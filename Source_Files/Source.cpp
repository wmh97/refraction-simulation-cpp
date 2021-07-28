#include <iostream>
#include <math.h>

int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;
int MEDIUM_REFRACTIVE_INDEX = 1;
float PI = 3.14159;

class Prism2D
{
public:
 
    float tipXPos, tipYPos, refractiveIndex;
    float leftBaseXPos, rightBaseXPos;
    float baseYPos;

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

    float startXPos, startYPos;
    float rayHeadXPos, rayHeadYPos;
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
        rayHeadXPos = x;
        rayHeadYPos = y;

        wavelenghth = lambda;
        
        // will sign of dx and dy be correct for all angles?
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
        output << "********** Light Ray **********: " << std::endl;
        output << "startX: " << ray.startXPos << std::endl;
        output << "startY: " << ray.startYPos << std::endl;
        output << "currentX: " << ray.rayHeadXPos << std::endl;
        output << "currentY: " << ray.rayHeadYPos << std::endl;
        output << "Ray Heading: " << ray.headingRadians << std::endl;
        output << "dx: " << ray.dx << std::endl;
        output << "dy: " << ray.dy << std::endl << std::endl;
        return output;   
    }
};

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
    */
    
    // float w1 = ((Ax*(Cy-Ay))+((Py-Ay)*(Cx-Ax))-(Px*(Cy-Ay))) / (((By-Ay)*(Cx-Ax)) - ((Bx-Ax)*(Cy-Ay)));
    // float w2 = (Py-Ay-(w1*(By-Ay))) / (Cy-Ay);
    // When we take into account the fact that Ay==Cy in our case (equilateral triangle)
    // the above w1 and w2 expressions can be derived as:
    double w1 = (Py-Ay)/(By-Ay);
    double w2 = ((Px-Ax)/(Cx-Ax))-(((Py-Ay)*(Bx-Ax))/((By-Ay)*(Cx-Ax)));

    std::cout << "w1: " << w1 << " w2: " << w2 << std::endl;

    if (0 <= w1 && 0 <= w2 && (w1+w2) <= 1)
    {
        return true;
    }
    return false;
}

int main()
{

    Prism2D prism(250, 300, 50, 2);
    std::cout << prism;
    
    LightRay ray(250, 301, 90, 666);
    bool flag = posIsInTriangle(
                    prism.leftBaseXPos, prism.baseYPos,
                    prism.tipXPos, prism.tipYPos,
                    prism.rightBaseXPos, prism.baseYPos,
                    ray.rayHeadXPos, ray.rayHeadYPos
    );
    std::cout << "Pos is in Triangle: " << flag << std::endl;


    return 0;
}