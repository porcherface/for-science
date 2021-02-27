clear all
close all
clc

DATA = load('QSITE_QSTATE.txt');

TIME_ENTRIES = numel(DATA(:,1));
SITE_ENTRIES = numel(DATA(1,:));

Q0 = zeros(TIME_ENTRIES,1);
Q1 = zeros(TIME_ENTRIES,1);

j0 = 1:2:SITE_ENTRIES-1;
j1 = j0+1;

for i = 1:TIME_ENTRIES

    Q0(i) = mean(  DATA(i,j0)  );
    Q1(i) = mean(  DATA(i,j1)  );
    
    
end
    
figure(1)
plot(Q0)

figure(2)
plot(Q1)