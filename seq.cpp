#include<iostream>
#include<typeinfo>
#include<math.h>
#include<time.h>
#include<omp.h>
#include<stdlib.h>
#ifndef n
#define n 100
#endif

using namespace std;

int main(){
	//int n=1000;
	//cout<<"Enter dimension of A\n";
	//cin>>n;
	static double a[n][n];
	static double l[n][n];
	static double u[n][n];
	srand48(time(0));
	//cout<<"Enter elements of A\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j] = drand48();
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
	
	/*cout<<"\nA = \n";
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
	}
	*/
	/*static double a2[n][n];
	for(int i=0;i<n;i++){
	
		for(int j=0;j<n;j++){
			a2[i][j] = a[i][j];
		}
	}
	*/
	
	
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
		//cout<<"max = "<<max<<" ";
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
		//cout<<"u("<<k<<") = "<<u[k][k]<<endl;
		for(int i=k+1;i<n;i++){
			l[i][k] = (double)a[i][k]/u[k][k];
			u[k][i] = a[k][i];
		}
		
		for(int i = k; i<n;i++){
			for(int j = k;j<n;j++){
			//double x = l[i][k] * u[k][j];
				a[i][j] -= (double)l[i][k] * u[k][j];
			}
		}
	}
	/*
	static double prod[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			prod[i][j] = 0;
			for(int k=0;k<n;k++){
				prod[i][j] += (double)l[i][k]*u[k][j];
			}
		}
	}
	
	/*
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
	/*
	static double permutation[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j == p[i]){
				permutation[i][j] = 1;
			}
			else permutation[i][j] = 0;
		}
	}
	
	static double newprod[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			newprod[i][j] = 0;
			for(int k=0;k<n;k++){
				newprod[i][j] += permutation[i][k]*a2[k][j];
			}
		}
	}
	/*cout<<"\nProd = \n";
	for(int i=0;i<n;i++){
	cout<<endl;
		for(int j=0;j<n;j++){
			cout<<prod[i][j]<<"\t";
		}
	}
	
	cout<<"\nn="<<n<<"\n";
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
	/*
	*/
	//cout<<"\n\nChecking accuracy\n\n";
	/*
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			prod[i][j] -= newprod[i][j];
		}
	}
	
	*/
	double sumarr[n];
	
	for(int j=0;j<n;j++){
		double sum = 0;
		for(int i=0;i<n;i++){
			//sum+=prod[i][j] * prod[i][j];
			sum+=a[i][j] * a[i][j];
		}
		sumarr[j] = sum;
	}		

long double sum = 0;
for(int i=0;i<n;i++){
	sum += sumarr[i];
}
cout<<"\nresidue ="<<(double)sqrt(sum)<<"\n";

}
