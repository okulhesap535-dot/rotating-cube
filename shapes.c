#include <math.h>
#include <stdio.h>
//#include <string.h>
#include <time.h>
int heightCanvas = 50;
int widthCanvas = 50;

char bg[2] = "  ";

const char *palette[] = {
    "🟦",
    "🟩",
    "🟥",
    "🟧"

};

int paint = 0;
struct coordinate
{
    int x;
    int y;
};
struct coordinate rotatePointAxisZ(int posx, int posy, int pointx, int pointy, double angle)
{
    int x = pointx - posx;
    int y = pointy - posy;

    struct coordinate result;
    result.x = (int)(x * cos(angle) - y * sin(angle) + posx);
    result.y = (int)(x * sin(angle) + y * cos(angle) + posy);

    return result;
}

void printSquare(struct coordinate pos, int length, double zrotation, double yrotation)
{
    for (int vertical = 0; vertical < heightCanvas; vertical++) 
    {
        for (int horizontal = 0; horizontal < widthCanvas; horizontal++) 
        {
            struct coordinate rotatedGridPosition;
            //Rotate the Z axis
            int rotatedY = vertical - pos.y;
            rotatedY /= cos(yrotation);
            rotatedY +=pos.y;

            rotatedGridPosition = rotatePointAxisZ(pos.x, pos.y, horizontal, rotatedY, zrotation);
            //Rotate the Y axis afterwards (order matters)
            //rotatedGridPosition.y -=pos.y;
            //rotatedGridPosition.y /= cos(yrotation);
            //rotatedGridPosition.y +=pos.y;

            if( rotatedGridPosition.x <= pos.x + length && rotatedGridPosition.x >= pos.x - length && rotatedGridPosition.y <=pos.y +length && rotatedGridPosition.y >=pos.y -length)
            {
                printf("%s", palette[paint]);
            }
            else 
            {
                printf("%s", bg);
            }
        }
        printf("\n");
    }
    fflush(0);
}

void printCircle(struct coordinate pos, int r, double rotation)
{
    for (int vertical = 0; vertical < heightCanvas; vertical++) 
    {
        for (int horizontal = 0; horizontal < widthCanvas; horizontal++) 
        {
            
            int dx = horizontal - pos.x;
            int dy = vertical - pos.y;
            double factor = cos(rotation);
            const double EPS = 1e-6;

            if (fabs(factor) < EPS)
            {
                printf("%s", bg);
            }
            else{
            dy /= factor; //Rotate here
            if(dx*dx + dy*dy <= r*r)
             {
                 printf("%s", palette[paint]);
             }
            else 
             {
                 printf("%s", bg);
             }
            }
        }
        printf("\n");
    }
    fflush(0);
}
void printTriangle(struct coordinate dotA,struct coordinate dotB,struct coordinate dotC, double zrotation, double xrotation)
{
    struct coordinate centroid;
    centroid.x = (dotA.x + dotB.x + dotC.x) / 3.0f;
    centroid.y = (dotA.y + dotB.y + dotC.y) / 3.0f;
    
    
    for (int vertical = 0; vertical < heightCanvas; vertical++) 
    {
        for (int horizontal = 0; horizontal < widthCanvas; horizontal++) 
        {
            struct coordinate rotatedGridPosition = rotatePointAxisZ(centroid.x, centroid.y, horizontal, vertical, zrotation);

            int dy = rotatedGridPosition.y - centroid.y;
            double factor = cos(xrotation);
            const double EPS = 1e-6;

            if (fabs(factor) < EPS)
            {
                printf("%s", bg);
            }
            else{
            dy /= factor; //Rotate here
            dy+= centroid.y;
            float vector1 = (float) (dotA.x*(dotC.y - dotA.y) + (rotatedGridPosition.x - dotA.y)*(dotC.x - dotA.x) -dy*(dotC.y - dotA.y)) / ((dotB.y - dotA.y)*(dotC.x - dotA.x) - (dotB.x - dotA.x)*(dotC.y - dotA.y));
            float vector2 = (float) (rotatedGridPosition.x - dotA.y- vector1*(dotB.y - dotA.y)) / (dotC.y - dotA.y);
            if(vector1 >= 0 && vector2 >=0 && (vector1 + vector2) <=1)
            {
                printf("%s", palette[paint]);
            }
            else 
            {
                printf("%s", bg);
            }
            }
        }
        printf("\n");
    }
    fflush(0);
  
}
int main()
{
    struct coordinate shapePos;
    shapePos.x=30;
    shapePos.y=20;
    struct coordinate dotA;
    dotA.x= 10;
    dotA.y= 10;
    struct coordinate dotB;
    dotB.x= 20;
    dotB.y= 10;
    struct coordinate dotC;
    dotC.x= 20;
    dotC.y= 20;
    
    //printTriangle(dotA, dotB, dotC,  0);
    int i =0;
    struct timespec remaining, request = { 0, 100000000 };
    while(1)
    {
      printCircle(shapePos, 10,(i)*(M_PI/8));
      //printTriangle(dotA, dotB, dotC, 0, (i)*(M_PI/8));
      nanosleep(&request, &remaining);
      fflush(0);
      printf("\x1b[H\x1b[J");
      i = i+1;
      if(i == 16){
        i=0;
      }
      if((i==4)||(i==12)){
        paint = (paint+1)%4;
      }
    
    }
    printf("\n");
}