#include<graphics.h>
#include<stdio.h>
#include<math.h>
int main()
{

int x,y,end,p,x1,x2,y1,y2,dx,dy;
	
printf("\nEnter the co-ordinates of first point : ");
scanf("%d %d",&x1,&y1);
printf("\nEnter the co-ordinates of second point : ");
scanf("%d %d",&x2,&y2);

int gd=DETECT, gm=VGAMAX;
initgraph(&gd, &gm, 0);
	
	dx=abs(x1-x2);
	dy=abs(y1-y2);
	p = 2*dy-dx;
	
	if(x1>x2)
	{
		x=x2;
		y=y2;
		end=x1;
	}
	else
	{
		x=x1;
		y=y1;
		end=x2;
	}
	putpixel(x,y,WHITE);
	
	while(x<=end)
	{
		if(p<0)
		{
			x++;
			p=p+2*dy;
		}
		else
		{
			x++;
			y++;
			p=p+2*(dy-dx);
		}
		putpixel(x, 480 - y,WHITE);
		delay(10);
	}
	
	getchar();
	closegraph();
	return 0;
}