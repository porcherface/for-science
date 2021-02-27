%% f2rsb
% 
clc %%cancella le cose scritte su command window
close all %%chiude tutti gli handler e le figures
clear all %%cancella tutte le variabili nel workspace

tic %%cronometro
% load('matlabCIAOMOM.mat');

DATA = load('Q0Q1Q2.txt'); %% questo funziona solo se
                              %%%il file si trova nella stessa cartella
                              %%dello script 
% DATA = DATACopy;

ENTRIES = numel(DATA(:,1));   %trova il numero di colonne

NUM = sqrt(ENTRIES);

% F = zeros(NUM); %in realtà l'inizializzazione non è necessaria
                      %ma è consgliabile
% counter = 0;
% for i = 1:ENTRIES %%for cicla sugli elementi del vettore [1:entries] 
%                   %%i cicli for accettano sintassi tipo 
%                   %%for numero = vettore
%                   
%     N = numel(DATA(i,:));
%     
%     if(mod(i-1,NUM) == 0)
%     counter = counter+1;
%     end
%     
%     if(i<=NUM)
%     x_s(i) = DATA(i,2); %al contrario di F questi due sono allocati 
%     end
%     if(mod(i,NUM)==0)
%     x_C(counter) = DATA(i,1); %dinamicamente (non è una buona idea)
%     end
%     F(mod(i,NUM)+1,counter) = mean ( DATA(i,3:N) ); %il simbolo : senza nient'altro indica "tutti"
%     errF(mod(i,NUM)+1,counter) = var( DATA(i,3:N) );
%     
% A(i)=mean ( DATA(i,3:N));
% end

for t= 1:ENTRIES

q0(t) = mean(DATA(1:t,1));
v0(t) = var(DATA(1:t,1));
q1(t) = mean(DATA(1:t,2));
v1(t) = var(DATA(1:t,2));
q2(t) = mean(DATA(1:t,3));
v2(t) = var(DATA(1:t,3));
end

plot(1:t,q0,'r',1:t,q1,'b',1:t,q2,'k')