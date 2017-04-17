#include <stdio.h>

int main()
{
	int flag=0,flag1=0;
	int s[10],d[10],sn,eop=1,dm,a[10][10];
	int i,j,sum=0,min,x[10][10],k,fa,fb;
	printf("Enter the number of supplies : ");
	scanf("%d",&sn);
	printf("Enter the number of demands : ");
	scanf("%d",&dm);
	printf("Enter the supply values : \n");
	for(i=0;i<sn;i++)
	scanf("%d",&s[i]);
	printf("Enter the demand values \n");
	for(j=0;j<sn;j++)
	scanf("%d",&d[j]);
	printf("Enter the cost matrix \n");
	for(i=0;i<sn;i++)
	{
		for(j=0;j<dm;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	i=0;
	j=0;
	for(i=0,j=0;i<sn,j<dm;)
	{
		if(s[i]<d[j])          
		{
			x[i][j]=a[i][j]*s[i];
			d[j]=d[j]-s[i];
			i++;
		}
		else if(s[i]>=d[j])
		{
			x[i][j]=a[i][j]*d[j];
			s[i]=s[i]-d[j];
			j++;
		}
	}
	printf("\n\n Given cost matrix is :");
	for(fa=0;fa<sn;fa++)
	{
		printf("\n");
		for(fb=0;fb<dm;fb++)
		{
			printf("%d ",a[fa][fb]);
		}
	}
	printf("\n\n Allocated cost matrix is : ");
	for(fa=0;fa<sn;fa++)
	{
		printf("\n");
		for(fb=0;fb<dm;fb++)
		{
			printf("%d ",x[fa][fb]);
			sum=sum+x[fa][fb];
		}
	}
	printf("\n\nThe transportation cost is : %d",sum);
	return(0);
}