clear
clc


% format long

%% Exact integration
syms x y
f = 3*x + 2*y - x*y + 5*x^3 - 3*y^5 + 700;
x1 = 1;
y1 = 1;
x2 = 3;
y2 = 2;
x3 = 2;
y3 = 4;
exactInt = int(int(f,y, x/2+0.5, 3*x-2),x,1,2) + int(int(f,y,x/2+0.5,-2*x+8),x, 2,3);


%% Numerical integration
precision = 5;       % numerical integration precision
[weight, points] = GaussTriangleNumericalIntegration(precision);
numericalInt = 0;
for i = 1:length(weight)
    xx = points(i,1)*(x2-x1) + points(i,2)*(x3-x1) + x1;
    yy = points(i,1)*(y2-y1) + points(i,2)*(y3-y1) + y1;
    numericalInt = numericalInt + subs(subs(f,x,xx), y, yy)*weight(i);
end
valJacobi = abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));   % Jacobi determinant
%  x = (x2-x1)*r + (x3-x1)*s + x1;
%  y = (y2-y1)*r + (y3-y1)*s + y1;
%  
%  Jacobi = abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)) 
%  r = (  (y3-y1)*(x-x1)-(x3-x1)*(y-y1) )/jacobi;
%  s = ( -(y2-y1)*(x-x1)-(x2-x1)*(y-y1) )/jacobi;
numericalInt = numericalInt*valJacobi*0.5;

val = zeros(2,1);
val(1,1) = exactInt;
val(2,1) = numericalInt;
val
relativeError = abs(val(1,1)-val(2,1))/val(1,1)



