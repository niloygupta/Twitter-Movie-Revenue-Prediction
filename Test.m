function FinalRevenue = Test
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
load TestSet.txt
disp(TestSet);
R=TestSet*P;
disp(R);
FinalRevenue=exp(R)*Wk;
disp(FinalRevenue)
end

