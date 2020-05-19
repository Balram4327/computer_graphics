// Midpoint Circle Drawing Algorithm 

#include<stdio.h> 
# include<graphics.h>

void midPointCircleDraw(int x_centre, int y_centre, int r) 
{ 
	int x = r, y = 0; 

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
	
	// Printing the initial point on the axes 
	// after translation 
	//	printf("(%d, %d) ", x + x_centre, y + y_centre);
    putpixel(320 + x_centre + x, 240 - y_centre + y, 1); 
	
	// When radius is zero only a single 
	// point will be printed 
	if (r > 0) 
	{ 
        putpixel(320 + x_centre+x, y_centre - y,1); 
        putpixel(320 + x_centre+y, y_centre + x,1); 
        putpixel(320 + x_centre-y, y_centre + x,1);
	} 
	
	// Initialising the value of P 
	int P = 1 - r; 
	while (x > y) 
	{ 
		y++; 
		// Mid-point is inside or on the perimeter 
		if (P <= 0) 
			P = P + 2 * y + 1; 
			
		// Mid-point is outside the perimeter 
		else
		{ 
			x--; 
			P = P + 2 * y - 2 * x + 1; 
		} 
		
		// All the perimeter points have already been printed 
		if (x < y) 
			break; 
		
		// Printing the generated point and its reflection 
		// in the other octants after translation 
        putpixel(320 + x_centre+x, 240 -  y_centre + y,1);
        putpixel(320 + x_centre-x, 240 - y_centre + y,1);
        putpixel(320 + x_centre+x, 240 - y_centre - y,1);
        putpixel(320 + x_centre-x, 240 - y_centre - y,1);
		delay(10);
		// If the generated point is on the line x = y then 
		// the perimeter points have already been printed 
		if (x != y) 
		{ 
            putpixel(320 + x_centre+y, 240 - y_centre + x,1);
            putpixel(320 + x_centre-y, 240 - y_centre + x,1);
            putpixel(320 + x_centre+y, 240 - y_centre -x,1);
            putpixel(320 + x_centre-y, 240 - y_centre -x,1);
			delay(10);
		} 
	} 

getchar();
closegraph();
} 

int main() 
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
	return 0; 
} 
