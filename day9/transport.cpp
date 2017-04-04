#include <iostream>
#include <iomanip>
#define MAX 5
#define FORN(i,n) for(int i=0;i<n;i++)

using namespace std;

float mat[MAX][MAX] = {0};
int m; //Number of Sources
int n; // Number of Destination
float temp[MAX][MAX], aa[MAX], bb[MAX];
float u[MAX] = {0}, v[MAX] = {0};

float printTemp(){
	float cost = 0;
    static int no=0;
     for(int i = 0 ; i <m ; i++){
          for(int j = 0 ; j < n; j++){
          		cost += mat[i][j] * temp[i][j];
               cout << fixed<<setw(7)<<setprecision(1)<<std::setfill(' ') <<mat[i][j]<<"*"<<temp[i][j] << " ";
          }
          cout << endl;
     }
     cout<<endl;
     return cost;
}

bool min_row_col(float row, float col){
	if (row<col) return true;
	else return false;
}

int main(){
	// Using NWCR Method
	cout << "Enter the number of sources: ";cin >> m;
	cout << "Enter the number of destinations: ";cin >> n;
	cout << "Enter the payoff matrix: \n";
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin >> mat[i][j];
		}
	}

	cout << "Enter the coefficients for supply: \n";
	for(int i=0;i<m;i++)cin >> aa[i];
	cout << "Enter the coefficients for demand: \n";
	for(int j=0;j<n;j++)cin >> bb[j];
	int min_row = MAX + 1, min_col = MAX + 1;

	int i = 0;
	int j = 0;
	u[0] = 0;
	v[0] = mat[0][0] - u[0];
	while (i<m && j<n){
			if (min_row_col(aa[i], bb[j])){
				// Minimum in row
				temp[i][j] = aa[i];
				bb[j] -= aa[i];
				i++;
				u[i] = mat[i][j] - v[j];
			}
			else {
				temp[i][j] = bb[j];
				aa[i] -= bb[j];
				j++;
				v[j] = mat[i][j] - u[i];
			}
		}
    cout<<"Cost : "<<printTemp()<<endl;

    cout<<"\nDuality Test:\n";
    bool optimal = true;
    FORN(i,m){
        FORN(j,n)
            if (u[i] + v[j] <= mat[i][j] ) cout<<"w "; else cout<<"x ", optimal=false;
        cout<<endl;
    }
    cout<<endl;
    if (optimal)
        cout<<"Optimal Solution";
    else
        cout<<"Not optimal Solution";

    cout<<endl;
}
