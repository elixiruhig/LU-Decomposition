#include<iostream>
#include<typeinfo>
#include<math.h>
#include<time.h>
#include<omp.h>
#ifndef n
#define n 100
#endif
#ifndef t
#define t 4
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
	
	omp_set_num_threads(t);
	for(int i=0;i<n;i++){
	p[i] = i;
	/*#pragma omp parallel shared(l,u)
	{
	
	omp_set_num_threads(omp_get_num_procs());
	#pragma omp for schedule(dynamic)
	*/
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
	//}
}
	/*cout<<"\nA = \n";
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
	}
	*/
	//static double a2[n][n];
	/*for(int i=0;i<n;i++){
		#pragma omp parallel shared(a,a2)
	{
		//omp_set_num_threads(n/2);
		#pragma omp for schedule(dynamic)
		for(int j=0;j<n;j++){
			a2[i][j] = a[i][j];
		}
	}
	}
	*/
	
	
	//#pragma omp parallel shared(a,p,l,u)
	//{
	//omp_set_num_threads(n);
	//#pragma omp for schedule(static)								///wdoknvwokvwkonv hellellel
	for(int k = 0; k<n;k++){
	
	
	
	
		double max = 0;
		int k2;
		#pragma omp parallel shared(a,k)
		{
		#pragma omp for
		for(int i=k;i<n;i++){
			#pragma omp critical
			if(max < abs(a[i][k])){
			
				max = abs(a[i][k]);
				k2 = i;
			}
		}
		}
		//cout<<"max = "<<max<<" ";
		if(max == 0){
			cout<<"Error: Matrix is singular\n";
			exit(0);
		}
		double temp = p[k];
		p[k] = p[k2];
		p[k2] = temp;
		
		
		//omp_set_num_threads(n);
		//#pragma omp for//	schedule(static, 1)
		for(int i=0;i<n;i++){
			temp = a[k][i];
			a[k][i] = a[k2][i];
			a[k2][i] = temp;
		}
		//#pragma omp barrier
		//omp_set_num_threads(k);
		//#pragma omp for// schedule(static,1)
		for(int i=0;i<k-1;i++){
			temp = l[k][i];
			l[k][i] = l[k2][i];
			l[k2][i] = temp;
		}
		
		
		u[k][k] = a[k][k];
		//cout<<"u("<<k<<") = "<<u[k][k]<<endl;
		#pragma omp parallel shared(a,u,l)
		{
		//omp_set_num_threads((n-k)/2);
		#pragma omp for schedule(dynamic)
		for(int i=k+1;i<n;i++){
			l[i][k] = (double)a[i][k]/u[k][k];
			u[k][i] = a[k][i];
		}
		#pragma omp barrier
		#pragma omp for schedule(dynamic)
		for(int i = k; i<n;i++){
			for(int j = k;j<n;j++){
			//double x = l[i][k] * u[k][j];
				a[i][j] -= (double)l[i][k] * u[k][j];
			}
		}
	}
	}
	
	
	
	//} ///parallel bracket
	
/*	
	
	static double prod[n][n];
	#pragma omp parallel shared(prod, u, l)
	{
	omp_set_num_threads(max(omp_get_num_threads()*2, n/2));							//sdvjknwsjkvnwkjvnsjnvjwnovnws hereeeeeeee
	#pragma omp for schedule(dynamic)
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			//#pragma omp atomic
			prod[i][j] = 0;
			for(int k=0;k<n;k++){
			#pragma omp atomic
				prod[i][j] += (double)l[i][k]*u[k][j];
			}
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
/*	
	static double permutation[n][n];
	#pragma omp parallel shared(permutation)
	{
	omp_set_num_threads(max(omp_get_num_threads()*2, n/2));
	#pragma omp for schedule(static)
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j == p[i]){
				//#pragma omp atomic
				permutation[i][j] = 1;
			}
			//#pragma omp atomic
			else permutation[i][j] = 0;
		}
	}
	}
	
	static double newprod[n][n];
	#pragma omp parallel shared(newprod, permutation)
	{
	omp_set_num_threads(omp_get_num_procs());
	#pragma omp for schedule(dynamic)
	for(int i=0;i<n;i++){
	//#pragma omp for
	
		for(int j=0;j<n;j++){
			newprod[i][j] = 0;
			for(int k=0;k<n;k++){
				#pragma omp atomic
				newprod[i][j] += permutation[i][k]*a2[k][j];
			}
		}
	}
	}//#pragma omp barrier
	
	/*cout<<"\nProd = \n";
	#pragma omp for
	for(int i=0;i<n;i++){
	cout<<endl;
		for(int j=0;j<n;j++){
			cout<<prod[i][j]<<"\t";
		}
	}
	
	cout<<"\nn="<<n;
	//#pragma omp barrier
	
	cout<<"\nA= "<<endl;
//	#pragma omp for
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<"\t";
		}
	}
	//#pragma omp barrier
	cout<<"\nL= "<<endl;
	//#pragma omp for
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<l[i][j]<<"\t";
		}
	}
	//#pragma omp barrier
	cout<<"\nU= "<<endl;
	//#pragma omp for
	for(int i=0;i<n;i++){
	cout<<"\n";
		for(int j=0;j<n;j++){
			cout<<u[i][j]<<"\t";
		}
	}
	//#pragma omp barrier
	cout<<"\nP = "<<endl;
	for(int i=0;i<n;i++){
		cout<<p[i]<<"\t";
	}
	/*
	cout<<"\n\nChecking accuracy\n\n";
	*/
	/*
	#pragma omp parallel shared(newprod, prod)
	{
	omp_set_num_threads(omp_get_num_threads());
	#pragma omp for schedule(dynamic)
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			prod[i][j] -= newprod[i][j];
		}
	}
	
	}
	*/
	static double sumarr[n];
	
	for(int j=0;j<n;j++){
		double sum = 0;
		for(int i=0;i<n;i++){
			
			//sum+=prod[i][j] * prod[i][j];
			sum+=a[i][j] * a[i][j];
		}
		//#pragma omp critical
		sumarr[j] = sum;
	}		

double sum = 0;
for(int i=0;i<n;i++){
	sum += sumarr[i];
}
cout<<"\nresidue ="<<(double)sqrt(sum)<<"\n";

}
