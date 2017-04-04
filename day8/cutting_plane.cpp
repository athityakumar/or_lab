#include <iostream>
#include <cmath>
using namespace std;

int d[10]={0};
int dmap[10]={-1};
float mat[10][10], b[10], temp[10][10], constants[10];
float ans[10][10], z[10];
int R, C;

int duald[10]={0};
int dualdmap[10]={-1};
float dualmat[10][10], dualb[10], dualtemp[10][10], dualconstants[10];
float dualans[10][10], dualz[10];
int dualR, dualC;
int main()
{
	int in_var, eqn, var;
	int flag = 0;int incos=0;
	string inequality;
	cout << "Enter no of variables\n";
	cin >> in_var;
	var= in_var;
	cout << "Enter no. of equations\n";
	cin >> eqn;
	for(int i = 0 ; i < eqn ; i++)
	{
		cout << "Enter coefficients and constant term of equation no " << i+1 << " seperated by spaces:\n";
		for(int j = 0 ; j <= in_var ; j++)
		{
			cin >> mat[i][j];
		}

	}
	
	for(int i=0;i < eqn;i++)
	{
		for(int j=0;j<=in_var;j++)
		{
			temp[i][j] = mat[i][j];
		}
	}
	
	cout << "Enter the objective function to be maximised\n";
	for(int i=0;i<=in_var;i++)
	{
		int a=0;
		cin >> a;
		if(a>0)flag=1;
		temp[eqn][i] = -a;
	}
	
	cout << "Initial simplex table\n ";
	for(int i=0;i <= eqn;i++)
	{
		for(int j=0;j<=in_var;j++)
		{
			cout << " " << temp[i][j];
		}
		cout << endl;
	}
	int dummy=1;
	cout << " Flag is " << flag;
	while(flag){
		
		float min = 10000; int prod=0;
		int minpos = -1;
		for(int i=0;i<in_var;i++)
		{
			if(temp[eqn][i] < 0)prod=1;
		}
		if(!prod){
			cout << "Prod is " << prod;
			flag=0;
			break;
		}
				
		for(int i=0;i<in_var;i++)
		{
			if(temp[eqn][i] <= min)
			{
				min = temp[eqn][i];
				minpos = i;
			}
		}
		
		cout << " Value of minpos is " << minpos << "  and invar is  " << in_var << endl;
		int pivot = -1;
		float minp = 10000;
		for(int i=0;i< eqn;i++)
		{
			if(1.0*temp[i][in_var]/temp[i][minpos] < minp && 1.0*temp[i][in_var]/temp[i][minpos]>0)
			{
				minp = 1.0*temp[i][in_var]/temp[i][minpos];
				pivot = i;
			}
		}
		
		if(pivot==-1){
			flag=0;
			incos = 1;
			break;
		}
		cout << "PIvot " << temp[pivot][minpos] << " at pos " << pivot;
		cout << "Most nbegatiove element " << min;
		
		d[minpos] = 1;
		dmap[minpos] = pivot;
		float p = temp[pivot][minpos];
		
		for(int i=0;i<=eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				if(i==pivot || j==minpos)continue;
				//cout <<  "\n\n Debuggind pqrs  for i = " << i << " and j=  " << j << "\n";
				//cout << " q " << temp[pivot][j] << " r " << temp[i][minpos];
				temp[i][j] = temp[i][j] - 1.0*temp[pivot][j]*temp[i][minpos]/p;
			}
		}

		for(int i=0;i<=eqn; i++)
		{
			if(i==pivot)continue;
			temp[i][minpos] = -temp[i][minpos]/p;
		}
		for(int j=0;j<=in_var;j++)
		{
			if(j==minpos)continue;
			temp[pivot][j] = temp[pivot][j]/p;
		}
		temp[pivot][minpos] = 1.0/temp[pivot][minpos];

		
		
		cout << "Simplex table\n ";
		for(int i=0;i <= eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				cout <<temp[i][j] << " ";
			}
			cout << endl;
		}
		//flag = 0;
	}

	if(incos)
	{
		cout << "The given system of equations inconsistent  ";
		return 0;
	}
	//cout << "The maximum of z is : " << temp[eqn][in_var];
	//for(int i=0;i<10;i++)
	//{
	//	if(d[i]){
	//		cout << " at x" << i+1 << " = " << temp[dmap[i]][in_var];
	//	}
	//}
	for(int j=0;j<in_var;j++)
	{
		if(temp[eqn][j]==0)
		{
			cout << " However infinite solutions exist for this case ";
			break;
		}
	}
	
	bool flagdual = true;
	while(flagdual){

		bool ifc=true;
		for(int i=0;i < eqn;i++)
		{
			if(fabs(floor(temp[i][in_var])-temp[i][in_var])>1e-5){
				ifc = false;break;
			}
		}
		if(ifc){flagdual=false;break;}
		float xbmax=-1; int xbpos;
		for(int i=0;i < eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				dualtemp[i][j] = temp[i][j];
				if(j==in_var && fabs(floor(temp[i][j])-temp[i][j])>1e-5){
					if((temp[i][j]-floor(temp[i][j])) > xbmax){
						xbmax = temp[i][j]-floor(temp[i][j]);
						xbpos = i;
					}
				}
			}
		}
		cout << "\nvalue of xbmax: " << xbmax << endl;
		if((int)xbmax==-1 || fabs(xbmax-1)<1e-5){cout << "Integer solution already calculated : ";return 0;}
		cout << "value of xbpos : " << xbpos;
		for(int j=0;j<=in_var;j++){
			dualtemp[eqn][j] = floor(temp[xbpos][j]) - temp[xbpos][j];
			dualtemp[eqn+1][j] = temp[eqn][j];
		}
		eqn = eqn +1;

		cout << "\nPrinting in-between table: \n";
		for(int i=0;i <= eqn;i++)
		{
			for(int j=0;j<=in_var;j++)
			{
				cout << dualtemp[i][j] << " " ;
			}
			cout << endl;
		}
	
		float min = 10000;int minpos = -1;
			int pivot = -1;
		
			for(int i=0;i< eqn;i++)
			{
				if(dualtemp[i][in_var] < min){
					min = dualtemp[i][in_var];
					pivot = i;
				}
			}

		cout << "\n Value of pivot: " << pivot << endl;
			float minp = 10000;
		for(int j=0;j<in_var;j++){
			float f = 1.0*dualtemp[eqn][j]/dualtemp[pivot][j];
			cout << "Value f : " << fabs(f) << " ";
			if(fabs(f) < minp){minp = fabs(f);minpos = j;cout << "Minpos selected as: " << j << endl;}
		}
		float p = dualtemp[pivot][minpos];
		cout << "\n Value of minpos and p: " << minpos << " " << p << endl;
		for(int i=0;i<=eqn;i++)
			{
				for(int j=0;j<=in_var;j++)
				{
					if(i==pivot || j==minpos)continue;
					dualtemp[i][j] = dualtemp[i][j] - 1.0*dualtemp[pivot][j]*dualtemp[i][minpos]/p;
				}
			}

		for(int i=0;i<=eqn; i++)
			{
				if(i==pivot)continue;
				dualtemp[i][minpos] = -dualtemp[i][minpos]/p;
			}
			for(int j=0;j<=in_var;j++)
			{
				if(j==minpos)continue;
				dualtemp[pivot][j] = dualtemp[pivot][j]/p;
			}
			dualtemp[pivot][minpos] = 1.0/dualtemp[pivot][minpos];

		for(int i=0;i <= eqn;i++)
			{
				for(int j=0;j<=in_var;j++)
				{
					cout <<dualtemp[i][j] << " ";
					temp[i][j] = dualtemp[i][j];
				}
				cout << endl;
			}
	}
	return 0;
}
