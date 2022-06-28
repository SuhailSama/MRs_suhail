clear 
clc 
close all

% add subfolders to paths 
folder = fileparts(which(mfilename)); 
addpath(genpath(folder));

%% 
load exampleMaps

ss = stateSpaceSE2;
sv = validatorOccupancyMap(ss);

image_file = '1.jpg';

[unsafeRegion,centersMMRs, radiiMMRs] = EnvRegMMR_Unsafe(image_file);

MRR_map = unsafeRegion;

map = occupancyMap(MRR_map,1);
map.show;


sv.Map = map;
sv.ValidationDistance = 1;
ss.StateBounds = [map.XWorldLimits; map.YWorldLimits; [-pi pi]];
planner = plannerRRTStar(ss,sv);
planner.ContinueAfterGoalReached = true;
planner.MaxIterations = 5000;
planner.MaxConnectionDistance = 10; 

%%% specify start and goal 
% start = [10, 10, 0];
% goal = [100, 500, 0];

% specify start and goal on image
[x_start,y_start] = ginput(1);
[x_end,y_end] = ginput(1);
start = [x_start, y_start, 0];
goal = [x_end,y_end, 0];


rng(100, 'twister') % repeatable result
[pthObj, solnInfo] = plan(planner,start,goal);

map.show;
hold on;
title( 'MMR' );

f = findobj('type','figure');
ax = gca(f);
hold(ax, 'on');
plot(solnInfo.TreeData(:,1),solnInfo.TreeData(:,2), '.-'); % tree expansion
plot(pthObj.States(:,1),pthObj.States(:,2),'r-','LineWidth',2); % draw path

% MPC 
mpcverbosity('off');
%  nlmpc controller object with three states, three outputs, and two inputs.
nx = 3;
ny = 3;
nu = 2;

nlobjTracking = nlmpc(nx,ny,nu);

% sample time (Ts), prediction horizon (PredictionHorizon),
% and control horizon (ControlHorizon) for the controller.
% change parameters to improve path following (trade-off performance time)
Ts = 0.1;
pTracking = 10;
nlobjTracking.Ts = Ts;
nlobjTracking.PredictionHorizon = 10;
nlobjTracking.ControlHorizon = pTracking;

% Contraints 
nlobjTracking.MV(1).Min = 0;
nlobjTracking.MV(1).Max = 1;
nlobjTracking.MV(2).Min = -2*pi;
nlobjTracking.MV(2).Max = 2*pi;

% tuning wieghts 
nlobjTracking.Weights.OutputVariables = [1,1,3]; 
nlobjTracking.Weights.ManipulatedVariablesRate = [0.1,0.2];

% motion of MRs is governed by 
nlobjTracking.Model.StateFcn = "MMR_model";
nlobjTracking.Jacobian.StateFcn = "MMR_JacobianFcn";
%  terminal constraints on control input
nlobjTracking.Optimization.CustomEqConFcn = "parkingTerminalConFcn";

% validate controler design
validateFcns(nlobjTracking,randn(3,1),randn(2,1));

%% Run Closed-loop Simulation in MATLAB
x = start'; % init state 
u = [0;0]; % init control 
% obtain code generation data for the NLMPC controller.
[coredata,onlinedata] = getCodeGenerationData(nlobjTracking,x,u);
mexfcn = buildMEX(nlobjTracking,'parkingRRTMex',coredata,onlinedata);

%%
% Initialize data before running simulation
xTrackHistory = x;
uTrackHistory = u;
mv = u;
Duration = 300;
Tsteps = Duration/Ts;

% plot(ax,xRef(:,1), xRef(:,2),'b-','LineWidth',2)
p = 3000;
pthObj.interpolate(p+1);
xRef = pthObj.States;

Xref = [xRef(2:p+1,:);repmat(xRef(end,:),Tsteps-p,1)];
%% 

% Run the closed-loop simulation in MATLAB using the MEX function.
for ct = 1:Tsteps
    % States
    xk = x;
    % Compute optimal control moves with MEX function
    onlinedata.ref = Xref(ct:min(ct+pTracking-1,Tsteps),:);
    [mv,onlinedata,info] = mexfcn(xk,mv,onlinedata);
    % Implement first optimal control move and update states.
    ODEFUN = @(t,xk) parkingVehicleStateFcnRRT(xk,mv);
    [TOUT,YOUT] = ode45(ODEFUN,[0 Ts], xk);
    x = YOUT(end,:)';
    % Save plant states for display.
    xTrackHistory = [xTrackHistory x]; %#ok<*AGROW>
    uTrackHistory = [uTrackHistory mv];
end


plot(xTrackHistory(1,:),xTrackHistory(2,:),'y-','LineWidth',2); % draw path

%% 


% %% 
% image = imread(image_file);
% dim1 = 512; dim2 = 512;
% imgResized = imresize(image,[dim1, dim2]);
% imshow(imgResized)


%% 
figure;
title('Control inputs')
subplot(2,1,1)
stairs(uTrackHistory(1,:))
grid on
xlabel('sample')
ylabel('speed (m/s)')
subplot(2,1,2)
stairs(rad2deg(uTrackHistory(2,:)))
grid on
xlabel('sample')
ylabel('steering (deg)')
% 
% % Analysis
% e1 = norm(xTrackHistory(2,1:num)-xRef(:,2)',inf);
% e2 = norm(xTrackHistory(2,1:num)-xRef(:,2)',inf);
% e3 = rad2deg(norm(xTrackHistory(3,1:num)-xRef(:,3)',inf));
% fprintf('Tracking error infinity norm in x (m), y (m) and theta (deg): %2.4f, %2.4f, %2.4f\n', e1, e2,e3);
% vFinal = uTrackHistory(1,end);
% deltaFinal = rad2deg(uTrackHistory(2,end));
% fprintf('Final control inputs of speed (m/s) and steering angle (deg): %2.4f, %2.4f\n', vFinal,deltaFinal);
