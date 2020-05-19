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

void cyrus(int vertices[][2], int n, int line[4])
{
    float d[2];
    d[0] = line[2] - line[0];
    d[1] = line[3] - line[1];

    float t[n];

    for (int i = 0; i < n; i++)
    {
        int nor[2];

        if (i == 5)
        {
            nor[1] = sign(vertices[i][0], vertices[0][0]);
            nor[0] = -1*sign(vertices[i][1], vertices[0][1]);
        }

        else
        {
            nor[1] = sign(vertices[i][0], vertices[i + 1][0]);
            nor[0] = -1*sign(vertices[i][1], vertices[i + 1][1]);
        }

        float w[2];
        w[0] = line[0] - vertices[i][0];
        w[1] = line[1] - vertices[i][1];

        float dn, wn;

        dn = (d[0] * nor[0]) + (d[1] * nor[1]);
        wn = (w[0] * nor[0]) + (w[1] * nor[1]);

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

int main()
{
    int n;
    int vectices[][2] = {{3*50, 0*50}, {1*50, 2*50}, {1*50, 4*50}, {3*50, 6*50}, {5*50, 4*50}, {5*50, 2*50}};

    int myline[4];

    n = 6;
   
    myline[0] = 250;
    myline[1] = 250;
    myline[2] = 70;
    myline[3] = 50;

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    setcolor(GREEN);

    line(3*50, 480 - 0*50, 1*50, 480 -  2*50);
    line(1*50, 480 - 2*50, 1*50, 480 -  4*50); 
    line(1*50, 480 -  4*50, 3*50, 480 -  6*50);
    line(3*50, 480 -  6*50, 5*50, 480 -  4*50);
    line(5*50, 480 -  2*50, 3*50, 480 -  0*50);
    line(250, 480 - 200, 250, 480 - 100);

    setcolor(BLUE);

    line(myline[0], 480 - myline[1], myline[2], 480 - myline[3]);

    getch();

    setcolor(RED);

    cyrus(vectices, n, myline);

    
    float clipped_line[4];
    clipped_line[0] = myline[0] + (myline[2] - myline[0]) * tl_max;
    clipped_line[1] = myline[1] + (myline[3] - myline[1]) * tl_max;

    clipped_line[2] = myline[0] + (myline[2] - myline[0]) * tu_min;
    clipped_line[3] = myline[1] + (myline[3] - myline[1]) * tu_min;

    line(clipped_line[0], 480 -  clipped_line[1], clipped_line[2], 480 -  clipped_line[3]);

    getch();

    closegraph();
    return 0;
}
