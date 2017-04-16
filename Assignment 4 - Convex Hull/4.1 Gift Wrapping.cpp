#include<iostream>
using namespace std;
struct point
{
    int x;
    int y;
};
int orientation (point p, point q, point r)
{
    int dir = (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y);
    if (dir == 0) return 0;  // collinear
    return (dir > 0)? 1: -1; // cw or anti-cw
};
void convex_hull_GW (point pt[], int n)
{
    if (n<3) return;
    int hull[n];
    for (int i = 0; i < n; i++)
        hull[i] = -1;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (pt[i].x < pt[l].x)
            l = i;
    int p = l, q;
    do
    {
        q = (p + 1) % n;
        for (int j = 0; j < n; j++)
            if (orientation(pt[p], pt[j], pt[q]) == -1)
                q = j;
        hull[p] = q;
        p = q;
    } while (p != l);
    int k = l;
    do
    {
        cout << "(" << pt[k].x << ", " << pt[k].y << ")\n";
        k=hull[k];
    } while (k!=l);
};

int main()
{
    point pt[] = { { 0, 3 }, { 2, 2 }, { 1, 1 }, { 2, 1 }, { 3, 0 }, { 0, 0 }, { 3, 3 } };
    cout << "The points in the convex hull are: \n";
    int n = sizeof(pt)/sizeof(pt[0]);
    convex_hull_GW(pt, n);
    return 0;
}

