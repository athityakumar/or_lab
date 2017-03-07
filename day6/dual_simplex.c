#include <stdio.h>
#define INFINITY -999
#define N 10
#define M 20
/***************************************************/
/***** Solves the LPP by "DUAL SIMPLEX" method *****/
/***************************************************/
void minimum(float *arr,int *arrminpos,int n);
/* Calculates the minimum valued position among the array arr having n elements. */
void maximum(float *arr,int *arrminpos,int n);
/* Calculates the minimum valued position among the array arr having n elements. */
void display (float c[],float b[],float a[][M],int basic[]);
/* Display the table */
void displayframe(float c[M]);
/* Displays the frame of the table */
void calctemp(float *,float [][M],float [],int []);
/* Calculates Zj-Cj */

int countmaxzterms;
int constraint;

void main()
{
  float c[M];
  /* Stores co-efficient of the objective function Max(z) */
  float a[N][M];    /* Stores the co-efficent of the constraints */
  float b[N];      /* Stores the values on RHS of constraints */
  float temp[M];    /* Stores the values of Zj-Cj*/
  int bminpos;     /* Stores the minimum valued position
            of {Zj-Cj} i.e. coming in variable */
  float maxratio[M];   /* Stores the value of the ratio Zj-Cj/a[i][j] */
  int maxratiomaxpos;  /* Stores the minimum valued position of
            b[i]/a[i][j] i.e. going out variable */
  float key;      /* Stores the key element */
  int gooutcol;     /* Stores the column number which goes out */
  int incomingcol;
  float z;       /* Stores the value of the objective function */
  float x[M];     /* Stores the value of the variables */
  int i,j;      /* Loop variables */
  int basic[N];     /* Stores the basic variable */
  int flag=0;    /* Terminating variable */
  int obj_type=0;
  /*** Initializing basic variables ***/

  for(i=0;i<M;i++)
    c[i]=x[i]=temp[i]=0;
  for(i=0;i<N;i++)
    for(j=0;j<M;j++)
      a[i][j]=0;

  /*** Inputing requisite amount of data ***/

  printf("\nEnter number of terms in objective function\n");
  scanf("%d",&countmaxzterms);
  printf("\nEnter the co-efficient\n");
  for(i=0;i<countmaxzterms;i++)
    scanf("%f",&c[i]);
  printf("\nEnter type of objective function (1: Minimize, else maximize) \n");
  scanf("%d",&obj_type);
  if(obj_type==1)
    for(i=0;i<countmaxzterms;i++)
      c[i] *= (-1.0);
  printf("\nYou have entered the function as follows:-\n");
  printf("\nMax z = ");
  for(i=0;i<countmaxzterms;i++)
  {
    if(i==0)
      printf("%g*x%d",c[i],i+1);
    else
      printf(" + %g*x%d",c[i],i+1);
  }
  printf("\nEnter number of constraint\n");
  scanf("%d",&constraint);
  int crit_type[constraint];
  printf("\nEnter the co-efficient of constraints\n");
  for(i=0;i<constraint;i++)
    for(j=0;j<countmaxzterms;j++)
      scanf("%f",&a[i][j]);
  for(i=0;i<constraint;i++)
    a[i][j++]=1;
  printf("\nEnter values of bi's\n");
  for(i=0;i<constraint;i++)
    scanf("%f",&b[i]);
  for(i=0;i<countmaxzterms+constraint;i++)
    basic[i]=(i+countmaxzterms);
  printf("\nYou have entered the function as follows:-\n");
  for(i=0;i<constraint;i++)
  {
    for(j=0;j<countmaxzterms;j++)
    {
      if(j==0)
        printf(" %g*x%d ",a[i][j],j+1);
      else
        printf(" + %g*x%d ",a[i][j],j+1);
    }
    printf(" <= %g\n",b[i]);
  }

  printf("\nEnter type of inequalities of above equations (1: >=, else <=) \n");
  for(i=0;i<constraint;i++)
    scanf("%d",&crit_type[i]);
  for(i=0;i<constraint;i++)
    if(crit_type[i]==1)
      {
        for(j=0;j<countmaxzterms;j++)
          a[i][j] *= (-1.0);
        b[i] *= (-1.0);        
      }  
  /*** Calculation for actual table ***/

  do
  {

    /*** Terminating condition ***/

    for(i=0;i<constraint;i++)
    {
      flag=1;
      if(b[i]<=0)
      {
        flag=0;
        break;
      }
    }

    z=0;
    calctemp(temp,a,c,basic);
    printf("\n");

    display(c,b,a,basic);
    printf("\n\tZj-Cj\t\t");
    for(i=0;i<constraint+countmaxzterms;i++)
      printf("%0.3g\t",temp[i]);
    printf("\n\n");

    /*** Determining the outgoing column ***/

    minimum(b,&bminpos,constraint);
    gooutcol=basic[bminpos];

    /*** Determining the incoming column ***/
    for(i=0;i<M;i++)
      maxratio[i]=INFINITY;

    for(i=0;i<constraint+countmaxzterms;i++)
    {
      if(a[bminpos][i]==0)
      {
        maxratio[i]=INFINITY;
        continue;
      }
      if(a[bminpos][i]>0)
      {
        maxratio[i]=INFINITY;
        continue;
      }
      maxratio[i]=temp[i]/a[bminpos][i];
    }
    maximum(maxratio,&maxratiomaxpos,2*constraint);
    incomingcol=maxratiomaxpos;
    for(i=0;i<constraint+countmaxzterms;i++)
      x[i]=0;
    for(i=0;i<constraint;i++)
    {
      x[basic[i]]=b[i];
      printf("x[%d]=%0.3g\n",basic[i]+1,b[i]);
    }
    printf("\n Other variables are non-basic, ie, 0.");
    for(i=0;i<constraint;i++)
      z=z+c[i]*x[i];
    if(obj_type==1)
      z *= (-1.0);
    printf("Max(z) = %g",z);
    printf("\nComing in variable = X%d\t",incomingcol+1);
    printf("Going out variable = X%d\n",gooutcol+1);

    /*** Changing the basic and non-basic variable ***/

    basic[bminpos]=incomingcol;

    /*** Performing the operations to bring similar expressions in
    in-coming variable as out-going variable by row operations ***/

    key=a[bminpos][incomingcol];
    b[bminpos]=b[bminpos]/key;
    for(i=0;i<constraint+countmaxzterms;i++)
      a[bminpos][i]=a[bminpos][i]/key;
    for(i=0;i<constraint;i++)
    {
      if(bminpos==i)
        continue;
      key=a[i][incomingcol];
      for(j=0;j<(constraint+countmaxzterms);j++)
        a[i][j]=a[i][j]-a[bminpos][j]*key;
      b[i]=b[i]-b[bminpos]*key;
    }
    

  }while(flag==0);

  printf("\nPress any key to exit...\n");
  
}
void calctemp(float *temp,float a[N][M],float c[M],int basic[N])
{
  int i,j;
  for(i=0;i<constraint+countmaxzterms;i++)
  {
    temp[i]=0;
    for(j=0;j<constraint;j++)
      temp[i]=temp[i]+c[basic[j]]*a[j][i];
    temp[i]=temp[i]-c[i];
  }
}
void maximum(float *arr,int *arrmaxpos, int n)
{
  int i;
  int arrmax;
  arrmax=arr[0];
  *arrmaxpos=0;
  for(i=0;i<n;i++)
    if(arr[i]>arrmax)
    {
      arrmax=arr[i];
      *arrmaxpos=i;
    }
}

void minimum(float *arr,int *arrminpos, int n)
{
  int i;
  int arrmin;
  arrmin=arr[0];
  *arrminpos=0;
  for(i=0;i<n;i++)
    if(arr[i]<arrmin)
    {
      arrmin=arr[i];
      *arrminpos=i;
    }
}
void display (float c[N],float b[N],float a[N][M],int basic[N])
{
  int i,j;
  displayframe(c);
  for(i=0;i<constraint;i++)
  {
    printf("\n%0.3g\tX%d\t%0.3g\t",c[basic[i]],basic[i]+1,b[i]);
    for(j=0;j<constraint+countmaxzterms;j++)
      printf("%0.3g\t",a[i][j]);
    printf("\n");
  }
}
void displayframe(float c[M])
{
  int i;
  printf("\t\tc[j]\t");
  for(i=0;i<constraint+countmaxzterms;i++)
    printf("%0.2g\t",c[i]);
  printf("\n");
  printf("\nc[B]\tB\tb\t");
  for(i=0;i<constraint+countmaxzterms;i++)
    printf("a[%d]\t",i+1);
  printf("\n");
}