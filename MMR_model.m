function dxdt = MMR_model(x, u)
% State equations for parking: 
% state variables x, y and yaw angle theta.
% control variables v and steering angle delta.

% Copyright 2019 The MathWorks, Inc.

%%
% Parameters
a0 = 0.1;

% Variables
theta = x(3);
f = u(1);
alpha = u(2);


% State equations
dxdt = zeros(3,1);
dxdt(1) = a0*f*cos(alpha);
dxdt(2) = a0*f*sin(alpha);
dxdt(3) = 1;



