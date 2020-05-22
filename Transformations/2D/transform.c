#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define SIN(x) sin(x * 3.141592653589/180) 
#define COS(x) cos(x * 3.141592653589/180)   

//Prototypes
void translate();
void scale();
void rotate();
void reflect();
void shear();
void translate_poly(float[], float[], int, int, int);
void scale_poly(float[], float[], int, int, int);
void shear_poly(float[], float[], int, float, float);
void reflect_poly(float[], float[], int, int);
void rotate_poly(float[], float[], int, float, int);
void draw_poly(float[], float[], int);
float mat_mul(float[], float[], float[], int, int, int);

void main()
{
    short res;
    printf("Welcome!\n");
    printf("What would you like to do?\n");
    printf("1. Translate\n2. Scale\n3. Shear\n4. Refelect\n5. Rotate\n");
    scanf("%hi", &res);

    switch (res)
    {
    case 1:
        translate();
        break;
    case 2:
        scale();
        break;
    case 3:
        shear();
        break;
    case 4:
        reflect();
        break;
    case 5:
        rotate();
        break;

    default:
        printf("You tripping?");
        break;
    }

    closegraph;
}

float mat_mul(float mat1[], float mat2[], float mat3[], int x, int y, int num)
{
    float value;
    if (num == 0)
        value = mat1[0] * x + mat2[0] * y + mat3[0] * 1;
    else
        value = mat1[1] * x + mat2[1] * y + mat3[1] * 1;

    return value;
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

void translate_poly(float pointsx[], float pointsy[], int v, int tx, int ty)
{
    float mat1[3] = {1, 0, 1};
    float mat2[3] = {0, 1, 1};
    float mat3[3] = {tx, ty, 1};

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    draw_poly(pointsx, pointsy, v);
}

void scale_poly(float pointsx[], float pointsy[], int v, int sx, int sy)
{
    float mat1[3] = {sx, 0, 0};
    float mat2[3] = {0, sy, 0};
    float mat3[3] = {1, 0, 1};

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    draw_poly(pointsx, pointsy, v);
}

void shear_poly(float pointsx[], float pointsy[], int v, float shx, float shy)
{
    float mat1[3] = {1, shy, 0};
    float mat2[3] = {shx, 1, 0};
    float mat3[3] = {0, 0, 1};
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

void reflect_poly(float pointsx[], float pointsy[], int v, int num)
{
    float mat1[3] = {0, 0, 0};
    float mat2[3] = {0, 0, 0};
    float mat3[3] = {0, 0, 0};
    if (num == 1)
    {
        mat1[0] = 1;
        mat2[1] = -1;
        mat3[2] = 1;
    }
    else if (num == 2)
    {
        mat1[0] = -1;
        mat2[1] = 1;
        mat3[2] = 1;
    }
    else
    {
        mat1[1] = 1;
        mat2[0] = 1;
        mat3[2] = 1;
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = pointsx[i] + 320;
        pointsy[i] = pointsy[i] + 240;
    }

    draw_poly(pointsx, pointsy, v);
}

void rotate_poly(float pointsx[], float pointsy[], int v, float theta, int num)
{
    float mat1[3] = {0, 0, 0};
    float mat2[3] = {0, 0, 0};
    float mat3[3] = {0, 0, 1};
    int temp[2];
    temp[0] = pointsx[0];
    temp[1] = pointsy[0];

    if (num == 1)
    {
        mat1[0] = COS(theta);
        mat1[1] = -1 * SIN(theta);

        mat2[0] = SIN(theta);
        mat2[1] = COS(theta);
    }

    else
    {
        mat1[0] = cos(theta);
        mat1[1] = sin(theta);

        mat2[0] = -1 * sin(theta);
        mat2[1] = cos(theta);
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = pointsx[i] - temp[0];
        pointsy[i] = pointsy[i] - temp[1];
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 0);
        pointsy[i] = mat_mul(mat1, mat2, mat3, pointsx[i], pointsy[i], 1);
    }

    for (int i = 0; i < v; i++)
    {
        pointsx[i] = pointsx[i] + temp[0];
        pointsy[i] = pointsy[i] + temp[1];
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

        float pointsx[v], pointsy[v];
        printf("\n Enter the points: \n");
        for (int i = 0; i < v; i++)
        {
            scanf("%f", &pointsx[i]);
            scanf("%f", &pointsy[i]);
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

    float pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%f", &pointsx[i]);
        scanf("%f", &pointsy[i]);
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
    printf("Let's Rotate? \n");

    int v, num;
    float theta;
    printf("\n Polygon, right?");
    printf("\n Enter the number of vertices (it can be two for a line): \n");
    scanf("%d", &v);

    float pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%f", &pointsx[i]);
        scanf("%f", &pointsy[i]);
    }

    printf("\n Enter theta: ");
    scanf("%f", &theta);

    printf("\n Clockwise(1) or anticlockwise(2)? ");
    scanf("%d", &num);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    draw_poly(pointsx, pointsy, v);
    setcolor(GREEN);
    rotate_poly(pointsx, pointsy, v, theta, num);
}

void reflect()
{
    printf("Reflection \n");

    int v, num;
    printf("\n Polygon, right?");
    printf("\n Enter the number of vertices (it can be two for a line): \n");
    scanf("%d", &v);

    float pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%f", &pointsx[i]);
        scanf("%f", &pointsy[i]);
    }

    printf("\n Choose your pick: \n");
    printf("1. About x-asis\n");
    printf("2. About y-asis\n");
    printf("3. About line x = y\n");
    scanf("%d", &num);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    float pointsx_t[v], pointsy_t[v];

    for (int i = 0; i < v; i++)
    {
        pointsx_t[i] = pointsx[i] + 320;
        pointsy_t[i] = pointsy[i] + 240;
    }

    draw_poly(pointsx_t, pointsy_t, v);
    setcolor(GREEN);
    reflect_poly(pointsx, pointsy, v, num);
}

void shear()
{
    printf("Let's shear? \n");

    int v;
    float shx, shy;
    printf("\n Polygon, right?");
    printf("\n Enter the number of vertices (it can be two for a line): \n");
    scanf("%d", &v);

    float pointsx[v], pointsy[v];
    printf("\n Enter the points: \n");
    for (int i = 0; i < v; i++)
    {
        scanf("%f", &pointsx[i]);
        scanf("%f", &pointsy[i]);
    }

    printf("\n Tell me shx and shy: \n");
    scanf("%f %f", &shx, &shy);

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    draw_poly(pointsx, pointsy, v);
    setcolor(GREEN);
    shear_poly(pointsx, pointsy, v, shx, shy);
}