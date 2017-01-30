#include <stdio.h>
#include <math.h>

int next_iteration_index(double *ptr, int m, int n)
{
    int i,index=0;
    for(i=1;i<n-1;i++)
    {   
        if(*(ptr+(n-1)*n+i) < *(ptr+(n-1)*n+index))
        {
            index = i;
        }
    }
    if(*(ptr+(n-1)*n+index) > 0)
    {
        return -1;
    }
    return index;
}

int pivot_index(double *ptr, int m, int n)
{
    int i,j=next_iteration_index(ptr,m,n),index=j;
    double vi = *(ptr+i*n+j),vn = *(ptr+i*n+n-1),min = vn/vi;
    for(i=1;i<n-1;i++)
    {
        vi = *(ptr+i*n+j);
        vn = *(ptr+i*n+n-1);
        if(vi>0 && (vn/vi)<min)
        {
            min = vn/vi;
            index = i*n+j;
        }
    }
    return index;
}

double * convert_pivot(double *ptr, int m, int n, int p_index)
{
    double p = *(ptr+p_index);
    p = 1/p;
    *(ptr+p_index) = p;
    return ptr;
}

double * convert_row(double *ptr, int m, int n, int p_index)
{
    double p = *(ptr+p_index),r;
    int p_row = p_index/n,p_col=p_index%n,i;
    for(i=0;i<n;i++)
    {
        if(i!=p_col)
        {
            r = *(ptr+p_row*n+i);
            r = r*p; 
            *(ptr+p_row*n+i) = r;       
        }
    }
    return ptr;
}

double * convert_column(double *ptr, int m, int n, int p_index)
{
    double p = *(ptr+p_index),c;
    int p_row = p_index/n,p_col = p_index%n,i;   
    for(i=0;i<n;i++)
    {
        if(i!=p_row)
        {
            c = *(ptr+i*n+p_col);
            c = (-1)*c*p;
            *(ptr+i*n+p_col) = c;                  
        }
    }
    return ptr;
}

double * convert_others(double *ptr, int m, int n, int p_index)
{
    double p = *(ptr+p_index),c,r,s;
    int p_row = p_index/n,p_col = p_index%n,i,j;   
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=p_row && j!=p_col)
            {
                r = *(ptr+p_row*n+j);
                c = *(ptr+i*n+p_col);
                s = *(ptr+i*n+j);
                s += (c*r/p); 
                *(ptr+i*n+j) = s;                                  
            }
        }
    }
    return ptr;
}

void print_array(double *ptr, int m, int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("\n");
        for(j=0;j<n;j++)
        {
            printf(" %lf ",*(ptr+i*n+j));       
        }
    }   
}

double * simplex_solve(double *ptr, int m, int n)
{   
    int p,i=1;
    while(next_iteration_index(ptr,m,n)!=-1)
    {
        printf(" Tableu from iteration  %d \n",i++);
        p = pivot_index(ptr,m,n);
        ptr = convert_pivot(ptr,m,n,p);
        ptr = convert_row(ptr,m,n,p);
        ptr = convert_column(ptr,m,n,p);
        ptr = convert_others(ptr,m,n,p);
        print_array(ptr,m,n);    
        printf("\n\n");
    }
    return ptr;
}

void main()
{
    double arr[] = {2,3,0,8,0,2,5,10,3,2,4,15,-3,-5,-4,0};
    double *ptr;
    int i,m=4,n=5;
    ptr = arr;
    ptr = simplex_solve(ptr,m,n);
}