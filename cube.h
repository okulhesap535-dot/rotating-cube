#define EPS 1e-4
#include <math.h>
const int heightCanvas = 50;
const int widthCanvas = 50;;
const char luminosity[] = ".,-~:;=!*#$@";

struct coordinate
{
    double x;
    double y;
    double z;
};
struct color
{
    int r;
    int g;
    int b;
};
static const struct color frontColor = { 255, 0, 0 }; //Red
static const struct color backColor = { 74, 14, 237 }; //Purple
static const struct color topColor = {36, 92, 27}; //Green
static const struct color bottomColor = { 235, 152, 213 }; //Pink
static const struct color leftColor = { 24, 159, 163 }; //Cyan
static const struct color rightColor= { 199, 81, 22 }; //Orange
static const struct color headerColors[6] = {frontColor,leftColor,topColor,bottomColor,rightColor,backColor};

static const struct coordinate middle = {heightCanvas/2,widthCanvas/2};
static const struct coordinate origin = {0,0};
static const struct coordinate point1 = {30,25,10};

//[i][0] is xangle of the i. face, [i][1] is zangle. Put the opposite angles in so we don2t have to inverse them again
static const double faces[6][2] = {
    {  0.0,          0.0          }, // front  (+Z)
    {  0.0,  +M_PI_2               }, // left   (-X)
    { -M_PI_2,       0.0          }, // top    (+Y)
    { +M_PI_2,       0.0          }, // bottom (-Y)
    {  0.0,  -M_PI_2               }, // right  (+X)
    {  0.0,        M_PI           }  // back   (-Z)
};