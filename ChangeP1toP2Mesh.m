function [p,t] = ChangeP1toP2Mesh(p,t)
%
%  Input:  p: nodes
%          t: index of node
%  Each triangle is described by three points.

%  Output: p: nodes
%          t: index of node
%  Each triangle is described by six points.
%
%    y
%    |
%    |
%    |
%    3
%    |\
%    |  \
%    6    \5
%    |      \
%    |________\ ________x                 
%    1    4    2
%  
%  ex: 
%  p = [0,0; 1,0; 0,1]';
%  t = [1;2;3;1];
%  p = [0,0; 1,0; 0,1; 1/2,0; 1/2,1/2; 0,1/2];
%  t = [1;2;3;4;5;6];
%

        np=size(p,2);        % number of nodes 
        edges=Tri2Edge(p,t); % get element edge numbers 
        edges=edges+np;      % change edges to new nodes 
        i=t(1,:); j=t(2,:); k=t(3,:);
        e=edges(:,1); 
        p(1,e)=0.5*(p(1,j)+p(1,k)); 
        p(2,e)=0.5*(p(2,j)+p(2,k)); 
        e=edges(:,2); 
        p(1,e)=0.5*(p(1,i)+p(1,k));
        p(2,e)=0.5*(p(2,i)+p(2,k)); 
        e=edges(:,3);
        % edge node coordinates
        p(1,e)=0.5*(p(1,i)+p(1,j));
        p(2,e)=0.5*(p(2,i)+p(2,j));
        % t(7,:)=t(4,:); % move subdomain info, resize t 
        t(4:6,:)=edges'; % insert edge nodes into t
        tt = t;
        t(4,:) = tt(6,:);
        t(5,:) = tt(4,:);
        t(6,:) = tt(5,:);
end
