#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
 
int t = 0;
int n = 0;
char col[20];
bool c[20][20] = {0};
bool colored[20][20] = {0};
bool swit[20][20] = {0};
 
void changeswit(int a, int b)
{
    colored[a][b] = !colored[a][b];
    colored[a - 1][b] = !colored[a - 1][b];
    colored[a + 1][b] = !colored[a + 1][b];
    colored[a][b - 1] = !colored[a][b - 1];
    colored[a][b + 1] = !colored[a][b + 1];
}
 
 
int main()
{
    scanf("%d", &t);
    for(int ti = 1; ti <= t; ++ti)
    {
        int sum = 0;
        scanf("%d", &n);
        int min = n * n + 1;
        for(int i = 1; i <= n; ++i)
        {
            scanf("%s", col);
            for(int j = 1; j <= n; ++j)
            {
                if(col[j - 1] == 'y') c[i][j] = 1;
                else c[i][j] = 0;
            }
        }
        for(int k = 0; k < pow(2.0, n); k++)
        {
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                {
                    colored[i][j] = c[i][j];
                }
            for(int i = 1; i <= n; i++)
            {
                swit[1][i] = (k>>(i - 1)) & 1;
                if(swit[1][i])
                {
                    changeswit(1, i);
                    sum++;
                }
            }
            for(int i = 2; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    if(!colored[i - 1][j])
                    {
                        swit[i][j] = 1;
                        sum++;
                        changeswit(i, j);
                    }
            int mark = 0;
            for(int j = 1; j <= n; j++)
                if(!colored[n][j]) mark = 1;
            if(!mark && sum < min) min = sum;
            sum = 0;
        }
        if(min != n*n + 1) printf("%d\n",min);
        else printf("inf\n");
    }
    return 0;
}