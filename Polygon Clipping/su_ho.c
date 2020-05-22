//Sutherland–Hodgman line clipping
#include <stdio.h>
#include <graphics.h>

const int MAX_POINTS = 20;

// Returns x-value of point of intersectipn of two
// lines
int x_intersect(int x1, int y1, int x2, int y2,
				int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (x3 - x4) -
			  (x1 - x2) * (x3 * y4 - y3 * x4);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

// Returns y-value of point of intersectipn of
// two lines
int y_intersect(int x1, int y1, int x2, int y2,
				int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (y3 - y4) -
			  (y1 - y2) * (x3 * y4 - y3 * x4);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

void draw_poly(float pointsx[], float pointsy[], int v)
{
	for (int i = 0; i < v; i++)
		if (i == v - 1)
			line(pointsx[i], 480 - pointsy[i], pointsx[0], 480 - pointsy[0]);
		else
			line(pointsx[i], 480 - pointsy[i], pointsx[i + 1], 480 - pointsy[i + 1]);

	getch();
}

// This functions clips all the edges w.r.t one clip
// edge of clipping area
int clip(float poly_pointsx[], float poly_pointsy[], int poly_size,
		 int x1, int y1, int x2, int y2)
{
	int new_points[MAX_POINTS][2], new_poly_size = 0;

	// (ix,iy),(kx,ky) are the co-ordinate values of
	// the points
	for (int i = 0; i < poly_size; i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % poly_size;
		int ix = poly_pointsx[i], iy = poly_pointsy[i];
		int kx = poly_pointsx[k], ky = poly_pointsy[k];

		// Calculating position of first point
		// w.r.t. clipper line
		int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);

		// Calculating position of second point
		// w.r.t. clipper line
		int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		// Case 1 : When both points are inside
		if (i_pos < 0 && k_pos < 0)
		{
			//Only second point is added
			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}

		// Case 2: When only first point is outside
		else if (i_pos >= 0 && k_pos < 0)
		{
			// Point of intersection with edge
			// and the second point is added
			new_points[new_poly_size][0] = x_intersect(x1,
													   y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = y_intersect(x1,
													   y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;

			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}

		// Case 3: When only second point is outside
		else if (i_pos < 0 && k_pos >= 0)
		{
			//Only point of intersection with edge is added
			new_points[new_poly_size][0] = x_intersect(x1,
													   y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = y_intersect(x1,
													   y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;
		}

		// Case 4: When both points are outside
		else
		{
			//No points are added
		}
	}

	// Copying new points into original array
	// and changing the no. of vertices
	poly_size = new_poly_size;
	for (int i = 0; i < poly_size; i++)
	{
		poly_pointsx[i] = new_points[i][0];
		poly_pointsy[i] = new_points[i][1];
	}

	return poly_size;
}

// Implements Sutherland–Hodgman algorithm
void suthHodgClip(float poly_pointsx[], float poly_pointsy[], int poly_size, float clipper_pointsx[], float clipper_pointsy[], int clipper_size)
{
	//i and k are two consecutive indexes
	for (int i = 0; i < clipper_size; i++)
	{
		int k = (i + 1) % clipper_size;

		// We pass the current array of vertices, it's size
		// and the end points of the selected clipper line
		poly_size = clip(poly_pointsx, poly_pointsy, poly_size, clipper_pointsx[i],
						 clipper_pointsy[i], clipper_pointsx[k],
						 clipper_pointsy[k]);
	}

	// Printing vertices of clipped polygon
	for (int i = 0; i < poly_size; i++)
	{
		//	cout << '(' << poly_points[i][0] << ", " << poly_points[i][1] << ") ";
		if (i == 0)
			line(poly_pointsx[poly_size - 1], 480 - poly_pointsy[poly_size - 1], poly_pointsx[i], 480 - poly_pointsy[i]);

		else
			line(poly_pointsx[i - 1], 480 - poly_pointsy[i - 1], poly_pointsx[i], 480 - poly_pointsy[i]);
	}
}

//Driver code
void main()
{
	// Defining polygon vertices in clockwise order
	int poly_size;
	//int poly_points[][2] = {{50, 100}, {50, 300}, {300, 400}, {400, 300}, {200, 200}, {400, 100}};

	printf("Number of points: (in the subject polygon) ");
	scanf("%d", &poly_size);
	float poly_pointsx[poly_size];
	float poly_pointsy[poly_size];

	printf("Enter the polygon: \n");
	for (int i = 0; i < poly_size; i++)
		scanf("%f %f", &poly_pointsx[i], &poly_pointsy[i]);

	int clipper_size;
	printf("Number of points: (in the clipping polygon) ");
	scanf("%d", &clipper_size);
	//int clipper_points[][2] = {{250, 50}, {250, 450}, {500, 450}, {500, 50}};
	float clipper_pointsx[clipper_size];
	float clipper_pointsy[clipper_size];

	printf("Enter the clipping polygon: \n");
	for (int i = 0; i < clipper_size; i++)
		scanf("%f %f", &clipper_pointsx[i], &clipper_pointsy[i]);
	

	int gd = DETECT, gm = VGAMAX;
	initgraph(&gd, &gm, 0);

	draw_poly(clipper_pointsx, clipper_pointsy, clipper_size); //clipper

	setcolor(RED);

	draw_poly(poly_pointsx, poly_pointsy, poly_size); //polygon

	setcolor(GREEN);

	suthHodgClip(poly_pointsx, poly_pointsy, poly_size, clipper_pointsx, clipper_pointsy, clipper_size);

	getch();

	closegraph();
}
