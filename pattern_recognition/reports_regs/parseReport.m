clc
close all
clear all

NUM_ENTRIES = 111;
NUM_RAZOR = 500;
counter = 0;
datacounter = 0;
% %
DATA = zeros(NUM_ENTRIES,4);
TARGET = zeros(NUM_ENTRIES,2);
minb = -0;
maxb = -0;

SOIL = 0;

% %
for i = 1:NUM_ENTRIES
    
    %load report
    reportName = strcat('Report' , int2str(i) , '.csv');
    [a] = textread(reportName,'%q');
    
    
    %get every item
    for j = 2:numel(a)
        
        LOG = a{j};
        
        %parse
        TMP = strsplit(LOG,',"');
        for k = 3:13
            C = find(TMP{k} == ',');
            S = TMP{k};
            S(C) = '.';
            TMP{k} = str2double(S);
                
% %                  s={'the table'};
% %      r=strrep(s,'the ','')
% % % r = 'table' % <- a CELLSTR
% % % see also: regexprep

%             disp(TMP{2});
        end
%         name type hands      vpip pfr 3bet     f3bet WTSD Agg      cbet turncbet fcbet     bb100
        if(TMP{3}>NUM_RAZOR)
            datacounter = datacounter+1;
%             DATA(datacounter,1) = TMP{3};
            DATA(datacounter,1) = TMP{4};%v
            DATA(datacounter,2) = TMP{5};%p
            DATA(datacounter,5) = TMP{6};%3
            DATA(datacounter,6) = TMP{7};%f
%             DATA(datacounter,6) = TMP{8};%sd
            DATA(datacounter,7) = TMP{9};%ag
            DATA(datacounter,3) = TMP{10};%cb
% %             DATA(datacounter,9) = TMP{11};%trncb
            DATA(datacounter,4) = TMP{12};%fcbet
%             DATA(datacounter,11) = TMP{13};
            
% %             TARGET(datacounter,1) = TMP{13}>=maxb;
% %             TARGET(datacounter,2) = TMP{13}<maxb;

            
            TARGET(datacounter,1) = TMP{13};
            TARGET(datacounter,2) = TMP{13};

            
%             disp(TMP{13});
            A(datacounter) = TMP{13};
%             TARGET(datacounter,2) = (TMP{13}>minb * TMP{13}<maxb);
%             TARGET(datacounter,3) = TMP{13}<=minb;
        end
    end
    
    
    waitbar(i/NUM_ENTRIES);
end

%%
VPIP =  DATA(:,1)/100;
CBET = DATA(:,3)/100;
FCB  = DATA(:,4)/100;
PFR =  DATA(:,2)/100;
%%
ADJ = weights(TARGET,CBET,FCB,VPIP,PFR)*2;
%% %%
figure(1)
hist(ADJ)
figure(2)
 hist(TARGET(:,1))
% hist(CBET)
%% reverse data
DATA = DATA'/100;
for i = 1:datacounter 
    TARGET(i,1) = ADJ(i)>SOIL;
    
    TARGET(i,2) = ADJ(i)<=SOIL;

end
TARGET = TARGET';





save('reportdataset.mat','DATA','TARGET');
% clear all


