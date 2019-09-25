/** An Example to solve  Equations Ax = b **/
/*
 *  Using Gaussian Elimination and Column Pivot Element
 *
*/
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "assert.h"

using namespace std;

const double eps = pow(10,-10);
double absDou(double a)
{
	return (a >= 0)?a:(-a);
}

// Use functions to get martix A and vector b
void getA(vector<vector<double> >& A, int n)
{
	/*
	double a; // a number in A
	vector<double> tmp(n, 0.0);
	cout<<"Please input the matrix A:"<<endl;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cin>>a;
			tmp.push_back(a); // Save row vector in tmp first
		}
		A.push_back(tmp); // Then put tmp into A
		tmp.clear(); // Clean tmp for next row vector
	}
	*/
	cout<<"Please input the matrix A:"<<endl;
	double a;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n ;j++)
		{
			cin>>a;
			A[i][j] = a;
		}
}
void getb(vector<double>& b, int n)
{
	/*
	double a;	// a number in b
	cout<<"Please input the vector b:"<<endl;
	for (int i = 0; i < n; i++)
	{
		cin>>a;
		b.push_back(a);
	}
	*/
	cout<<"Please input the vector b:"<<endl;
	double a;
	for(int i = 0; i < n; i++)
	{
		cin>>a;
		b[i] = a;
	}
}

//Solve the problem by Gaussian Elimination
void GaussElimination(vector<vector<double> >& A, vector<double>& b, vector<double>& x)
{
	//assert(A.size() == A[0].size() && A.size() == b.size());

	int n = A.size();
	double tar;
	int pivot;
	vector<double> swa;
	for(int j = 0; j < n; j++)
	{
		// Find column pivot element,
		// the largest number in column vector
		pivot = j;
		for (int i = j + 1; i < n; i++)
		{
			if(absDou(A[i][j]) > absDou(A[pivot][j]))
			{
				pivot = i;
			}
		}
		
		// swap A[j] with the vector has largest number in j
		if(absDou(A[pivot][j]) < eps)
		{	// at this time, det(A) = 0
			cerr<<"Error! The equations may have no solution."<<endl;
			exit(1); 
		}
		if(pivot != j)
		{
			swa = A[j];
			A[j] = A[pivot];
			A[pivot] = swa;
			
			tar = b[j];
			b[j] = b[pivot];
			b[pivot] = tar;
		}
		
		// Gaussian Elimination
		for(int i = j + 1; i < n; i++)
		{
			double c = A[i][j]/A[j][j]; // The rate to minus
			A[i][j] = 0;
			for(int k=j+1;k<n;k++)
			{
				A[i][k] = A[i][k] - c*A[j][k];
			}
			b[i] = b[i] - c*b[j];
		}
	}
	// Return to get vector x
	for(int i = n - 1; i >= 0; i--)
	{
		tar = 0.0;	//b[i] should minus something
		for(int k = i + 1; k < n; k++)
		{
			tar += x[k] * A[i][k];
		}
		x[i] = (b[i] - tar)/A[i][i];
	}
}

int main()
{
	int n = 0; // The rank of A
	cout<<"Solving Ax = b by Gaussian Elimination"<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<<"This program can only solve questions "
	      "with just one solution.\n"<<endl;
	while(n<1)
	{
		cout<<"Please input the rank of A:";
		cin>>n;
		if (n<1)
			cout<<"Please input a number larger than 1!"<<endl;
	}


/*
	vector<vector<double> > A;
	vector<double> b, x;
*/


	vector<vector<double> > A(n, vector<double>(n, 0.0));
	vector<double> b(n, 0.0), x(n, 0.0);


	getA(A ,n);
	getb(b, n);



/*
	n = 2;
	vector<vector<double> > A(n, vector<double>(n, 0.0));
	vector<double> b(n, 0.0), x(n, 0.0);

	A[0][0] = 2; A[0][1] = 3;
	A[1][0] = 5; A[1][1] = 4;
	b[0] = 8;
	b[1] = 13;
*/


	GaussElimination(A, b, x);
	// To Solve

	cout<<"The solution x is:"<<endl;
	//Output
	for(int i = 0; i < n; i++)
	{
		cout<<x[i]<<" ";
	}
	cout<<endl;
	
	return 0;
}
