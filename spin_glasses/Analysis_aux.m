
close all
clear all

% //graphics_toolkit('gnuplot')


FILENAME = ...
    strcat('H:\BRAND_NEW_WORK_TO_DO\'...
    ,'build-MULTISPINCODING-Desktop_Qt_5_2_0_MinGW_32bit_qt_520-Debug\'...
    ,'mylog_bimodal_glass_z6_2spin_lowT_Qs_REP_LP.txt');

RAWDATA = dlmread(FILENAME);

Temps = RAWDATA(1,:);

R = numel(RAWDATA(1,:));
T = numel(RAWDATA(:,1));

LOG = RAWDATA(:,:);

figure(1)
hold off
	
%% meansssssss
MEANLOG = LOG;
for i = 1:R
	for t = 1:T
	
	MEANLOG(t,i) = mean(LOG(1:t,i));
	
	end
end 
	
	
	
for i = 1:R
	
	figure(1);
	plot(1:T,LOG(:,i),'Color',[i/R , 0 , (1 - i/R)])
	hold on

end

figure(2)
hist(MEANLOG(T,:));
figure(3)
hist(LOG(T,:))
	
	