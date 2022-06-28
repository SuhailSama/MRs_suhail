function [A, B] = MMR_JacobianFcn(x, u)
% State equations for parking: 
% state variables x, y and yaw angle theta.
% control variables v and steering angle delta.

% Copyright 2019 The MathWorks, Inc.

%%
% Parameters
a0 = 2.8;

% Variables
alpha = u(1);
f = u(2);

% Linearize the state equations at the current condition
A = zeros(3,3); % input , output
B = zeros(3,2); % input , control

% A(1,3) = -v*sin(theta); %d(dxdt(1))dx(3)
B(1,1) = a0* cos(alpha);%d(dxdt(1))du(1)

% A(2,3) = v*cos(theta); %d(dxdt(2))dx(3)
B(2,1) = a0* sin(alpha);%d(dxdt(2))du(1)

B(1,2) = -a0* f*sin(alpha); %d(dxdt(1))du(2)
B(2,2) = a0* f*cos(alpha); %d(dxdt(2))du(2)