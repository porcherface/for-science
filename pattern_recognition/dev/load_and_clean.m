%% holdem manager graphs toolbox
%% riccetto88@gmail.com
clc
close all
clear all

%% input varibles
fileName = 'cashNew_toMatlab.png';

%% load data
IDATA=imread(fileName);

%% cycle settings
N=numel(IDATA(1,:,1));
M=numel(IDATA(:,1,1));

BLACKDATA = zeros(M,N);
RESULT = zeros(2,N);
%% set colors
background = [53,58,61];
white = [221 221 221];
green = [27 146 34];
%% remove boxes
for i = 1:N
    for j = 1:M
        
        IDATA(j,i,1) = 0;
        IDATA(j,i,3) = 0;
        if IDATA(j,i,2)>190
            IDATA(j,i,2) = 0;
        elseif IDATA(j,i,2) < 100
            IDATA(j,i,2) = 0;
        else
            IDATA(j,i,2) = 256;            
        end
        BLACKDATA(j,i) = sum(IDATA(j,i,:));
        RESULT(2,i) = RESULT(2,i) + j*BLACKDATA(j,i);
    end
    
    RESULT(1,i) = i;
    RESULT(2,i) = RESULT(2,i) / sum(BLACKDATA(:,i));
    
end

BLACKDATA(1,:) = 0;
%% reverse image
RESULT(2,:) = max(RESULT(2,:)) - RESULT(2,:);

%% smooth the graph a bit
numMean = 7;
K = numMean/2 + 0.5;
appo = RESULT(2,:);

for i = K:N-K
   
    appo(i) = sum(RESULT(2,i-K+1:i+K-1))/numMean;
    
end

RESULT(2,:) = appo;

%% set start & endpoint
Start = [0,0];
End   = [73352,79.76];

Len = End - Start;
OrgLen = [RESULT(1,end)-RESULT(1,1),RESULT(2,end)-RESULT(2,1)]; 

coeff = Len./OrgLen;


%% traslation operations
RESULT(1,:) = (RESULT(1,:) - RESULT(1,1) + Start(1))*coeff(1);
RESULT(2,:) = (RESULT(2,:) - RESULT(2,1) + Start(2))*coeff(2);

RESULT = RESULT';
%% plot the result graph
figure(1)
plot(RESULT(:,1),RESULT(:,2),'k')

%% stream operations

%fp=open('CashData.txt');
%fprintf(fp,RESULT);

%% do a linear fit

[c gof] = fit(RESULT(:,1),RESULT(:,2),'a*x+b');
[c2 gof2] = fit(RESULT(:,1),RESULT(:,2),'a*x');
[c3 gof3] = fit(RESULT(:,1),RESULT(:,2),'a*(x^0.5)');

xFit = linspace(RESULT(1,1),RESULT(end,1),100);
yFit1 = c.a*xFit+c.b;
yFit2 = c2.a*xFit;
yFitS = c3.a*sqrt(xFit);

clc

%% and plot it
figure(1)
hold on
plot(xFit,yFit1,'-','Color','r')
plot(xFit,yFit2,'-','Color','b')
plot(xFit,yFitS,'-','Color','g');



