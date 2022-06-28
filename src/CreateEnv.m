function env=CreateEnv(image_file, pStart,pGoal,plot_env)
% Start position
env.xStart=pStart.x;
env.yStart=pStart.y;
% Goal position
env.xGoal=pGoal.x;
env.yGoal=pGoal.y;
% obstacle parameters
% nobs = 5; xmin =1; xmax=8; ymin = 1; ymax =8; rmin=0.1;rmax=1;
%      env.obs.x = xmin+rand(1,nobs)*(xmax-xmin);
%      env.obs.y = ymin+rand(1,nobs)*(ymax-ymin);
% env.obs.radius = rmin+rand(1,nobs)*(rmax-rmin);
[img,centers,radii] = EnvReg(image_file,false);
env.xmin=0;
env.ymin=0;
env.xmax = size(img,1); 
env.ymax = size(img,2);

env.image = img;
env.centers = centers;
env.radii = radii;

env.obs.x= centers(:,1);
env.obs.y=centers(:,2);
env.obs.radius=radii;
% limit the canvas

% limit the maximum velocity
alpha=0.1; % maximum velocity ratio
env.vel_xmax=alpha*(env.xmax-env.xmin);    % Maximum Velocity in x direction
env.vel_xmin=-env.vel_xmax;                % Minimum Velocity in x direction
env.vel_ymax=alpha*(env.ymax-env.ymin);    % Maximum Velocity in y direction
env.vel_ymin=-env.vel_ymax;                % Minimum Velocity in y direction

if plot_env
    figure()
%     xobs=env.obs.x;
%     yobs=env.obs.y;
%     robs=env.obs.radius;
%     theta=linspace(0,2*pi,100);
    imshow(img);
    hold on;
    viscircles(centers,radii);
    plot(env.xStart,env.yStart,'bs','MarkerSize',12,'MarkerFaceColor','y');
    plot(env.xGoal,env.yGoal,'kp','MarkerSize',16,'MarkerFaceColor','g');
    hold off;
%     axis equal;
end