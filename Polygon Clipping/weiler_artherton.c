#include <stdio.h>
#include <graphics.h>

float check_int(int, int, int, int, int, int, int, int, int);

void wclip(int clip_win[][2], int n, int poly[][2], int m)
{
    int count = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            float flag;
            if (j == 0)
            {
                if (i == m - 1)
                    flag = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 0);
                else
                    flag = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 0);
            }

            else
            {
                if (i == m - 1)
                    flag = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 0);

                else
                    flag = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 0);
            }

            if (flag != 1000)
                count++;
        }
    }

    float clip[n + count][2];
    int clip_ind[n + count];
    float subject[m + count][2];
    int subject_ind[m + count];

    int i_temp = 0;
    int j_temp = 0;

    for (int i = 0; i < m; i++)
    {
        subject[i_temp][0] = poly[i][0];
        subject[i_temp][1] = poly[i][1];
        subject_ind[i_temp] = 1;
        i_temp++;

        for (int j = n - 1; j >= 0; j--)
        {
            float y = 0;
            float x = 1000;

            if (j == 0)
            {
                if (i == m - 1)
                {
                    x = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 0);
                    y = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 1);
                }
                else
                {
                    x = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 0);
                    y = check_int(clip_win[j][0], clip_win[j][1], clip_win[n - 1][0], clip_win[n - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 1);
                }
            }
            else
            {
                if (i == m - 1)
                {
                    x = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 0);
                    y = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[0][0], poly[0][1], 1);
                }
                else
                {
                    x = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 0);
                    y = check_int(clip_win[j][0], clip_win[j][1], clip_win[j - 1][0], clip_win[j - 1][1], poly[i][0], poly[i][1], poly[i + 1][0], poly[i + 1][1], 1);
                }
            }

            if (x != 1000)
            {
                subject[i_temp][0] = x;
                subject[i_temp][1] = y;
                subject_ind[i_temp] = 0;
                i_temp++;
            }
        }
    }

    int toggle = 1;
    for (int i = 0; i < m + count; i++)
    {
        if (subject_ind[i] == 0)
            toggle = toggle + 1;

        setcolor(MAGENTA);
        if (toggle % 2 == 0)
        {
            if (i == m + count - 1)
                line(subject[i][0], 480 - subject[i][1], subject[0][0], 480 - subject[0][1]);
            else
                line(subject[i][0], 480 - subject[i][1], subject[i + 1][0], 480 - subject[i + 1][1]);

            delay(500);
        }
    }
    toggle = 1;

    i_temp = 0;
    j_temp = 0;

    for (int i = 0; i < n; i++)
    {
        clip[j_temp][0] = clip_win[i][0];
        clip[j_temp][1] = clip_win[i][1];
        clip_ind[j_temp] = 1;
        j_temp++;

        for (int j = m; j > 0; j--)
        {
            float y;
            float x = 1000;

            if (j == m)
            {
                if (i == n - 1)
                {
                    x = check_int(clip_win[i][0], clip_win[i][1], clip_win[0][0], clip_win[0][1], poly[0][0], poly[0][1], poly[m - 1][0], poly[m - 1][1], 0);
                    y = check_int(clip_win[i][0], clip_win[i][1], clip_win[0][0], clip_win[0][1], poly[0][0], poly[0][1], poly[m - 1][0], poly[m - 1][1], 1);
                }
                else
                {
                    x = check_int(clip_win[i][0], clip_win[i][1], clip_win[i + 1][0], clip_win[i + 1][1], poly[0][0], poly[0][1], poly[m - 1][0], poly[m - 1][1], 0);
                    y = check_int(clip_win[i][0], clip_win[i][1], clip_win[i + 1][0], clip_win[i + 1][1], poly[0][0], poly[0][1], poly[m - 1][0], poly[m - 1][1], 1);
                }
            }
            else
            {
                if (i == n - 1)
                {
                    x = check_int(clip_win[i][0], clip_win[i][1], clip_win[0][0], clip_win[0][1], poly[j][0], poly[j][1], poly[j - 1][0], poly[j - 1][1], 0);
                    y = check_int(clip_win[i][0], clip_win[i][1], clip_win[0][0], clip_win[0][1], poly[j][0], poly[j][1], poly[j - 1][0], poly[j - 1][1], 1);
                }
                else
                {
                    x = check_int(clip_win[i][0], clip_win[i][1], clip_win[i + 1][0], clip_win[i + 1][1], poly[j][0], poly[j][1], poly[j - 1][0], poly[j - 1][1], 0);
                    y = check_int(clip_win[i][0], clip_win[i][1], clip_win[i + 1][0], clip_win[i + 1][1], poly[j][0], poly[j][1], poly[j - 1][0], poly[j - 1][1], 1);
                }
            }

            if (x != 1000)
            {
                clip[j_temp][0] = x;
                clip[j_temp][1] = y;
                clip_ind[j_temp] = 0;
                j_temp++;
            }
        }
    }

    for (int i = 0; i < n + count; i++)
    {
        if (clip_ind[i] == 0)
            toggle = toggle + 1;

        setcolor(RED);
        if (toggle % 2 == 0)
        {
            if (i == n + count - 1)
                line(clip[i][0], 480 - clip[i][1], clip[0][0], 480 - clip[0][1]);
            else
                line(clip[i][0], 480 - clip[i][1], clip[i + 1][0], 480 - clip[i + 1][1]);

            delay(500);
        }
    }
}

