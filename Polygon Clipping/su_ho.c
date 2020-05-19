//Sutherland–Hodgman line clipping

#include <stdio.h>
#include <graphics.h>
//using namespace std;

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

// This functions clips all the edges w.r.t one clip
// edge of clipping area
int clip(int poly_points[][2], int poly_size,
		 int x1, int y1, int x2, int y2)
{
	int new_points[MAX_POINTS][2], new_poly_size = 0;

	// (ix,iy),(kx,ky) are the co-ordinate values of
	// the points
	for (int i = 0; i < poly_size; i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % poly_size;
		int ix = poly_points[i][0], iy = poly_points[i][1];
		int kx = poly_points[k][0], ky = poly_points[k][1];

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
		poly_points[i][0] = new_points[i][0];
		poly_points[i][1] = new_points[i][1];
	}

	return poly_size;
}

// Implements Sutherland–Hodgman algorithm
void suthHodgClip(int poly_points[][2], int poly_size,
				  int clipper_points[][2], int clipper_size)
{
	//i and k are two consecutive indexes
	for (int i = 0; i < clipper_size; i++)
	{
		int k = (i + 1) % clipper_size;

		// We pass the current array of vertices, it's size
		// and the end points of the selected clipper line
		poly_size = clip(poly_points, poly_size, clipper_points[i][0],
						 clipper_points[i][1], clipper_points[k][0],
						 clipper_points[k][1]);
	}

	// Printing vertices of clipped polygon
	for (int i = 0; i < poly_size; i++)
	{
		//	cout << '(' << poly_points[i][0] << ", " << poly_points[i][1] << ") ";
		if (i == 0)
			line(poly_points[poly_size - 1][0],480 - poly_points[poly_size - 1][1], poly_points[i][0], 480 - poly_points[i][1]);

		else
			line(poly_points[i - 1][0], 480 - poly_points[i - 1][1], poly_points[i][0], 480 - poly_points[i][1]);
	}
}

//Driver code
int main()
{
	// Defining polygon vertices in clockwise order
	int poly_size = 6;
	int poly_points[][2] = {{50, 100}, {50, 300}, {300, 400}, {400, 300}, {200, 200}, {400, 100}};

	// Defining clipper polygon vertices in clockwise order
	// 1st Example with square clipper
	int clipper_size = 4;
	int clipper_points[][2] = {{250, 50}, {250, 450}, {500, 450}, {500, 50}};

	int gd = DETECT, gm = VGAMAX;
	initgraph(&gd, &gm, 0);

	rectangle(250,480 - 50, 500,480 - 450);
	setcolor(RED);

	line(50, 480 - 100, 50, 480 - 300);
	line(50, 480 - 300, 300, 480 - 400);
	line(300, 480 - 400, 400, 480 - 300);
	line(400, 480 - 300, 200, 480 - 200);
	line(200, 480 - 200, 400, 480 - 100);
	line(400, 480 - 100, 50, 480 - 100);

	setcolor(GREEN);
	
	suthHodgClip(poly_points, poly_size, clipper_points,
				 clipper_size);

	getch();

	closegraph();
	return 0;
}
