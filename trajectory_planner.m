clc;
clear;
close all;
%% look at the environment
plot_env = true;
%% run PSO trajectory planner
image_file = "sample.png";

pStart.x = randi([10,50]);
pStart.y = randi([10,50]);
pGoal.x = randi([100,288]);
pGoal.y = randi([100,288]);

GlobalBest2 = PSO_planner(image_file,pStart,pGoal);