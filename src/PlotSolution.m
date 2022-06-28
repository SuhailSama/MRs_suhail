function PlotSolution(sol,env,iter,BestCost)
    centers=env.centers;
    radii=env.radii; 
    img = env.image;

%     xobs=env.obs.x;
%     yobs=env.obs.y;
%     robs=env.obs.radius;
    
    XS=sol.XS;
    YS=sol.YS;
    xx=sol.xx;
    yy=sol.yy;
    
%     theta=linspace(0,2*pi,100);
    imshow(img)
    hold on;
    viscircles(centers,radii)
    plot(xx,yy,'g','LineWidth',2);
    plot(XS,YS,'bo');
    plot(env.xStart,env.yStart,'bs','MarkerSize',12,'MarkerFaceColor','y');
    plot(env.xGoal,env.yGoal,'kp','MarkerSize',16,'MarkerFaceColor','g');
    xlabel(['Iteration ' num2str(iter) ': Minimal cost=' num2str(BestCost)]);
    hold off;
%     grid on;
%     axis equal;
end