#include <graphics.h>
#include <stdio.h>

void main()
{
      int count;

      int dx, dy, x0, y0, x1, y1;
      int xmin, xmax, ymin, ymax;
      int t_x0, t_x1, t_y0, t_y1;
      float tmin, tmax, p[4], q[4], t;

      printf("Enter xmin and xmax for the clipping window: ");
      scanf("%d %d", &xmin, &xmax);

      printf("Enter ymin and ymax for the clipping window: ");
      scanf("%d %d", &ymin, &ymax);

      printf("Enter the line \n");
      printf("First point: \n");
      scanf("%d %d", &x0, &y0);
      printf("Second point: \n");
      scanf("%d %d", &x1, &y1);

      int gd = DETECT, gm = VGAMAX;
      initgraph(&gd, &gm, 0);

      rectangle(xmin, 480 - ymin, xmax, 480 - ymax);
      line(x0, 480 - y0, x1, 480 - y1);
      setcolor(RED);

      dx = x1 - x0;
      dy = y1 - y0;
      p[0] = -dx;
      p[1] = dx;
      p[2] = -dy;
      p[3] = dy;
      q[0] = x0 - xmin;
      q[1] = xmax - x0;
      q[2] = y0 - ymin;
      q[3] = ymax - y0;

      for (count = 0; count < 4; count++)
      {
            if (p[count] == 0)
            {
                  printf("\nLine is parallel\n");
                  if (q[count] >= 0)
                  {
                        if (count < 2)
                        {
                              if (y0 < ymin)
                              {
                                    y0 = ymin;
                              }
                              if (y1 > ymax)
                              {
                                    y1 = ymax;
                              }
                              line(x0, 480 - y0, x1, 480 - y1);
                        }
                        if (count > 1)
                        {
                              if (x0 < xmin)
                              {
                                    x0 = xmin;
                              }
                              if (x1 > xmax)
                              {
                                    x1 = xmax;
                              }
                              line(x0, 480 - y0, x1, 480 - y1);
                        }
                  }
            }
      }
      tmin = 0;
      tmax = 1;

      for (count = 0; count < 4; count++)
      {
            t = q[count] / p[count];
            if (p[count] < 0)
            {
                  if (tmin <= t)
                  {
                        tmin = t;
                  }
            }
            else
            {
                  if (tmax > t)
                  {
                        tmax = t;
                  }
            }
      }

      if (tmin < tmax)
      {
            t_x0 = x0 + tmin * p[1];
            t_x1 = x0 + tmax * p[1];
            t_y0 = y0 + tmin * p[3];
            t_y1 = y0 + tmax * p[3];
            line(t_x0, 480 - t_y0, t_x1, 480 - t_y1);
      }
      getch();
      closegraph();
}