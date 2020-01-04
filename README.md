# NumericalAlgorithm


1. IntersectAreaOfPoly.cpp
double IntersectAreaOfPoly(vector<Point>& polygon1, vector<Point>& polygon2)
/*
  Input: arbitrary polygon points, counterclockwise
  Output: Area of intersection of two polygons
*/
// HDU 3060 acm question


2. GaussElimination.cpp
void GaussElimination(vector<vector<double> >& A, vector<double>& b, vector<double>& x)
// Solving Ax = b by Gaussian Elimination
/* 
  Input: vector<vector<double> >& A
         vector<double>& b
         vector<double>& x
  solve result save in x;
*/
  
  
3. function [x, r, i] = GMRES ( A, b, x0, tol, maxit )
% solve Ax = b;
% Input:
% x0       Initial value
% tol      Precision
% maxit    The maximum number of iterations

% Output:
% x        Solution
% r        
% i        The number of iterations


4. GaussTriangleNumericalIntegration.m
function [weight, gausspoints] = GaussTriangleNumericalIntegration(precision)
% Calculate numerical integration on Triangle
% Input:
% precision       integration precision

% Output: 
% weight          integration weight
% gausspoints     integration points


5. TestForGauTriNumInt.m
% Just for test GaussTriangleNumericalIntegration
% If change triangle points exact integration need change 


6.ConjugateGradient.m
function [x,n] = ConjugateGradient(A, b, x0, epsa)
% solve Ax = b; 
% Input: 
        % A Matrix
        % b Vector
        % x0 Initial value 
        % epsa Precision 
 % Output:
        % x approximate solution
        % b the maximum number of iterations
        








