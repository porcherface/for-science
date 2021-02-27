function [Z nx ny] = picstart()

%% caricamento
z = imread('minigatto.png');
nx = numel(z(1,:,1));
ny = numel(z(:,1,1));

Z = zeros(ny,nx);

%% tolgo il colore
for i = 1:nx
    for j = 1:ny
        
        Z(j,i) = sum(z(end-j+1,end-i+1,:));
    end
end

Z = Z / max(max(Z));

%% pulizia immagine
for i = 1:nx
    for j = 1:ny
        
        if Z(j,i) > 0.5
            Z(j,i) = 0;
        else
            Z(j,i) = 1;
        end
    end
end
