#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "cube.h"


int printCube(const struct coordinate cubePosition, const int radius, const double zAngle,const double yAngle, const double xAngle, const struct color *colors)
{
   const double cosz = cos(zAngle);
   const double sinz = sin(zAngle);
   const double cosx = cos(xAngle);
   const double sinx = sin(xAngle);
   const double sinxDividedbyCosx = sinx/cosx;
   for(int y =0; y<heightCanvas; y++)
   {
    for(int x = 0; x<widthCanvas; x++){
     //Transform so the cube position is the origin now
     int tx = x - cubePosition.x;
     int ty = y - cubePosition.y;
     //Rotate z axis
     double nx = tx*cosz - ty*sinz;
     double ny = tx*sinz + ty*cosz;
     
     //Find the z value where after the rotation it lands on the screen
     double tz = (radius-y*sinx)/cosx;
     ny =ny*cosx -(radius-ny*sinx)*sinxDividedbyCosx;
     struct color pointColor = colors[0];
     if(fabs(nx)<radius+EPS && fabs(ny)<radius+EPS)
      {
       printf("\033[38;2;%d;%d;%dm@@\033[0m",pointColor.r,pointColor.g,pointColor.b);
      }
     else{
        printf("  ");
      }
    }
    printf("\n");
   }
   return 0;
}

void rotatingCube(const struct coordinate cubePosition, const int radius, const struct color *colors){
    struct timespec remaining, request = { 0, 200000000 };
    int i = 0;
    while(1){
      printCube(cubePosition, radius, 0, 0,(i-16)*M_PI/16, colors);
      nanosleep(&request, &remaining);
      printf("\x1b[H\x1b[J");
      i = (i + 1) % 33;
    }
}


int main()
{
    rotatingCube(middle,10,headerColors);
    printf("\n");
    return 0;
}