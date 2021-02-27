%% ME NEED F MOAR!!!!

NUM = numel(F(:,1));
x_1_moar = zeros(NUM+NUM-1,1);
x_2_moar = x_1_moar;

F_moar = zeros(NUM+NUM-1);
err_F = F_moar;

for i = 1:2:NUM+NUM-1
    for j = 1:2:NUM+NUM-1
        err_F(i,j)  = errF((i+1)/2,(j+1)/2);
        F_moar(i,j) = F((i+1)/2,(j+1)/2);
    end
    x_1_moar(i) = x_C((i+1)/2);
    x_2_moar(i) = x_s((i+1)/2);
end


for i = 2:2:NUM+NUM-2
    for j = 1:2:NUM+NUM-1
        err_F(i,j)  = (err_F(i-1,j)+err_F(i+1,j) )/2;
        F_moar(i,j) = (F_moar(i-1,j)+F_moar(i+1,j) )/2;
        
        err_F(j,i) = (err_F(j,i-1)+err_F(j,i+1) )/2;
        F_moar(j,i) = (F_moar(j,i-1)+F_moar(j,i+1) )/2;
    end
    x_1_moar(i) = (x_1_moar((i+1)) + x_1_moar(i-1) )/2;
    x_2_moar(i) = (x_2_moar((i+1)) + x_2_moar(i-1) )/2;
    
end


for i = 2:2:NUM+NUM-2
    for j = 2:2:NUM+NUM-2
        
        F_moar(i,j) = (F_moar(i-1,j)+F_moar(i+1,j)+...
        F_moar(i,j-1)+F_moar(i,j-1))/4;
        
        err_F(i,j) = (err_F(i-1,j)+err_F(i+1,j)+...
        err_F(i,j-1)+err_F(i,j-1))/4;
        
    end
end



figure(1)

surf(x_1_moar,x_2_moar, F_moar)
view(0,90)
shading faceted
xlim([min(x_C),max(x_C)]);
ylim([min(x_s),max(x_s)]);

xlabel('x_C');
ylabel('x_s');



figure(2)

surf(x_1_moar,x_2_moar, err_F)
view(0,90)
shading faceted
xlim([min(x_C),max(x_C)]);
ylim([min(x_s),max(x_s)]);

xlabel('x_C');
ylabel('x_s');