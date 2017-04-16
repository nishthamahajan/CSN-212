#include<iostream>
#include<stack>
#include <stdlib.h>
using namespace std;

struct point
{
    int x;
    int y;
};

point p0;

point nextToTop(stack<point> &S)
{
    point p = S.top();
    S.pop();
    point res = S.top();
    S.push(p);
    return res;
};

int swap(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
};

int sqDist(point p1, point p2)
{
    return (((p1.x - p2.x)^2) + ((p1.y - p2.y)^2));
};

int orientation(point p, point q, point r)
{
    int dir = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (dir == 0) return 0; // collinear
    return (dir > 0) ? 1 : -1; // cw or anti-cw
};

int compare(const void *vp1, const void *vp2)
{
    point *p1 = (point *) vp1;
    point *p2 = (point *) vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (sqDist(p0, *p2) >= sqDist(p0, *p1)) ? -1 : 1;
    return o;
};

void convex_hull_GS (point pt[], int n)
{
    int ymin = pt[0].y;
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = pt[i].y;
        if ((y < ymin) || (ymin == y && pt[i].x < pt[min].x))
            {
                ymin = pt[i].y;
                min = i;
            };
    };
    swap(pt[0], pt[min]);
    p0 = pt[0];
    qsort(&pt[1], n - 1, sizeof(point), compare);
    stack<point> S;
    S.push(pt[0]);
    S.push(pt[1]);
    S.push(pt[2]);
    for (int j = 3; j < n; j++)
    {
        while (orientation(nextToTop(S), S.top(), pt[j]) != -1)
            S.pop();
        S.push(pt[j]);
    };
    while (!S.empty())
    {
        point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    };
};

int main()
{
    point pt[] = { { 0, 3 }, { 1, 1 }, { 2, 2 }, { 4, 4 }, { 0, 0 }, { 1, 2 }, { 3, 1 }, { 3, 3 } };
    int n = sizeof(pt) / sizeof(pt[0]);
    cout << "The points in the convex hull are: \n";
    convex_hull_GS(pt, n);
    return 0;
}
