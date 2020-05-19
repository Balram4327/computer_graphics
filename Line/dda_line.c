//DDA Line drawing algorithm

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <graphics.h>
#include<X11/Xlib.h>

int main()
{
    int x1, y1; // First point
	int x2, y2; // last point
    int dx,dy;
    float x, y, xinc, yinc, steps;

    printf("\nEnter the co-ordinates of first point (-320 < x < 320 and -240 < y < 240 ) : ");
    scanf("%d %d", &x1, &y1);
    printf("\nEnter the co-ordinates of second point (-320 < x < 320 and -240 < y < 240 ) : ");
    scanf("%d %d", &x2, &y2);

    x = x1;
    y = y1;

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    for(int i = 0; i < 480; i++)
		{
			putpixel(320, i, WHITE);
		}
	for(int i = 0; i < 640; i++)
		{
			putpixel(i, 240, WHITE);
		}

    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dx) > abs(dy))
        steps = dx;
    else
        steps = dy;
    
    xinc = dx/(float) steps;
    yinc = dy/(float) steps;

    for(int v = 0; v < steps; v++)
    {
        x = x + xinc;
        y = y + yinc;

    putpixel(320 + x, 240 - y, BLUE); 
    delay(10);
    }  

    getchar();
    closegraph();
    return 0;
}