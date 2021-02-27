function [NT] = weights(T,CBET,FCB,VPIP,PFR)


coeff1 = 38.8;
coeff2 = 46.153;
coeff3 = 9.1101;
N = [numel(CBET(:,1)),numel(CBET(1,:))];

randv1 = rand(N) + rand(N) + 1;

randv2 = rand(N);
% randv1 = randv1';
randv3 = rand(N)+ rand(N)+rand(N)+1 ;
% randv2= randv2';
DIFF = VPIP - PFR;
totcoef =0;% 1.16578;
NT = T(:,1) + totcoef*((CBET - 0.6235266).*randv1*coeff1 + ...
    (FCB - 0.5704222).*randv3*coeff2 - coeff3*DIFF.*randv2);


NT = NT'/10;