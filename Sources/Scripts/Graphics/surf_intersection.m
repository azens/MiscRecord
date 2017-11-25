clear;clc;
x=-2:0.01:2;
y=-2:0.01:2;
[X,Y]=meshgrid(x,y);
Z1=X.^2+2*Y.^2;
Z2=6-2*X.^2-Y.^2;
Z1(X.^2+Y.^2>2)=NaN;
Z2(X.^2+Y.^2>2)=NaN;
surf(X,Y,Z1,'edgecolor','none');
hold on
surf(X,Y,Z2,'edgecolor','none');

