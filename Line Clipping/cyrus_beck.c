#include <stdio.h>
#include <graphics.h>

float tl_max = -1, tu_min = 2;

int sign(int f, int i)
{
    if ((f - i) > 0)
        return 1;
    else if ((f - i) < 0)
        return -1;
    else
        return 0;
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

void cyrus(float verticesx[], float verticesy[], int n, int line[4])
{
    float d[2];
    d[0] = line[2] - line[0];
    d[1] = line[3] - line[1];

    float t[n];

    for (int i = 0; i < n; i++)
    {
        int nor[2];

        if (i == n - 1)
        {
            nor[1] = sign(verticesx[i], verticesx[0]);
            nor[0] = -1 * sign(verticesy[i], verticesy[0]);
        }

        else
        {
            nor[1] = sign(verticesx[i], verticesx[i + 1]);
            nor[0] = -1 * sign(verticesy[i], verticesy[i + 1]);
        }

        float w[2];
        w[0] = line[0] - verticesx[i];
        w[1] = line[1] - verticesy[i];

        float dn, wn;

        dn = (d[0] * nor[0]) + (d[1] * nor[1]);
        wn = (w[0] * nor[0]) + (w[1] * nor[1]);

     //   printf("dn = %f, ti = %f\n",dn,t[i]);
        t[i] = ((-1) * (wn / dn));

        if ((t[i] <= 1) && (t[i] >= 0) && (dn > 0))
        {
            if (tl_max < t[i])
                tl_max = t[i];
        }
        else if ((t[i] <= 1) && (t[i] >= 0) && (dn < 0))
        {
            if (tu_min > t[i])
                tu_min = t[i];
        }

    }
}

void main()
{
    int n;
    int myline[4];

    printf("Enter the number of points for the polygon");
    scanf("%d", &n);

    float verticesx[n];
    float verticesy[n];

    printf("Enter the polygon");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &verticesx[i]);
        scanf("%f", &verticesy[i]);
    }

    printf("Enter the line \n");
    printf("First point: \n");
    scanf("%d %d", &myline[0],&myline[1]);
    printf("Second point: \n");
    scanf("%d %d", &myline[2],&myline[3]);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    setcolor(BLUE);
    line(myline[0], 480 - myline[1], myline[2], 480 - myline[3]);

    getch();

    setcolor(GREEN);

    draw_poly(verticesx, verticesy, n);

    setcolor(RED);

    cyrus(verticesx, verticesy, n, myline);
    float clipped_line[4];
    clipped_line[0] = myline[0] + (myline[2] - myline[0]) * tl_max;
    clipped_line[1] = myline[1] + (myline[3] - myline[1]) * tl_max;
    clipped_line[2] = myline[0] + (myline[2] - myline[0]) * tu_min;
    clipped_line[3] = myline[1] + (myline[3] - myline[1]) * tu_min;

    line(clipped_line[0], 480 - clipped_line[1], clipped_line[2], 480 - clipped_line[3]);

    getch();

    closegraph();
}
