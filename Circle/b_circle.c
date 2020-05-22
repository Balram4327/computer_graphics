//Bresenham Circle Drawing Algorithm
#include <stdio.h>
#include <graphics.h>

void main()
{
    int r, x, y, p, xc, yc;

    printf("Bresenham circle drawing algorithm\n");
    printf("Enter Center for circle\nx : ");
    scanf("%d", &xc);
    printf("y : ");
    scanf("%d", &yc);

    printf("Enter the radius ");
    scanf("%d", &r);

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

    putpixel(320 + xc, 240 - yc, RED);

    x = 0;
    y = r;
    putpixel(320 + xc + x, 240 - yc - y, 1);

    p = 3 - (2 * r);

    for (x = 0; x <= y; x++)
    {
        if (p < 0)
        {
            y = y;
            p = (p + (4 * x) + 6);
        }
        else
        {
            y = y - 1;
            p = p + ((4 * (x - y) + 10));
        }

        putpixel(320 + xc + x, 240 - yc - y, 1);
        putpixel(320 + xc - x, 240 - yc - y, 2);
        putpixel(320 + xc + x, 240 - yc + y, 3);
        putpixel(320 + xc - x, 240 - yc + y, 4);
        putpixel(320 + xc + y, 240 - yc - x, 5);
        putpixel(320 + xc - y, 240 - yc - x, 6);
        putpixel(320 + xc + y, 240 - yc + x, 7);
        putpixel(320 + xc - y, 240 - yc + x, 8);
        delay(10);
    }
    getchar();
    closegraph();
}