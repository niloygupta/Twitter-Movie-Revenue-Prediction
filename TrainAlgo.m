function P = TrainAlgo
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
load DataSet.txt
load FuzzyQualityScore.txt
DataSet(:,4)=FuzzyQualityScore*100;
load WeekendRevenue.txt
load Revenue
Y=log(Revenue./WeekendRevenue);
P=DataSet\Y;
end

