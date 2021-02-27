clc
close all
clear all

NUM_ENTRIES = 10;
NUM_RAZOR = 200;
counter = 0;
datacounter = 0;
% %
DATA = zeros(NUM_ENTRIES,10);
TARGET = zeros(NUM_ENTRIES,3);
minb = -5;
maxb = 0;
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
%             disp(TMP{2});
        end
        
        if(TMP{3}>NUM_RAZOR)
            datacounter = datacounter+1;
            DATA(datacounter,1) = TMP{3};
            DATA(datacounter,2) = TMP{4};
            DATA(datacounter,3) = TMP{5};
            DATA(datacounter,4) = TMP{6};
            DATA(datacounter,5) = TMP{7};
            DATA(datacounter,6) = TMP{8};
            DATA(datacounter,7) = TMP{9};
            DATA(datacounter,8) = TMP{10};
            DATA(datacounter,9) = TMP{11};
            DATA(datacounter,10) = TMP{12};
%             DATA(datacounter,11) = TMP{13};
            
            TARGET(datacounter,1) = TMP{13}>=maxb;
            TARGET(datacounter,2) = (TMP{13}>minb * TMP{13}<maxb);
            TARGET(datacounter,3) = TMP{13}<=minb;
        end
    end
    
    
    waitbar(i/NUM_ENTRIES);
end


%%reverse data
DATA = DATA';
TARGET = TARGET';
