#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "cube.h"


int printCube(const struct coordinate cubePosition, const int radius, const double zAngle,const double yAngle, const double xAngle, const struct color *colors)
{
   struct color pointColor;
   bool pointExists;
   const double cosz = cos(zAngle);
   const double sinz = sin(zAngle);
   const double cosy = cos(yAngle);
   const double siny = sin(yAngle);
   const double cosx = cos(xAngle);
   const double sinx = sin(xAngle);
   //Rotation vector v (length factor
   int factor = 100; //bigger factor better accuraccy
   int vx = factor*(siny*cosz +sinz*sinx*cosy);
   int vy=  factor*(sinz*siny +cosz*sinx*cosy);
   int vz= factor*(cosx*cosy);
   bool leftface = false;
   bool topface = false;
   bool frontface = false;
   if(vx>0){
    leftface = true;
   }
   if(vy>0){
    topface = true;
   }
   if(vz>0){
    frontface = true;
   }
     for(int y =0; y<heightCanvas; y++)
     {
       for(int x = 0; x<widthCanvas; x++){
         //Transform so the cube position is the origin now
         int tx = x - cubePosition.x;
         int ty = y - cubePosition.y;
         pointExists = false;
         //Unrotate z axis
         double nx = tx*cosz - ty*sinz;
         double ny = tx*sinz + ty*cosz;
         
           //Front back faces
           //Find the z value where after the x axis rotation it lands on the face
           double tz = (((radius*(frontface*2 -1)-ny*sinx)/cosx));

           //Find the z value where after the y axis rotation it lands on the prev tz value
           double sz = (((tz +nx*siny)/cosy));

           //First rotate this sz by y axis
           double newestx = nx*cosy + sz*siny;
           //sz -->tz

           //Rotate x axis
           double newesty = ny*cosx -tz*sinx;
           //tz -->radius
           if(fabs(newestx)<radius+EPS && fabs(newesty)<radius+EPS)
           {
             pointExists =true;
             pointColor=colors[1-frontface];
           }
           //If not move on to the next faces
           else{

           //Top bottom faces
           //Find the z value where after the x axis rotation it lands on the face
           tz = (radius*(1-2*topface)+ny*cosx)/sinx;

           //Find the z value where after the y axis rotation it lands on the prev tz value
           sz = (((tz +nx*siny)/cosy));

           //First rotate this sz by y axis
           newestx = nx*cosy + sz*siny;
           //sz -->tz

           //Rotate x axis
           double newery = ny*cosx -tz*sinx;
           tz = ny*sinx + tz*cosx;

           //Rotate x axis by 90 degrees
           //x stays the same after x axis rotation
           newesty = (2*topface -1)*tz;
           // z must become the radius if we did the math right

           if(fabs(newestx)<radius+EPS && fabs(newesty)<radius+EPS)
           {
             pointExists =true;
             pointColor=colors[5-topface];
           }
           }
          if(pointExists)
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
      printCube(cubePosition, radius, M_PI_4, 0,(i*M_PI/16), colors);
      nanosleep(&request, &remaining);
      printf("\x1b[H\x1b[J");
      i = (i+ 1 )%33;
    }
}


int main()
{
    rotatingCube(middle,10,headerColors);
    //printCube(middle, 10, 0,0,0,headerColors);
    printf("\n");
    return 0;
}