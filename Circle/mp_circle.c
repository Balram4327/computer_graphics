// Midpoint Circle Drawing Algorithm
#include <stdio.h>
#include <graphics.h>

void midPointCircleDraw(int x_centre, int y_centre, int r)
{
	int x = r, y = 0;

	int gd = DETECT, gm = VGAMAX;
	initgraph(&gd, &gm, 0);

	for (int i = 0; i < 480; i++)
	{
		putpixel(320, i, WHITE);
	}
	for (int i = 0; i < 640; i++)
	{
		putpixel(i, 240, WHITE);
	}

	//Initial point
	putpixel(320 + x_centre + x, 240 - y_centre + y, RED);

	putpixel(320 + x_centre, 240 - y_centre, RED);

	int P = 1 - r;
	while (x > y)
	{
		y++;
		if (P <= 0)
			P = P + 2 * y + 1;

		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		if (x < y)
			break;

		// Printing the generated point and its reflection
		// in the other octants after translation
		putpixel(320 + x_centre + x, 240 - y_centre + y, 1);
		putpixel(320 + x_centre - x, 240 - y_centre + y, 1);
		putpixel(320 + x_centre + x, 240 - y_centre - y, 1);
		putpixel(320 + x_centre - x, 240 - y_centre - y, 1);
		delay(10);
		
		if (x != y)
		{
			putpixel(320 + x_centre + y, 240 - y_centre + x, 1);
			putpixel(320 + x_centre - y, 240 - y_centre + x, 1);
			putpixel(320 + x_centre + y, 240 - y_centre - x, 1);
			putpixel(320 + x_centre - y, 240 - y_centre - x, 1);
			delay(10);
		}
	}

	getchar();
	closegraph();
}

void main()
{
	int r, xc, yc;

	printf("Midpoint circle drawing algorithm\n");
	printf("Enter Center for circle\nx : ");
	scanf("%d", &xc);
	printf("y : ");
	scanf("%d", &yc);

	printf("Enter the radius ");
	scanf("%d", &r);

	midPointCircleDraw(xc, yc, r);
}
