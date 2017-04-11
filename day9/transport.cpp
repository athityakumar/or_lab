#include <stdio.h>
struct table
{
int assign;
int cost;
};
void display(struct table **t,int *sp,int *dm,int r,int c)
{
int i,j;
printf("\nTransportation Table:\n");
for(i=0;i {
for(j=0;j {
printf("%d(%d)\t",t[i][j].cost,t[i][j].assign);
}
printf("\t %d",sp[i]);
printf("\n");
}
printf("\n");
for(i=0;i printf("%d\t",dm[i]);
printf("\n*****************************************\n");
}
void read(struct table **t,int *sp,int *dm,int r,int c)
{
int i,j;
printf("Enter the costs:\n");
for(i=0;i {
for(j=0;j scanf("%d",&t[i][j].cost);
}
printf("Enter Supply Values:\n");
for(i=0;i scanf("%d",&sp[i]);
printf("Enter Demands\n");
for(i=0;i scanf("%d",&dm[i]);
}
void checkBalance(int *sp,int *dm,int r,int c)
{
int i,sum=0,sm=0;
for(i=0;i sum=sum+sp[i];
for(i=0;i sm=sm+dm[i];
if(sum!=sm)
{
printf("\nThe Given Transportation table is Unbalanced\n");
}
}
void calculaterowpen(struct table**t,int r,int c,int *rd,int *sp,int* dm)
{
int i,j;
int min,x=0,sec;
for(i=0;i {
min=999;
for(j=0;j {
if(min>t[i][j].cost && sp[i]!=0 && dm[j]!=0)
{
min=t[i][j].cost;
x=j;
}
}
sec=999;
for(j=0;j {
if(t[i][j].cost	sec=t[i][j].cost;
}
if(sec==999)
sec=min;
rd[i]=sec-min;
}
}
void calculatecolpen(struct table**t,int r,int c,int *cd,int *sp,int *dm)
{
int i,j;
int min,sec,x=0;
for(j=0;j {
min=999;
for(i=0;i {
if(t[i][j].cost {
x=i;
min=t[i][j].cost;
}
}
sec=999;
for(i=0;i {
if(t[i][j].cost	sec=t[i][j].cost;
}
if(sec==999)
sec=min;
cd[j]=sec-min;
}
}
void display2(struct table **t,int *sp,int *dm,int *rd,int *cd,int r,int c)
{
int i,j;
printf("\n\nTransportation Table with Penality:\n");
printf("\n");
for(i=0;i {
for(j=0;j {
printf("%d\t",t[i][j].cost);
}
printf("\t %d",sp[i]);
printf("\t\t %d",rd[i]);
printf("\n");
}
printf("\n");
for(i=0;i printf("%d\t",dm[i]);
printf("\n\n");
for(i=0;i printf("%d\t",cd[i]);
}
void highPen(struct table **t,int *sp,int *dm,int *rd,int *cd,int r,int c)
{
int h,hi,high,i,j,x=0,xi=0,p,min,q,k;
h=-999;
for(i=0;i if(rd[i]>h && sp[i]!=0)
{
h=rd[i];
x=i;
}
hi=-999;
for(i=0;i if(cd[i]>hi && dm[i]!=0)
{
hi=cd[i];
xi=i;
}
if(h>hi)
{
high=h;
p=x;
q=1;
}
else
{
high=hi;
p=xi;
q=2;
}
printf("\n\nHigh penality:%d & position:%d",high,p);
if(q==1)
{
min=999;
for(i=0;i	{
if(min>t[p][i].cost && sp[p]!=0 && dm[i]!=0)
{
min=t[p][i].cost;
k=i;
}
}
if(sp[p]	{
t[p][k].assign=sp[p];
dm[k]=dm[k]-sp[p];
sp[p]=0;
}
else
{
t[p][k].assign=dm[k];
sp[p]=sp[p]-dm[k];
dm[k]=0;
}
printf("\n\nAssignment:%d &cost=%d",t[p][k].assign,min);
}
if(q==2)
{
min=999;
for(i=0;i	if(min>t[i][p].cost && dm[p]!=0 && sp[i]!=0)
{
min=t[i][p].cost;
k=i;
}
if(sp[k]	{
t[k][p].assign=sp[k];
dm[p]=dm[p]-sp[k];
sp[k]=0;
}
else
{
t[k][p].assign=dm[p];
sp[k]=sp[k]-dm[p];
dm[p]=0;
}
printf("\n\n Assignment:%d & cost=%d",t[k][p].assign,min);
}
printf("\n");
}
int balanced(int *sp,int *dm,int r,int c)
{
int i;
for(i=0;i if(sp[i]>0)
return 0;
for(i=0;i if(dm[i]>0)
return 0;
return 1;
}
void costCalculation(struct table **t,int r,int c)
{
int i,j,sum=0;
for(i=0;i {
for(j=0;j sum=sum+(t[i][j].cost*t[i][j].assign);
}
printf("\nTotal cost=%d",sum);
}
int main()
{
struct table **t;
int r,c,i,j;
int *sp,*dm,*rd,*cd;
printf("\n\n\t\t***TRANSPORTATION PROBLEM***\n");
printf("\nEnter the Number of supply and demand: ");
scanf("%d%d",&r,&c);
t=(struct table**)malloc(sizeof(struct table *)*r);
for(i=0;i t[i]=(struct table*)malloc(sizeof(struct table)*c);
for(i=0;i {
for(j=0;j t[i][j].assign=0;
}
sp=(int *)malloc(2*r);
dm=(int *)malloc(2*c);
rd=(int *)malloc(2*r);
cd=(int *)malloc(2*c);
read(t,sp,dm,r,c);
checkBalance(sp,dm,r,c);
do
{
calculaterowpen(t,r,c,rd,sp,dm);
calculatecolpen(t,r,c,cd,sp,dm);
display2(t,sp,dm,rd,cd,r,c);
highPen(t,sp,dm,rd,cd,r,c);
display(t,sp,dm,r,c);
}while(balanced(sp,dm,r,c)==0);
costCalculation(t,r,c);
return(0);
} 