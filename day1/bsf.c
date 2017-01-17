#include <stdio.h>

double * gauss_seidel(double a[][100], double b[], int n)
{
	int i,j,key;
	double er=0.0001,val,*x,x0[100],sum; 
	for(i=0;i<n;i++)
	{
		x0[i] = 0.0;
		x[i] = 0.0;
	}
	do
	{ 
		key = 0;
		for(i=0;i<n;i++)
		{
			sum = b[i];
			for(j=0;j<n;j++)
			{
				if(j!=i)
				{
					sum -= (a[i][j]*x0[j]);
				}
			}
			x[i] = sum/a[i][i];
			val = (x[i] - x0[i]) / x[i];
			if(val < 0.0)
			{
				val*=(-1.0);
			}
			if(val>er)
			{
				key = 1;
				x0[i] = x[i];
			}
		}
	}while(key==1);
	return(x);
}



void permute(double a[][100],int i, int j)
{

	// return a;
}

int combine(int arr[], int data[], int start, int end,int index, int r)
{
	int j,i,arr,k=0;
    if (index == r)
    {
        for (j=0; j<r; j++)
		{
            printf("%d ", data[j]);
        	arr[k] = data[j];
        	k=k+1;
        }
        printf("\n");
        return arr;
    }
 
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        int arr[] += combine(arr, data, i+1, end, index+1, r);
    }
}

void main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int r = 3;
    int n = sizeof(arr)/sizeof(arr[0]);
    int data[r];
    combine(arr, data, 0, n-1, 0, r);
}
