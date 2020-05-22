// Cohen Sutherland line clipping Algorithm
#include <stdio.h>
#include <graphics.h>

int xmin, xmax, ymin, ymax;

struct lines
{
	int x1, y1, x2, y2;
};

int sign(int x)
{
	if (x > 0)
		return 1;
	else
		return 0;
}

void clip(struct lines mylines)
{
	// arrays will store bits
	// Here bits impiles initial Point whereas bite implies end points
	int bits[4], bite[4], i, var;

	setcolor(RED);

	// Finding Bits
	bits[0] = sign(xmin - mylines.x1);
	bite[0] = sign(xmin - mylines.x2);
	bits[1] = sign(mylines.x1 - xmax);
	bite[1] = sign(mylines.x2 - xmax);
	bits[2] = sign(ymin - mylines.y1);
	bite[2] = sign(ymin - mylines.y2);
	bits[3] = sign(mylines.y1 - ymax);
	bite[3] = sign(mylines.y2 - ymax);

	// finding slope of line y=mx+c as (y-y1)=m(x-x1)+c
	// where m is slope m=dy/dx;

	float m = (mylines.y2 - mylines.y1) / (float)(mylines.x2 - mylines.x1);
	float c = mylines.y1 - m * mylines.x1;

	int f = 0;
	for (int i = 0; i < 4; i++)
		if (bits[i] != 0 || bite[i] != 0)
			f = 1;

	// if both points are inside the Accept the line and draw
	if (f == 0)
	{
		// inbuild function to draw the line from(x1, y1) to (x2, y2)
		line(mylines.x1, 480 - mylines.y1, mylines.x2, 480 - mylines.y2);
		return;
	}

	// this will contain cases where line maybe totally outside for partially inside
	else
	{

		f = 0;
		// taking bitwise end of every value
		for (i = 0; i < 4; i++)
		{

			int val = (bits[i] & bite[i]);
			if (val != 0)
				f = 1;
		}
		// as per algo if AND is not 0000 means line is completely outside hene draw nothing and retrurn
		if (f == 1)
			return;

		// Here contain cases of partial inside or outside
		// So check for every boundary one by one
		for (i = 0; i < 4; i++)
		{
			// if boths bit are same hence we cannot find any intersection with boundary so continue
			if (bits[i] == bite[i])
				continue;
			// Otherwise there exist a intersection

			// Case when initial point is in left xmin
			if (i == 0 && bits[i] == 1)
			{
				var = round(m * xmin + c);
				mylines.y1 = var;
				mylines.x1 = xmin;
			}
			// Case when final point is in left xmin
			if (i == 0 && bite[i] == 1)
			{
				var = round(m * xmin + c);
				mylines.y2 = var;
				mylines.x2 = xmin;
			}
			// Case when initial point is in right of xmax
			if (i == 1 && bits[i] == 1)
			{
				var = round(m * xmax + c);
				mylines.y1 = var;
				mylines.x1 = xmax;
			}
			// Case when final point is in right of xmax
			if (i == 1 && bite[i] == 1)
			{
				var = round(m * xmax + c);
				mylines.y2 = var;
				mylines.x2 = xmax;
			}
			// Case when initial point is in top of ymin
			if (i == 2 && bits[i] == 1)
			{
				var = round((float)(ymin - c) / m);
				mylines.y1 = ymin;
				mylines.x1 = var;
			}
			// Case when final point is in top of ymin
			if (i == 2 && bite[i] == 1)
			{
				var = round((float)(ymin - c) / m);
				mylines.y2 = ymin;
				mylines.x2 = var;
			}
			// Case when initial point is in bottom of ymax
			if (i == 3 && bits[i] == 1)
			{
				var = round((float)(ymax - c) / m);
				mylines.y1 = ymax;
				mylines.x1 = var;
			}
			// Case when final point is in bottom of ymax
			if (i == 3 && bite[i] == 1)
			{
				var = round((float)(ymax - c) / m);
				mylines.y2 = ymax;
				mylines.x2 = var;
			}
			// Updating Bits at every point
			bits[0] = sign(xmin - mylines.x1);
			bite[0] = sign(xmin - mylines.x2);
			bits[1] = sign(mylines.x1 - xmax);
			bite[1] = sign(mylines.x2 - xmax);
			bits[2] = sign(ymin - mylines.y1);
			bite[2] = sign(ymin - mylines.y2);
			bits[3] = sign(mylines.y1 - ymax);
			bite[3] = sign(mylines.y2 - ymax);
		}
		f = 0;
		for (int i = 0; i < 4; i++)
			if (bits[i] != 0 || bite[i] != 0)
				f = 1;

		// If now both points lie inside or on boundary then simply draw the updated line
		if (f == 0)
		{
			line(mylines.x1, 480 - mylines.y1, mylines.x2, 480 - mylines.y2);
			return;
		}
		// else line was completely outside hence rejected
		else
			return;
	}
}

void main()
{

	// Setting values of Clipping window
	printf("Enter xmin and xmax for the clipping window: ");
	scanf("%d %d", &xmin,&xmax);

	printf("Enter ymin and ymax for the clipping window: ");
	scanf("%d %d", &ymin,&ymax);

	struct lines myline;

	printf("Enter the line \n");
    printf("First point: \n");
    scanf("%d %d", &myline.x1,&myline.y1);
    printf("Second point: \n");
    scanf("%d %d", &myline.x2,&myline.y2);

	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);

	for (int i = 0; i < 480; i++)
	{
		putpixel(0, i, WHITE);
	}
	for (int i = 0; i < 640; i++)
	{
		putpixel(i, 479, WHITE);
	}

	rectangle(xmin, 480 - ymin, xmax, 480 - ymax); //Clipping window

	line(myline.x1, 480 - myline.y1, myline.x2, 480 - myline.y2); //Line to be clipped
	delay(1000);

	clip(myline);
	delay(1000);

	getch();
	closegraph();
}
