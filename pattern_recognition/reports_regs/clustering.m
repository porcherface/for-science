clc
close all
clear all

load('reportdataset.mat')

%%
CLUSTERDATA = DATA;
CLUSTERDATA(6:7,:) = TARGET(:,:);

CLUSTERDATA = CLUSTERDATA';
%%
[cidx2,cmeans2] = kmeans(CLUSTERDATA,3,'dist','cityblock');
[silh2,h] = silhouette(CLUSTERDATA,cidx2,'sqeuclidean');

%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%
%% hierarchical
clc
close all
clear all

load('reportdataset.mat')

CLUSTERDATA = DATA(1:5,:) ;
CLUSTERDATA = CLUSTERDATA';


eucD = pdist(CLUSTERDATA,'euclidean');
clustTreeEuc = linkage(eucD,'average');
cophenet(clustTreeEuc,eucD)

%%
[h,nodes] = dendrogram(clustTreeEuc,0);
h_gca = gca;
h_gca.TickDir = 'out';
h_gca.TickLength = [.002 0];
h_gca.XTickLabel = [];