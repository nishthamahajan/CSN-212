#include<iostream>
#include<limits>
#include<cstdlib>
#include<time.h>
using namespace std;
class Graph
{
    int V; // #Vertices
    int** AdjM; // Adjacency Matrix
public:
    Graph(int);
    void addEdge (int ,int, int);
    void randG (); // Generate a random graph
    void shortestPathBF (int); // Bellman Ford
};
Graph::Graph(int v)
{
    V=v;
    AdjM=new int*[v];
    for (int i=0; i<v; i++)
    {
        AdjM[i]=new int[v];
        for (int j=0; j<v; j++)
            AdjM[i][j]=INT_MAX; //Initialize the elements of Adjacency Matrix to infinity
    };
};
void Graph::addEdge (int start, int dest, int w)
{
    AdjM[start][dest]=w;
};
void Graph::randG()
{
    int edge;
    for (int i=0; i<V; i++)
    {
        for (int j=0; j<V; j++)
        {
            edge=rand()%2; // Randomly decide if an edge exists
            if (edge)
                AdjM[i][j]=(-2)+(rand()%13); // Randomly assign weights between -2 and 10
        };
    };
};
void Graph::shortestPathBF (int s)
{
    int d[V]; // Array which stores the shortest distance from the source
    for (int i=0; i<V; i++)
    {
        if(i==s) d[i]=0;
        else d[i]=INT_MAX; // Initialization
    };
    int count;
    for (int j=0; j<V-1; j++)
    {
        count=0;
        for (int k=0; k<V; k++)
            {
                for (int l=0; l<V; l++)
                {
                    if(d[k]!=INT_MAX && AdjM[k][l]!=INT_MAX && d[l]>(d[k]+AdjM[k][l]))
                    {
                        d[l]=d[k]+AdjM[k][l]; // Relaxation
                        count++; // To keep track of changes made in each iteration
                    };
                };
            };
        if (count==0) break; // Exit if an iteration does not result in any change in the array d
    };
    int flag=0;
    for (int p=0; p<V; p++)
    {
        for (int q=0; q<V; q++)
        {
            if (d[p]!=INT_MAX && AdjM[p][q]!=INT_MAX && d[q]>(d[p]+AdjM[p][q]))
                {
                    cout<<"Negative weight cycle exists!\n";
                    flag=1;
                };
            if (flag!=0) {p=V;q=V;}; // Exit as soon as a negative weight cycle is detected
        };
    };
    cout<<"Source Vertex: "<<s<<endl;
    cout<<"Vertex  Distance\n";
    for (int r=0; r<V; r++)
    {
        if(r!=s)
            cout<<"   "<<r<<"       "<<d[r]<<endl; // Display shortest distance of each vertex from source
    };
    cout<<endl;
};
int main()
{
    srand (time(NULL));
    Graph G1(6); // Graph #1
    G1.addEdge(0,1,10);
    G1.addEdge(0,5,8);
    G1.addEdge(1,3,2);
    G1.addEdge(2,1,1);
    G1.addEdge(3,2,-2);
    G1.addEdge(4,1,-4);
    G1.addEdge(4,3,-1);
    G1.addEdge(5,4,1);
    G1.shortestPathBF(0);
    Graph G2(7); // Graph #2
    G2.addEdge(0,1,3);
    G2.addEdge(0,2,6);
    G2.addEdge(0,4,1);
    G2.addEdge(1,2,2);
    G2.addEdge(1,4,4);
    G2.addEdge(1,2,2);
    G2.addEdge(2,0,7);
    G2.addEdge(2,1,3);
    G2.addEdge(2,3,2);
    G2.addEdge(2,6,3);
    G2.addEdge(3,2,5);
    G2.addEdge(3,5,1);
    G2.addEdge(3,6,2);
    G2.addEdge(4,0,2);
    G2.addEdge(4,1,3);
    G2.addEdge(4,5,1);
    G2.addEdge(5,1,1);
    G2.addEdge(5,3,1);
    G2.addEdge(5,4,2);
    G2.addEdge(5,6,2);
    G2.addEdge(6,2,2);
    G2.addEdge(6,3,1);
    G2.addEdge(6,5,5);
    G2.shortestPathBF(0);
    Graph G3(10); // Graph #3
    G3.randG();
    G3.shortestPathBF(0);
    return 0;
}

