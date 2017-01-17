#include<stdio.h>

void main()
{

	int n,i,j,key=1;
	double er,val,x[100],x0[100],sum,a[100][100],b[100]; 
	printf("\n\n Enter stopping criteria (er) : ");
	scanf("%lf",&er);
	printf("\n Enter size of matrix (n) : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\n Input for marix A's row %d column %d : ",(i+1),(j+1));
			scanf("%lf",&a[i][j]);
		}
	}
	
	printf("\n");	
	for(i=0;i<n;i++)
	{
		printf("\n Input for matrix B's row %d column 1 : ",(i+1));
		scanf("%lf",&b[i]);
	}



	for(i=0;i<n;i++)
	{
		x0[i] = 0.0;
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

	printf("\n\n Printing solved matrix x.");
	for(i=0;i<n;i++)
	{
		printf("\n x[%d] = %lf",i,x[i]);
	}
	
	printf("\n\n");

}
