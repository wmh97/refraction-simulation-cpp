#ifndef LIGHT_H
#define LIGHT_H

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

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

    LightRay(int x, int y, int thetaDegrees, int lambda);

    void propogate();

    void propogateToEnd();

    friend std::ostream& operator << (std::ostream& output, const LightRay ray);
};

#endif