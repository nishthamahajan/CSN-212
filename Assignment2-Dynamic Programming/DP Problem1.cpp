#include<iostream>
using namespace std;
int max(int a, int b)
{
    return a>b ? a : b;
}
int longestZigZag ( int* seq, int n)
{
    int tab[n][2];
    for (int i=0; i<n; i++)
    {
        tab[i][0]=1;
        tab[i][1]=1;
        for (int j=0; j<i; j++)
        {
            if ((seq[i]-seq[j])>0)
                tab[i][0]=max(tab[j][1] + 1, tab[i][0]);
            else if ((seq[i]-seq[j])<0)
                tab[i][1]=max(tab[j][0] + 1, tab[i][1]);
        };
    };
    return max(tab[n-1][0], tab[n-1][1]);
};
int main()
{
    int s1[6]={ 1, 7, 4, 9, 2, 5 };
    int s2[10]={ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
    int s3[9]={ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout <<" Length of longest zigzag subsequence:"<<endl;
    cout<< " S1 "<<longestZigZag(s1,6)<<endl;
    cout<< " S2 "<<longestZigZag(s2,10)<<endl;
    cout<< " S3 "<<longestZigZag(s3,9)<<endl;
    return 0;
}
