
clear F

for i= 1:960
for j= 1:540
F(j,961-i) = sum(firma(961-i,j,:));
if F(j,961-i) > 295
   F2(j,961-i)=1;
else
    F2(j,961-i)=0;
end
end
end
surf(F2)
colormap('gray')
shading flat
view(0,90)

xlim([100 850])
axis off
ylim([150 450])