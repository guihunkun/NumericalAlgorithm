function [weight, gausspoints] = GaussTriangleNumericalIntegration(precision)
%  Input: precision is integration precision  
%  Output: weight is weight
%          gausspoints is points
%
%    s
%    |
%    |
%    |
%    C
%    |\
%    |  \
%    |    \
%    |      \
%    |________\  ________r                  
%    A         B
%
%  A(0,0) B(1,0) C(0,1)
%  x = (x2-x1)*r + (x3-x1)*s + x1;
%  y = (y2-y1)*r + (y3-y1)*s + y1;
%  
%  Jacobi = abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1)) 
%  r = (  (y3-y1)*(x-x1)-(x3-x1)*(y-y1) )/jacobi;
%  s = ( -(y2-y1)*(x-x1)-(x2-x1)*(y-y1) )/jacobi;


switch precision
    case 1
        % 1 point
        weight = [1];
        gausspoints=[1/3 1/3];
    case 2
        % 3 points
        weight = [1/3 1/3 1/3];
        gausspoints = [1/6 1/6;
                       2/3 1/6;
                       1/6 2/3];
    case 3
        % 4 points
        weight = [-27/48 25/48 25/48 25/48];
        gausspoints = [1/3 1/3;
                       0.2 0.2;
                       0.6 0.2;
                       0.2 0.6];
    case 4
        % 6 points
        weight = [0.223381589678011
                  0.223381589678011
                  0.223381589678011
                  0.109951743655322
                  0.109951743655322
                  0.109951743655322];
        gausspoints = [0.445948490915965 0.445948490915965;
                       0.445948490915965 0.108103018168070;
                       0.108103018168070 0.445948490915965;
                       0.091576213509771 0.091576213509771;
                       0.091576213509771 0.816847572980459;
                       0.816847572980459 0.091576213509771];               
    case 5
        % 7 points
        weight = [0.1259391805448
                  0.1259391805448
                  0.1259391805448
                  0.1323941527885
                  0.1323941527885
                  0.1323941527885
                  0.225];
        gausspoints = [0.1012865073235, 0.1012865073235;
                       0.7974269853531, 0.1012865073235;
                       0.1012865073235, 0.7974269853531;
                       0.4701420641051, 0.0597158717898;
                       0.4701420641051, 0.4701420641051;
                       0.0597158717898, 0.4701420641051;
                       0.3333333333333, 0.3333333333333];                   
                   
    case 7
        % 13 points
        weight = [0.0533472356088
                  0.0533472356088
                  0.0533472356088
                  0.0771137608903
                  0.0771137608903
                  0.0771137608903
                  0.0771137608903          
                  0.0771137608903       
                  0.0771137608903                  
                  0.1756152574332
                  0.1756152574332                  
                  0.1756152574332
                  -0.1495700444677];
        gausspoints = [0.0651301029022, 0.0651301029022;
                       0.8697397941956, 0.0651301029022;
                       0.0651301029022, 0.8697397941956;
                       0.3128654960049, 0.0486903154253;
                       0.6384441885698, 0.3128654960049;
                       0.0486903154253, 0.6384441885698;
                       0.6384441885698, 0.0486903154253;
                       0.3128654960049, 0.6384441885698;
                       0.0486903154253, 0.3128654960049;
                       0.2603459660790, 0.2603459660790;
                       0.4793080678419, 0.2603459660790;
                       0.2603459660790, 0.4793080678419;
                       0.3333333333333, 0.3333333333333;];                       
    otherwise
        error('Quadrature precision too high on triangle');
end

