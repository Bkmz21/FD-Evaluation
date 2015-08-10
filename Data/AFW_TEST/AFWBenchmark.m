close all; 
clear all;
addpath('../m_func');

    alg{1}             = { 'OpenCV-default', 'VJ/type1/', 'VJ', [0, 0, 1], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-alt', 'VJ/type2/', 'VJ', [0, 0, 1], '+' };
    alg{size(alg,2)+1} = { 'OpenCV-alt2', 'VJ/type3/', 'VJ', [0, 0, 1], '*' };
    alg{size(alg,2)+1} = { 'OpenCV-alt-tree', 'VJ/type5/', 'VJ', [0, 0, 1], 's' };
    alg{size(alg,2)+1} = { 'OpenCV-lbp', 'VJ/type4/', 'VJ', [0, 0, 1], 'x' };
    alg{size(alg,2)+1} = { 'Matlab-CART', 'MVJ/type1/', 'MVJ', [0.5, 0, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'Matlab-LBP', 'MVJ/type2/', 'MVJ', [0.5, 0, 0.5], '+' };
    alg{size(alg,2)+1} = { 'SURF-24', 'SURF/type1/', 'SURF', [0, 1, 0], 'o' };
    alg{size(alg,2)+1} = { 'SURF-32', 'SURF/type2/', 'SURF', [0, 1, 0], '+' };
    alg{size(alg,2)+1} = { 'PICO', 'PICO/type1/', 'PICO', [0.8, 0.6, 0.4], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Koestinger', 'AFLW/type1/', 'AFLW', [0 0.8 1], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Pham', 'MTP/type1/', 'MTP', [1 0.8 0], 'o' };
    alg{size(alg,2)+1} = { 'FDPL-small', 'FDPL/type1/', 'FDPL', [0, 0.5, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'FDPL-large', 'FDPL/type2/', 'FDPL', [0, 0.5, 0.5], '+' };
    alg{size(alg,2)+1} = { 'FDLIB', 'FDLIB/type1/', 'FDLIB', [0.75, 0.75, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'CompactCNN (our)', 'CNN/type2/', 'CNN', [1, 0, 0], 'o' };
    alg{size(alg,2)+1} = { 'CompactCNN-weak (our)', 'CNN/type1/', 'CNN', [1, 0, 0], '+' };

min_size = [40];%[20 40 80 200]
knn = [1 2 3];%[1 2 3 4 5]

use_ROC = 0;

use_F_score = 0;
F_alpha = -1;

for i = 1:size(min_size, 2);

    msz = min_size(i);
    if (msz == 20)
        sf = '1.05';             
    else
        sf = '1.1';
    end 

    %% Read data

    [data, label, color, marker, data_label] = readData('', alg, msz, sf, knn);

    %% Calculation metrics
    
    [true, false, recall, precision, F_score] = calcMetrics(data, F_alpha, @sum);

    %% Graph data
    
    if i == 1
        figure('OuterPosition', [0 0 1000 800]);
    end
    subplot(1, size(min_size, 2), i);

    if use_F_score
        name = ['F-score for AFW-' int2str(msz)];        
        graphData(F_score, label, color, marker, [], name);
    else
        if use_ROC
            name = ['ROC-curve for AFW-' int2str(msz)];
            graphData({recall, false}, label, color, marker, {'Recall', 'False positive'}, name);   
        else
            name = ['PR-curve for AFW-' int2str(msz)];
            graphData({precision, recall}, label, color, marker, {'Precision', 'Recall'}, name);
        end
    end
end