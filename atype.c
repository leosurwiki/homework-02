#include <stdio.h>
#define N 32
#define M 32
const int shifti[4]={-1,-1,1,1};
const int shiftj[4]={1,-1,1,-1};
int shifter;
int m,n;
extern int a[32][32];
int father[N][M];
int value[1024];
int fatherfind(int x,int y)
{
    int result;
    result = x*m+y;
    if (father[x][y]!=x*m+y)
    {
        result = fatherfind(father[x][y]/m,father[x][y]%m);
        father[x][y] = result;
    }
    return result;
}
void setgraph()
{
    int i1,j1,i,j,fi,fj,num=0;
    int father2g[N*M],g[1024][1024];
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            father[i][j]=i*m+j;
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            father2g[i*m+j]=-1;
            if (a[i][j]>=0)
            {
                if (i>0&&a[i-1][j]>=0)
                {
                    father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i-1,j)/m][fatherfind(i-1,j)%m];
                }
                if (j>0&&a[i][j-1]>=0)
                {
                    father[fatherfind(i,j)/m][fatherfind(i,j)%m]=father[fatherfind(i,j-1)/m][fatherfind(i,j-1)%m];
                }
            }
        }
    }

    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            if (a[i][j]>0)
            {
                if (father2g[father[i][j]]==-1)
                {
                    father2g[father[i][j]]=num;
                    value[num]=a[i][j];
                    num++;
                }
                else
                {
                    value[num]+=a[i][j];
                }
            }
            else
            {
                value[num]=a[i][j];
                father2g[i*m+j]=num;
                num++;
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            for (shifter=0;shifter<4;shifter++)
            {
                if (i+shifti[shifter]>=0&&j+shiftj[shifter]>=0)
                {
                    i1=i+shifti[shifter];
                    j1=j+shiftj[shifter];
                    g[father2g[m*i1+j1]][father2g[m*i+j]]=1;
                    g[father2g[m*i+j]][father2g[m*i1+j1]]=1;
                }
            }
        }
    }
    for (i=0;i<num;i++)
    {
        for (j=0;j<num;j++)
        {
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }
    for (i=0;i<num;i++)
    {
        printf("%d ",value[i]);
    }
    printf("\n");
    return 0;
}
int main()
{
    int i,j;
    FILE * fin =fopen("input.txt","r");
    fscanf(fin,"%d%d",&m,&n);
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            fscanf(fin,"%d",&m,&n);
        }
    }

}
