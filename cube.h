#define EPS 1e-4
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
static const struct color headerColors[6] = {frontColor,topColor,backColor,bottomColor,rightColor,leftColor};

static const struct coordinate middle = {heightCanvas/2,widthCanvas/2};
static const struct coordinate origin = {0,0};
static const struct coordinate point1 = {30,25,10};
