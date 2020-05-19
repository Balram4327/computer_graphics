//Bresenham Line Drawing Algorithm
#include<graphics.h>
#include<stdio.h>
//#include<math.h>

int main()
	{
	int x1, y1; // First point
	int x2, y2; // last point
	int x, y, end, p, dx, dy;
	
	printf("\n Enter the co-ordinates of first point (-320 < x < 320 and -240 < y < 240 ) : ");
	scanf("%d %d", &x1, &y1);
	printf("\nEnter the co-ordinates of second point (-320 < x < 320 and -240 < y < 240 ) : ");
	scanf("%d %d", &x2, &y2);

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
	
	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	p = 2*dy-dx;
	
	if(x1 > x2)
		{
			x = x2;
			y = y2;
			end = x1;
		}
	else
		{
			x = x1;
			y = y1;
			end = x2;
		}

	putpixel(x + 320, 240 - y, RED);
	
	while(x <= end)
		{
			if(p < 0)
			{
				x++;
				p = p+2*dy;
			}
			else
			{
				x++;
				y++;
				p = p+2*(dy-dx);
			}
			putpixel(x + 320, 240 - y, RED);
			delay(10);
		}
	
	getchar();
	closegraph();
	return 0;
}