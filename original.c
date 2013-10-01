#include <stdio.h>
int maxsumline(int *p,int size)
{
    int i;
    int sum,ans;
    sum=0;
    ans=-1000000;
    for(i=0;i<size;i++)
    {
        if(sum<0)
            sum=0;
        sum+=p[i];
        if(ans<sum)
            ans=sum;
    }
    return ans;
}
int maxsumcycle(int *p,int size)
{
    int i;
    int sum,ans;
    sum=0;
    ans=maxsumline(p,size);
    for (i=0;i<size;i++)
    {
        sum+=p[i];
        p[i] = -p[i];
    }
    if ((sum+maxsumline(p,size))>ans)
    {
        return (sum+maxsumline(p,size));
    }
    else return ans;
}
int maxsumblock(int a[],int n,int m,int cycle,int expand)
{
    int i,j,k,tmp,totalmax=0,start;
    int sum[32][32];
    int t[32];
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            printf("%d ",a[i*m+j]);
            if (i!=0)
            {
                sum[i][j]=sum[i-1][j]+a[i*m+j];
            }
            else
            {
                sum[i][j]=a[i*m+j];
            }
        }
    }
    for (i=0;i<n;i++)
    {
        for (j=0;j<=i;j++)
        {
            for (k=0;k<m;k++)
            {
                t[k] = (j==0)?0:-sum[j-1][k];
                t[k] +=sum[i][k];
            }
            tmp = cycle?maxsumcycle(t,m):maxsumline(t,m);
            if (tmp>totalmax)
            {
                totalmax= tmp;
            }
            if (expand)
            {
                for (k=0;k<m;k++)
                {
                    t[k]=sum[n-1][k]-sum[i][k]+sum[j][k];
                }
                tmp = cycle?maxsumcycle(t,m):maxsumline(t,m);
                if (tmp>totalmax)
                {
                    totalmax= tmp;
                }
            }
        }
    }
    return totalmax;
}
int main()
{
    int m,n,j,i;
    int a[1024];
    FILE * fin = fopen("input.txt","r");
    fscanf(fin,"%d",&n);
    for (i=0;i<n;i++)
    {
        fscanf(fin,"%d",&a[i]);
    }
    printf("%d\n",maxsumcycle(a,n));
}