void main()
{
    int n = 4;
    //clipping window
    int clip_win[][2] = {{250, 50}, {250, 450}, {500, 450}, {500, 50}};

    int m = 6;
    //polygon
    int poly[][2] = {{50, 100}, {50, 300}, {300, 400}, {400, 300}, {200, 200}, {400, 100}};

    int gd = DETECT, gm = VGAMAX;
    initgraph(&gd, &gm, 0);

    setcolor(YELLOW);
    //Drawing clipping window
    line(250, 480 - 50, 250, 480 - 450);
    line(250, 480 - 450, 500, 480 - 450);
    line(500, 480 - 450, 500, 480 - 50);
    line(500, 480 - 50, 250, 480 - 50);

    setcolor(BLUE);
    //Drawing polygon
    line(50, 480 - 100, 50, 480 - 300);
    line(50, 480 - 300, 300, 480 - 400);
    line(300, 480 - 400, 400, 480 - 300);
    line(400, 480 - 300, 200, 480 - 200);
    line(200, 480 - 200, 400, 480 - 100);
    line(400, 480 - 100, 50, 480 - 100);

    wclip(clip_win, n, poly, m);

    getchar();
    closegraph();
}

float check_int(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int num)
{
    float m1 = 0, m2 = 0, c1 = 0, c2 = 0;

    if (x2 - x1 != 0)
    {
        m1 = (float)(y2 - y1) / (x2 - x1);
        c1 = y1 - m1 * x1;
    }

    else
    {
        if (x3 - x4 != 0)
        {
            if (x3 < x4)
            {
                if ((x3 > x1) || (x4 < x1))
                    return 1000;
            }
            else
            {
                if ((x3 < x1) || (x4 > x1))
                    return 1000;
            }

            m2 = (float)(y4 - y3) / (x4 - x3);
            c2 = y4 - m2 * x4;
            float y;
            y = m2 * x1 + c2;
            if (num == 0)
                return x1;
            else
                return y;
        }
        else
            return 1000;
    }

    if (x4 - x3 != 0)
    {
        m2 = (float)(y4 - y3) / (x4 - x3);
        c2 = y4 - m2 * x4;
    }

    else
    {
        if (x2 - x1 != 0)
        {
            if (x1 < x2)
            {
                if ((x1 > x3) || (x2 < x3))
                    return 1000;
            }
            else
            {
                if ((x1 < x3) || (x2 > x3))
                    return 1000;
            }

            m1 = (float)(y2 - y1) / (x2 - x1);
            c1 = y1 - m1 * x1;
            float y;
            y = m1 * x4 + c1;
            if (num == 0)
                return x4;
            else
                return y;
        }
        else
            return 1000;
    }

    if (m1 == m2)
        return 1000;

    else
    {
        float x;
        x = (c1 - c2) / (m2 - m1);
        int temp1 = x1, temp2 = x3, temp3 = x2, temp4 = x4;
        if (x1 > x2)
        {
            temp1 = x2;
            temp3 = x1;
        }

        if (x3 > x4)
        {
            temp2 = x4;
            temp4 = x3;
        }

        if ((x >= temp1) && (x <= temp3) && (x >= temp3) && (x <= temp4))
        {
            float y;
            y = m1 * x + c1;
            if (num == 0)
                return x;
            else
                return y;
        }

        else
            return 1000;
    }
}