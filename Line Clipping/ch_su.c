#include<stdio.h>

int cal_code(int x_min, int y_min, int x_max, int y_max, int x, int y)
{
    int arr[4] = { 0, 0, 0, 0 };
    if(x < x_min)
    arr[2] = 1; //left

    if(x > x_max)
    arr[3] = 1; //right

    if(y < y_min)
    arr[1] = 1; //bottom

    if(y > y_max)
    arr[0] = 1; //top
    
    int code = 0;

    code = arr[0];
    code = (code * 10) + arr[1];
    code = (code * 100) + arr[2];
    code = (code * 1000) + arr[3];

    return code;
}

int main()
{
    int x_min,y_min,x_max,y_max,x1,y1,x2,y2;

    printf("Enter x_min and y_min \n");
    scnaf("%d %d",&x_min,&y_min);

    printf("\n Enter x_max and y_max \n");
    scnaf("%d %d",&x_max,&y_max);

    printf("Enter x1 and y1 coordinates of the line \n");
    scnaf("%d %d",&x1,&y1);

    printf("Enter x2 and y2 coordinates of the line \n");
    scnaf("%d %d",&x2,&y2);

    if((cal_code(x_min,y_min,x_max,y_max,x1,y1)==area) && (cal_code(x_min,y_min,x_max,y_max,x2,y2)==area))
        Printf("Line is already clipped. \n");

    else
    {
        
    }

    
    
}