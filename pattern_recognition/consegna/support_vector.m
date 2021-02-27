clc, close, clear

load('reportdataset');


data3 = DATA;
theclass = ones(numel(data3(1,:)),1);
for i = 1:numel(data3(1,:));
theclass(i) = 2*TARGET(i) -1;
end
data3 = data3';
%%
%Train the SVM Classifier
cl = svmtrain(data3,floor(theclass),'Kernel_Function','rbf');
 



