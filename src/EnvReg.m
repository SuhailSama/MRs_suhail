function [img_resized,centers, radii]= EnvReg(image_file_name, IsPlot)
% IMPORTANT: This function assumes one type of objects
% Takes an image as an nput and returns the centers and radii of the objects (cells) in the images
% Inputs: image_file_name = string
%         IsPlot = true OR false
%
if nargin<2
    IsPlot = false;
end

%% Read image
image = imread(image_file_name);
dim1 = 256; dim2 = 256;
imgGray = rgb2gray(image);
imgGray = imresize(imgGray,[dim1, dim2]);

%% Adjust to use darker and brighter pixels
imgGray_adj = imadjust(imgGray);

%% Segment image with threshold

imgSegmented = segmentImage(imgGray_adj);
[imgSegmented,~] = filterRegions(imgSegmented); % remove borders

%% Find centers and radii of objects
stats = regionprops('table',imgSegmented,'Centroid',...
    'MajorAxisLength','MinorAxisLength');
diameters = mean([stats.MajorAxisLength stats.MinorAxisLength],2);
centers = stats.Centroid;
radii = diameters/2;

img_resized = imresize(image,[dim1, dim2]);
if IsPlot
    figure
    imshowpair(imgSegmented,img_resized, "montage")
    title("segmented VS original")
    hold on
    viscircles(centers,radii)
    hold off
end

end

