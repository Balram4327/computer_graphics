//Mid Point Ellipse Drawing Algorithm

#include<stdio.h>
#include<graphics.h>

void main()
  {
  float x, y, xc, yc, rx, ry, pk, pk1;

  printf("Mid point ellipse drawing algorithm\n");
  printf("Enter Center for ellipse\nx : ");
  scanf("%f", &xc);
  printf("y : ");
  scanf("%f", &yc);
  printf("Enter x-radius and y-radius\nx-radius : ");
   scanf("%f", &rx);
  printf("y-radius : ");
  scanf("%f",&ry);

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

  x = 0;
  y = ry;

  pk = (ry * ry) - (rx * rx * ry) + ((rx * rx)/4);
  while((2 * x * ry * ry) < (2 * y * rx * rx))
  {
    if(pk <= 0)
    {
      x = x + 1;
      pk1 = pk + (2 * ry * ry * x) + (ry * ry);
    }
    else
    {
      x = x + 1;
      y = y - 1;
      pk1 = pk + (2 * ry * ry * x) - (2 * rx * rx * y) + (ry * ry);
    }
    pk=pk1;
    putpixel(320 + xc + x, 240 - yc + y, 2);
    putpixel(320 + xc - x, 240 - yc + y, 2);
    putpixel(320 + xc + x, 240 - yc - y, 2);
    putpixel(320 + xc - x, 240 - yc - y, 2);
    delay(10);
  }

    pk = ((x + 0.5) * (x + 0.5) * ry * ry) + ((y - 1) * (y - 1) * rx * rx) - (rx * rx * ry * ry);
    while(y > 0)
    {
      if(pk > 0)
        {
          y = y - 1;
          pk1 = pk - (2 * rx * rx * y) + (rx * rx);
        }
      else
        {
          x = x + 1;
          y = y - 1;
          pk1 = pk + (2 * ry * ry * x) - (2 * rx * rx * y) + (rx * rx);
        }
  pk = pk1;
  putpixel(320 + xc + x, 240 - yc + y, 2);
  putpixel(320 + xc - x, 240 - yc + y, 2);
  putpixel(320 + xc + x, 240 - yc - y, 2);
  putpixel(320 + xc - x, 240 - yc - y, 2);

  }
  //line(xc + rx, yc, xc - rx, yc);
  //line(xc, yc + ry, xc, yc - ry);
  outtextxy(320 + xc + (1.2 * rx), 240 - yc - (1.2 * ry), "(x, y)");
  outtextxy(320 + xc - (1.2 * rx), 240 - yc + (1.2 * ry), "(-x, -y)");
  outtextxy(320 + xc + (1.2 * rx), 240 - yc + (1.2 * ry), "(x, -y)");
  outtextxy(320 + xc - (1.2 * rx), 240 - yc - (1.2 * ry), "(-x, y)");
  getch();
  closegraph();
}