#include<iostream>
#include<iomanip>

#define MAX 5
#define FORN(i,n) for(int i=0;i<n;i++)

using namespace std;

float cb[MAX]={0,0,0},cnb[MAX]={5,5,6};
int m = 3; // Number of variables
//float b1[MAX][MAX];

int copy(float a[][MAX], float b[][MAX]){
    FORN(i,MAX)
        FORN(j,MAX)
            a[i][j] = b[i][j];
}

void initialize_unity(float b[][MAX]){
    FORN(i,MAX)
        b[i][i] = 1.0;
}

void print_matrix(float b[][MAX], int n, int m=0){
    if (m==0) m=n;

    FORN(i, n){
        FORN(j, m)
            cout<<setw(7)<<setprecision(3)<<std::setfill(' ')<<b[i][j];
        cout<<endl;
    }
}

void print_vector(float b[MAX], int n){
    cout<<"[ ";
    FORN(i, n){
        cout<<setw(7)<<setprecision(3)<<std::setfill(' ')<<b[i]<<" ";
    }
    cout<<"] "<<endl;
}

void swap(float &a, float &b){
    float temp = a;
    a = b;
    b = temp;
}


int calculate(float b[][MAX], float bi[][MAX], float b1[][MAX] ,float c[MAX], int n){

    FORN(aa,5){

        float eita[MAX], e[MAX];

        float x[MAX] = {0};
        float y[MAX] = {0}, zc[MAX] = {0};
        float z=0;
        float alpha_temp[MAX] = {0};

        FORN(i, n)
            FORN(j, n)
                x[i] += bi[i][j] * c[j];

        z = 0;
        FORN (i,n)
            z += cb[i]*x[i];


        cout<<"z:    ";
        cout<<z<<endl;
        cout<<"x: ";
        print_vector(x,n);


        FORN (i, n)
            FORN (j, n)
                y[i] += cb[j] * bi[j][i];

        FORN (i, m){
            FORN (j, n)
                zc[i] += y[j] * b1[j][i];
            zc[i] -= cnb[i];
        }

        float min = 0;
        int min_index = -1;
        FORN(i, m){
            if (zc[i]<min) 
                min=zc[i],min_index=i;
        }

        int q = min_index; // Entering variable

        FORN(i,n){
            FORN(j,n)
                alpha_temp[i] += bi[i][j] * b1[j][min_index];
            alpha_temp[i] = x[i] / alpha_temp[i];
        }

        min = 99999;
        min_index = -1;
        
        FORN(i, n){
            if (alpha_temp[i]<min) 
                min=alpha_temp[i],min_index=i;
        }


        if (min_index<0) return 0;
        int r = min_index; //leaving variable


        float E[MAX][MAX] = {0};
        float btemp[MAX][MAX];

        // Calculating e
        FORN(j,n){
            e[j] = 0;
            FORN(k,n){
                e[j] += bi[j][k]*b1[k][q];
            }
        }

        // Calculating eita
        FORN(j,n){
            if (j==r)
                eita[j] = 1/e[r];
            else
                eita[j] = -e[j]/e[r];
        }


        initialize_unity(E);

        FORN(i,n){
            float t = b[i][r];
            b[i][r] = b1[i][q];
            b1[i][q] = t;
            E[i][r] = eita[i];
        }

        swap(cb[r],cnb[q]);

        FORN(i,n)
            FORN(j,n){
                btemp[i][j] = 0;
                FORN(k,n){
                    btemp[i][j] += E[i][k] * bi[k][j];
                }
            }


        cout<<"Basic : "<<endl;
        print_matrix(b,n);
        cout<<"Basic Inverse: "<<endl;
        print_matrix(btemp,n);

        cout<<"\n";


        copy(bi, btemp);
        }
}
/*
void input(){
    string inequality;
    printf("Enter no of variables\n");
    scanf("%d",&var);

    printf("Enter no. of equations\n");
    scanf("%d",&eqn);

    for(i = 0 ; i < eqn ; i++)
    {
        printf("Input equations #%d \n" , i + 1);
        for(j = 0 ; j < var+1 ; j++)
        {
            scanf("%f",&mat[i][j]);
                        
        }
        //cin >> inequality;
        //if (inequality.at(0) == '<')
        //{
             slackVar++;
             scanf("%f", &mat[i][j]);
        }
        //else if (inequality.at(0) == '>')
        //{
         // Can be extended for Big-M Method
        //}
                
        }

}
*/
int main(){

    float b[MAX][MAX]={0};
    float bi[MAX][MAX];
    // float b1[MAX][MAX] = {{3,2,3,1},{3,0,1,2},{1,3,0,2}};
    // float c[MAX] = {200,180,160,50};
    float b1[MAX][MAX] = {{-2,3,0,5},{-2,-1,1,-2},{1,0,3,3}};
    float c[MAX] = {-2,3,3,0};

    int n = 3;

    initialize_unity(b);
    copy(bi,b);

    calculate(b,bi,b1,c,n);

    return 0;
}