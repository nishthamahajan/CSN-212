#include<iostream>
using namespace std;
struct path
{
    int x1;
    int y1;
    int x2;
    int y2;
};
bool NB (path p, path* b, int n) // Not blocked
{
    for (int i=0; i<n; i++)
        {
            if (p.x1==b[i].x1 && p.y1==b[i].y1 && p.x2==b[i].x2 && p.y2==b[i].y2)
                return false;
        };
    return true;
};
int possible_paths (int width, int height, path* blocked, int nb)
{
    int tab[height+1][width+1];
    for (int i=height; i>=0; i--)
    {
        for (int j=width; j>=0; j--)
        {
            if ( NB({i,j,i+1, j}, blocked, nb) && NB({i,j,i,j+1}, blocked, nb) && i<height && j<width)
                tab[i][j]=tab[i+1][j]+tab[i][j+1];
            else if ( NB({i,j,i+1, j}, blocked, nb) && i<height )
                tab[i][j]=tab[i+1][j];
            else if ( NB({i,j,i,j+1}, blocked, nb) && j<width )
                tab[i][j]=tab[i][j+1];
            else if ( NB({i,j,i+1, j}, blocked, nb) && j==width )
                tab[i][j]=tab[i+1][j];
            else tab[i][j]=0;
        };
    };
    return tab[0][0];
};
int main()
{
    path b1[2]={{0, 0, 0, 1},{5, 6, 6, 6}};
    cout<<"Maximum Paths: "<<possible_paths(6,6,b1,2)<<endl;
    return 0;
}
