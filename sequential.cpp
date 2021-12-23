#include<iostream>
#include<typeinfo>

using namespace std;

int main(){
	int n;
	cout<<"Enter dimension of A\n";
	cin>>n;
	double a[n][n];
	double l[n][n];
	double u[n][n];
	
	cout<<"Enter elements of A\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	int p[n];
	

	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
		l[i][j] = 0.0;
		u[i][j] = 0.0;
			if(i == j){
				l[i][j] = 1.0;
			}
			else if(i < j){
				l[i][j] = 0.0;
			}
			else if(i > j){
				u[i][j] = 0.0;
			}
		}
	}
	
	
	
	
	
	for(int i=0;i<n;i++){
		p[i] = i;
	}
	for(int k = 0; k<n;k++){
	
	
	
	
		double max = 0;
		int k2;
		for(int i=k;i<n;i++){
			
			if(max < abs(a[i][k])){
				max = abs(a[i][k]);
				k2 = i;
			}
		}
		
		if(max == 0){
			cout<<"Error: Matrix is singular\n";
			break;
		}
		double temp = p[k];
		p[k] = p[k2];
		p[k2] = temp;
		
		for(int i=0;i<n;i++){
			temp = a[k][i];
			a[k][i] = a[k2][i];
			a[k2][i] = temp;
		}
		for(int i=0;i<k-1;i++){
			temp = l[k][i];
			l[k][i] = l[k2][i];
			l[k2][i] = temp;
		}
		
		
		
		u[k][k] = a[k][k];
		
		for(int i=k+1;i<n;i++){
			l[i][k] = (double)a[i][k]/u[k][k];
			u[k][i] = a[k][i];
		}
		
		for(int i = k+1; i<n;i++){
			for(int j = k+1;j<n;j++){
			//double x = l[i][k] * u[k][j];
				a[i][j] -= (double)l[i][k] * u[k][j];
			}
		}
	}
	
	
	
	/*for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j] -= prod[i][j];
		}
	}
	
	cout<<"\nA = "<<endl;
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
	}
	*/
	
	
	
	cout<<"\nA= "<<endl;
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
	}
	
	cout<<"\nL= "<<endl;
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<l[i][j]<<"\t";
		}
	}
	
	cout<<"\nU= "<<endl;
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<u[i][j]<<"\t";
		}
	}
	cout<<"\nP = "<<endl;
	for(int i=0;i<n;i++){
		cout<<p[i]<<"\t";
	}
	
	
}
