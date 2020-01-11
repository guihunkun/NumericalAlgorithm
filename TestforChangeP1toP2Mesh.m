clear
clc

[p,e,t] = initmesh('squareg'); 
%% plot mesh
figure
for i = 1:length(t)
    x = [p(1,t(1,i)), p(1,t(2,i)), p(1,t(3,i))];
    y = [p(2,t(1,i)), p(2,t(2,i)), p(2,t(3,i))];
    patch(x,y,'magenta');
    hold on 
end
% plot one triangle
kk = 1;
x = [p(1,t(1,kk)), p(1,t(2,kk)), p(1,t(3,kk))];
y = [p(2,t(1,kk)), p(2,t(2,kk)), p(2,t(3,kk))];
patch(x,y,'red');


%% Turn p1 element triangle into P2 element triangle
[p,t] = ChangeP1toP2Mesh(p,t);
%% plot mesh
figure
for i = 1:length(t)
    x = [p(1,t(1,i)), p(1,t(2,i)), p(1,t(3,i))];
    y = [p(2,t(1,i)), p(2,t(2,i)), p(2,t(3,i))];
    patch(x,y,'white');
    hold on 
end
% draw a triangle consisting of the midpoints of the three sides of a triangle
x = [p(1,t(4,kk)), p(1,t(5,kk)), p(1,t(6,kk))];
y = [p(2,t(4,kk)), p(2,t(5,kk)), p(2,t(6,kk))];
patch(x,y,'yellow');


hold on 
kk = 1;
x = [p(1,t(1,kk)), p(1,t(4,kk)), p(1,t(6,kk))];
y = [p(2,t(1,kk)), p(2,t(4,kk)), p(2,t(6,kk))];
patch(x,y,'cyan');

