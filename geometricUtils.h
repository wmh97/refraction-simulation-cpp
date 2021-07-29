#ifndef GEOMETRIC_UTILS
#define GEOMETRIC_UTILS

float midpointBetweenCoords(float coord1, float coord2);
float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2);
bool posIsInTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py);
float addAnglesDregreesWrapAround(float a1, float a2);
float degreesToRadians(float deg);
float radiansToDegrees(float rad);

#endif