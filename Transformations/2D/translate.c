#include <stdio.h>
#include <graphics.h>

//Prototypes
void translate();
void scale();
void rotate();
void reflect();
void shear();
void translate_poly(int[], int[], int, int, int);
void scale_poly(int[], int[], int, int, int);
void shear_poly(int[], int[], int, float, float);
void draw_poly(int[], int[], int);
float mat_mul(int[], int[], int[], int, int, int);

void main()
{
    //translate();
    //scale();
    shear();
    closegraph;
}

float mat_mul(int mat1[], int mat2[], int mat3[], int x, int y, int num)
{
    float value;
    if (num == 0)
        value = mat1[0] * x + mat2[0] * y + mat3[0] * 1;
    else
        value = mat1[1] * x + mat2[1] * y + mat3[1] * 1;

    return value;
}

void draw_poly(int pointsx[], int pointsy[], int v)
{
    for (int i = 0; i < v; i++)
        if (i == v - 1)
            line(pointsx[i], 480 - pointsy[i], pointsx[0], 480 - pointsy[0]);
        else
            line(pointsx[i], 480 - pointsy[i], pointsx[i + 1], 480 - pointsy[i + 1]);

    getch();
}

void translate_poly(int pointsx[], int pointsy[], int v, int tx, int ty)
{
    int mat1[3] = {1, 0, 1};
    int mat2[3] = {0, 1, 1};
    int mat3[3] = {tx, ty, 1};

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    draw_poly(pointsx, pointsy, v);
}

void scale_poly(int pointsx[], int pointsy[], int v, int sx, int sy)
{
    int mat1[3] = {sx, 0, 0};
    int mat2[3] = {0, sy, 0};
    int mat3[3] = {1, 0, 1};

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    draw_poly(pointsx, pointsy, v);
}

void shear_poly(int pointsx[], int pointsy[], int v, float shx, float shy)
{
    int mat1[3] = {1, shy, 0};
    int mat2[3] = {shx,1 , 0};
    int mat3[3] = {0, 0, 1};
    int temp[2];
    temp[0] = pointsx[0];
    temp[1] = pointsy[0];

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = pointsx[i] - pointsx[0] + temp[0];
        pointsy[i] = pointsy[i] - pointsy[0] + temp[1];
    }

    draw_poly(pointsx, pointsy, v);

}

void translate()
{
    short res;
    printf("What would you like to translate? \n");
    printf("1. Point \n");
    printf("2. Polygon \n");
    scanf("%hd", &res);
    if (res == 1)
    {
        int x0, y0, tx, ty;
        printf("\n Okay then ... enter the point: ");
        scanf("%d %d", &x0, &y0);
        printf("\n Tell me tx and ty: ");
        scanf("%d %d", &tx, &ty);

        int gd = DETECT, gm = VGAMAX;
        initgraph(&gd, &gm, 0);

        putpixel(x0, 480 - y0, RED);
        circle(x0, 480 - y0, 3);
        getch();

        x0 = x0 + tx;
        y0 = y0 + ty;

        putpixel(x0, 480 - y0, BLUE);
        circle(x0, 480 - y0, 3);

        getch();
    }
    else
    {
        int v, tx, ty;
        printf("\n so you've decided polygon? Okay ...\n");
        printf("\n Enter the number of vertices (it can be two for a line): \n");
        scanf("%d", &v);

        int pointsx[v], pointsy[v];
        printf("\n Enter the points: \n");
        for (int i = 0; i < v; i++)
        {
            scanf("%d", &pointsx[i]);
            scanf("%d", &pointsy[i]);
        }

        printf("\n Tell me tx and ty: ");
        scanf("%d %d", &tx, &ty);

        int gd = DETECT, gm = VGAMAX;
        initgraph(&gd, &gm, 0);

        draw_poly(pointsx, pointsy, v);

        setcolor(GREEN);
        translate_poly(pointsx, pointsy, v, tx, ty);
    }
}

void scale()
{
    printf("Let's scale? \n");

    int v, sx, sy;
    printf("\n Polygon, right?");
    printf("\n Enter the number of vertices (it can be two for a line): \n");
    scanf("%d", &v);

    int pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%d", &pointsx[i]);
        scanf("%d", &pointsy[i]);
    }

    printf("\n Tell me sx and sy: ");
    scanf("%d %d", &sx, &sy);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    draw_poly(pointsx, pointsy, v);
    setcolor(GREEN);
    scale_poly(pointsx, pointsy, v, sx, sy);
}

void rotate()
{
    printf("Dummy!");
}

void reflect()
{
    printf("Dummy!");
}

void shear()
{
  printf("Let's shear? \n");

    int v;
    float shx, shy;
    printf("\n Polygon, right?");
    printf("\n Enter the number of vertices (it can be two for a line): \n");
    scanf("%d", &v);

    int pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%d", &pointsx[i]);
        scanf("%d", &pointsy[i]);
    }

    printf("\n Tell me shx and shy: \n");
    scanf("%f %f", &shx, &shy);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    draw_poly(pointsx, pointsy, v);
    setcolor(GREEN);
    shear_poly(pointsx, pointsy, v, shx, shy);
}