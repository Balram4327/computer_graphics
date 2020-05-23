#include<stdio.h>
#include<graphics.h>

void translate();

void main()
{
    translate();
}

void translate()
{
    float xmin,xmax;
    float ymin,ymax;
    int tx, ty, tz;
    printf("Enter xmin and xmax ");
    scanf("%f %f", &xmin, &xmax);
    printf("Enter ymin and ymax ");
    scanf("%f %f", &ymax, &ymin);

    printf("Enter translation factor");

    scanf("%d%d",&tx,&ty,&tz);

    
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);

    bar3d(xmin,480 - ymin, xmax, 480-ymax,20,1);

    getch();

}