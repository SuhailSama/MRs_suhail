function [A, B] = parkingVehicleStateJacobianFcnRRT(x, u)
% Jacobian of model equations for parking.
% state variables x, y and yaw angle theta.
% control variables v and steering angle delta.

% Copyright 2019 The MathWorks, Inc.

%%
% Parameters
wb = 2.8;

% Variables
theta = x(3);
v = u(1);
delta = u(2);

%  nlmpc controller object with 
% three states, three outputs, and two inputs.
% nx = 3; % inputs
% ny = 3; % outputs
% nu = 2; % controls

% Linearize the state equations at the current condition
A = zeros(3,3); % input , output
B = zeros(3,2); % input , control

A(1,3) = -v*sin(theta); %d(dxdt(1))dx(3)
B(1,1) = cos(theta);%d(dxdt(1))du(1)

A(2,3) = v*cos(theta); %d(dxdt(2))dx(3)
B(2,1) = sin(theta);%d(dxdt(1))du(1)

B(3,1) = 1/wb*tan(delta); %d(dxdt(3))du(1)
B(3,2) = 1/wb*(v*(1+tan(delta)^2)); %d(dxdt(3))du(2)

