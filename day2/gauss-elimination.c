#include <stdio.h>

void gauss_elimination(double a[][100], int m,int n, int new2darr[])
{
    int i,j,k,key,flag,track=0;
    double er=0.001,val,x[100],x0[100],sum,a_new[100][100],c;
    for(i=0;i<m;i++)
    {
        x[i] = 0.0;
    }
    for(j=0; j<m; j++)
    {
        for(i=0; i<m; i++)
        {
            if(i>j)
            {
                c=a[i][j]/a[j][j];
                for(k=0; k<m+1; k++)
                {
                    a[i][k]=a[i][k]-c*a[j][k];
                }
            }
        }
    }
    x[m-1]=a[m-1][m]/a[m-1][m-1];
    for(i=m-1; i>=0; i--)
    {
        sum=0;
        for(j=i+1; j<m; j++)
        {
            sum=sum+a[i][j]*x[j];
        }
        x[i]=(a[i][m]-sum)/a[i][i];
    }
    for(i=0,j=0;i<n;i++)
    {
        flag = 0;
        for(k=0;k<(n-m);k++)
        {
            if(new2darr[k] == i)
                {
                    flag = 1;
                }
        }
        if (flag==0)
        {   
            printf(" x%d = %lf ",i+1,x[j++]);
        }
    }
}


int number_combine(int arr[], int data[], int start, int end,int index, int r, int s)
{
    int i;
    if (index == r)
    {
        return(s+1);
    }
 
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        s = number_combine(arr, data, i+1, end, index+1, r, s);    
    }
    return s;
}


int * combine(int arr[], int data[], int start, int end,int index, int r, int* newarr, int *l)
{
    int j,i;
    if (index == r)
    {
        for (j=0; j<r; j++)
        {
            *(newarr + *l) = data[j];
            (*l)++;
        }
        return newarr;
    }
 
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        newarr = combine(arr, data, i+1, end, index+1, r, newarr, l);    
    }
    return newarr;
}


void main () {

    int i,j,m,n;
    printf("\n Enter number of unknowns(n) : ");
    scanf("%d",&n);
    printf(" Enter number of equations (m) : ");
    scanf("%d",&m);
    double a[m][n],b[m];
    printf("\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf(" Input for marix a's row %d column %d : ",(i+1),(j+1));
            scanf("%lf",&a[i][j]);
        }
    }
    printf("\n");
    for(i=0;i<m;i++)
    {
        printf(" Input for matrix B's row %d column 1 : ",(i+1));
        scanf("%lf",&b[i]);
    }


    int arr[n],k;
    for(i=0;i<n;i++)
    {
        arr[i] = i;
    }
    int r = n-m;
    int data[r];
    int nc = number_combine(arr, data, 0, n-1, 0, r,0);
    int *getarr;
    int newarr[nc*r+1];
    int new2darr[nc+1][r+1];
    getarr = newarr;
    int l_start = 0;
    int *l = &l_start;
    getarr = combine(arr, data, 0, n-1, 0, r, getarr, l);
    for (i=0;i<nc;i++)
    {
        for(j=0;j<r;j++)
        {
            new2darr[i][j] = newarr[i*r+j];
        }
    }

    double a_new[100][100];
    int flag, track, h;

    for(i=0;i<nc;i++)
    {
        printf("\n");
        for(j=0;j<r;j++)
        {
            printf(" x%d = 0 ",new2darr[i][j]+1);
        }
        track = 0;
        for(j=0;j<n;j++)
        {
            flag = 0;
            for(k=0;k<(n-m);k++)
            {
                if(new2darr[i][k] == j)
                    {
                        flag = 1;
                    }
            }
            if (flag==0)
            {
                for(h=0;h<m;h++)
                {
                    a_new[h][j-track] = a[h][j];                
                }
            }
            else
            {
                track = track+1;
            }
        }
        for(h=0;h<m;h++)
        {
            a_new[h][m] = b[h];
        }
        gauss_elimination(a_new,m,n,new2darr[i]);

    }
}