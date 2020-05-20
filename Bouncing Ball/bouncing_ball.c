#include <stdio.h>
#include <math.h>
#include <graphics.h>

const float g = 9.8;
float ux, theta, x_pos = 10;

void throw(float);
void project_obj(float);

void main()
{
    float hmax;
    printf("Enter initial velocity: ");
    scanf("%f", &ux);

    printf("\nEnter the height: ");
    scanf("%f", &hmax);

    printf("\nHere you go!");

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    throw(hmax);

    getch();
}

void throw(float hmax)
{
    float temp, theta, u, uy, r, t;

    temp = sqrt((2 * hmax * g) / (ux * ux));
    theta = atan(temp);

    u = ux / (cos(theta));

    uy = u * sin(theta);

    r = ((u * u) * sin(2 * theta)) / (2 * g);

    t = 2 * uy / g;

    float t_p = t / 2, y = 0;

    for (int i = 0; i < 50; i++)
    {
        setcolor(BLACK);
        circle(x_pos, 480 - y, 10);
        x_pos = x_pos + ux * (t_p);
        y = (uy * t_p) - (g * t_p * t_p / 2);
        t_p = t_p + (t / 50);

        setcolor(RED);
        circle(x_pos, 480 - y, 10);
        delay(100);

        if ((y < 0) || (x_pos > 640))
        {
        //    printf("x = %f, y = %f", x_pos, y);
            break;
        }

        // printf("%d\n",i);
    }

    project_obj(uy * 1);
}

void project_obj(float uy)
{
    if ((uy < 10)  || (x_pos > 600))
    {
        printf("Stapped");
    }

    else
    {

        float t;

        t = 2 * uy / g;

        float t_p = 0, y = 0;

        for (int i = 0; i < 10; i++)
        {
            if (y < 0)
            {
                //printf("x = %f, y = %f", x_pos, y);
                break;
            }
            x_pos = x_pos + ux * t_p;
            y = (uy * t_p) - (g * t_p * t_p / 2);
            t_p = t_p + (t / 10);

            setcolor(RED);
            circle(x_pos, 480 - y, 10);
            delay(100);

            setcolor(BLACK);
            circle(x_pos, 480 - y, 10);
        }

        project_obj(uy * 1);
    }
}