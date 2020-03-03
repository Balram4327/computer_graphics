//DDA Line drawing algorithm
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <graphics.h>
#include<X11/Xlib.h>

int main()
{
int dx,dy,x1,y1,x2,y2;
float x, y, xinc, yinc, steps;

printf("\nEnter the co-ordinates of first point : ");
scanf("%d %d",&x1,&y1);
printf("\nEnter the co-ordinates of second point : ");
scanf("%d %d",&x2,&y2);

x = x1;
y = y1;

int gd=DETECT, gm=VGAMAX;
initgraph(&gd, &gm, 0);

dx = x2 - x1;
dy = y2 - y1;

if(abs(dx)>abs(dy))
    steps = dx;
else
    steps = dy;
    
xinc = dx/(float) steps;
yinc = dy/(float) steps;

for(int v=0; v<steps; v++)
{
    x = x + xinc;
    y = y + yinc;

    putpixel(x, 480 - y, BLUE); 
}

getchar();
closegraph();
return 0;
}