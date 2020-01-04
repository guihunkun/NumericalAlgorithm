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
        
        x = x0;
        r = A*x0-b;
        p = -r;
        n = 0;
        while(norm(r) >= epsa)
            alpha = (r'*r)/(p'*A*p);
            x = x + alpha*p;
            r2 = r + alpha*A*p; 
            beta = (r2'*r2)/(r'*r);
            p2 = -r2 + beta*p;
            n = n + 1;
            r = r2;
            p = p2;
        end
end