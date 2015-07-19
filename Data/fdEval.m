close all; 
clear all;
addpath('m_func');

video = 0;

if video
    'video benchmark'
    alg{1}             = { '-FastCNN-weak', 'CNN/type_1/', 'CNN', [1, 0, 0], '+' };
    alg{size(alg,2)+1} = { '-FastCNN-strong', 'CNN/type_3/', 'CNN', [1, 0, 0], '*' };
    alg{size(alg,2)+1} = { 'FastCNN-default', 'CNN/type_2/', 'CNN', [1, 0, 0], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-lbp', 'VJ/type_3/', 'VJ', [0, 0, 1], 'x' };
    alg{size(alg,2)+1} = { 'OpenCV-alt', 'VJ/type_2/', 'VJ', [0, 0, 1], '+' };
    alg{size(alg,2)+1} = { 'OpenCV-default', 'VJ/type_1/', 'VJ', [0, 0, 1], 'o' };
    alg{size(alg,2)+1} = { 'SURF-32', 'SURF/type_2/', 'SURF', [0, 1, 0], '+' };
    alg{size(alg,2)+1} = { 'SURF-24', 'SURF/type_1/', 'SURF', [0, 1, 0], 'o' };
    alg{size(alg,2)+1} = { 'PICO', 'PICO/type_1/', 'PICO', [0.8, 0.6, 0.4], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Pham', 'MTP/type_1/', 'MTP', [1 0.8 0], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Koestinger', 'AFLW/type_1/', 'AFLW', [0 0.8 1], 'o' };

    benchmark{1} = { 'CAM', 'CAM_TEST/', [80], [] };
    benchmark{2} = { 'CANTEEN', 'CANTEEN_TEST/', [80 160], [] };
    benchmark{3} = { 'HIMYM', 'HIMYM_TEST/', [40 80], [] };
    benchmark{4} = { 'CP', 'CP_TEST/', [40 80], [1 12; 13 24; 25 51; 52 78] }; %[1 12; 13 24; 25 51; 52 78]

    agg_data = @sum;
else
    'image benchmark';
    alg{1}             = { 'OpenCV-default', 'VJ/type1/', 'VJ', [0, 0, 1], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-alt', 'VJ/type2/', 'VJ', [0, 0, 1], '+' };
    alg{size(alg,2)+1} = { 'OpenCV-alt2', 'VJ/type3/', 'VJ', [0, 0, 1], '*' };
    alg{size(alg,2)+1} = { 'OpenCV-alt-tree', 'VJ/type5/', 'VJ', [0, 0, 1], 's' };
    alg{size(alg,2)+1} = { 'OpenCV-lbp', 'VJ/type4/', 'VJ', [0, 0, 1], 'x' };
    alg{size(alg,2)+1} = { 'Matlab-CART', 'MVJ/type1/', 'MVJ', [0.5, 0, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'Matlab-LBP', 'MVJ/type2/', 'MVJ', [0.5, 0, 0.5], '+' };
    alg{size(alg,2)+1} = { 'SURF-24', 'SURF_correct/type1/', 'SURF', [0, 1, 0], 'o' };
    alg{size(alg,2)+1} = { 'SURF-32', 'SURF_correct/type2/', 'SURF', [0, 1, 0], '+' };
    alg{size(alg,2)+1} = { 'PICO', 'PICO/type1/', 'PICO', [0.8, 0.6, 0.4], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Koestinger', 'AFLW_correct/type1/', 'AFLW', [0 0.8 1], 'o' };
    alg{size(alg,2)+1} = { 'OpenCV-Pham', 'MTP/type1/', 'MTP', [1 0.8 0], 'o' };
    alg{size(alg,2)+1} = { 'FDPL-small', 'FDPL/type1/', 'FDPL', [0, 0.5, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'FDPL-large', 'FDPL/type2/', 'FDPL', [0, 0.5, 0.5], '+' };
    alg{size(alg,2)+1} = { 'FDLIB', 'FDLIB/type1/', 'FDLIB', [0.75, 0.75, 0.5], 'o' };
    alg{size(alg,2)+1} = { 'CompactCNN (our)', 'CNN/type2/', 'CNN', [1, 0, 0], 'o' };
    alg{size(alg,2)+1} = { 'CompactCNN-weak (our)', 'CNN/type1/', 'CNN', [1, 0, 0], '+' };

    benchmark{1} = { 'FDDB', 'FDDB_TEST/', [20 40 80], [] };
    benchmark{2} = { 'AFW', 'AFW_TEST/', [20 40 80], [] };

    agg_data = @mean;
end

knn = [1 2 3];
F1_alpha = -1;
agg_score = @mean; %@median

%% Evaluation

score = [];
test_label = [];
for test_id = 1:size(benchmark, 2)
    test_id;
    
    for i = 1:size(benchmark{test_id}{3}, 2);
        msz = benchmark{test_id}{3}(i);
        if (msz == 20)
            sf = '1.05';             
        else
            sf = '1.1';
        end 
               
        %% Read data

        [data, label, color, marker, data_label] = readData(benchmark{test_id}{2}, alg, msz, sf, knn);

        %% Calculation metrics
        
        subdata_idx = benchmark{test_id}{4};
        if isempty(subdata_idx)
            [true, false, recall, precision, F1] = calcMetrics(data, F1_alpha, agg_data);
            score(size(score, 1)+1, :) = F1;
            test_label{size(test_label, 2)+1} = [benchmark{test_id}{1} '-' int2str(msz)];
        else
            for subdata_id = 1:size(subdata_idx, 1)
                min_id = subdata_idx(subdata_id, 1);
                max_id = subdata_idx(subdata_id, 2);  
             
                for sj = 1:size(data, 1)   
                    for si = 1:size(data, 2);
                        for sk = 1:size(data{sj, si}, 2);
                            subdata{sj, si}{sk} = data{sj, si}{sk}(min_id:max_id);
                        end
                    end
                end
                
                [true, false, recall, precision, F1] = calcMetrics(subdata, F1_alpha, agg_data);
                score(size(score, 1)+1, :) = F1;
                test_label{size(test_label, 2)+1} = [benchmark{test_id}{1} '-' int2str(msz) ', set' int2str(subdata_id)];
            end  
        end      
    end 
end

%% Comparison

for test_id = 1:size(score, 1)
    number = 0;
    val_max = 0;
    for i = 1000:-1:0
        val = i / 1000;
        idx = find(score(test_id, :) == val);
        if ~isempty(idx)
            number = number + 1;
            val_max = max(val, val_max);
            for k = 1:size(idx,2)
                comparison{test_id, idx(k)} = [number (val/val_max-1)*100];
            end
        end
    end
end

for alg_id = 1:size(score, 2)   
    mean_score(alg_id) = agg_score(score(:, alg_id));
end

for alg_id = 1:size(score, 2)
    diff = [];
    for test_id = 1:size(score, 1)
        val = comparison{test_id, alg_id}(2);
        diff = [diff val];
        
        str_val = num2str(roundn(val,-3),3);
        if val ~= 0
            str_val = [str_val '%'];
        else
            str_val = '0';
        end
        comparison{test_id, alg_id} = {[num2str(comparison{test_id, alg_id}(1)) ' (' str_val ')']};
    end
    mean_diff(alg_id) = agg_score(diff);
end

%mean_diff = [91.3 12.5 11.1 11.3 18 40.7 11.1 39.8 69.2 39.1 73.6 16.8 47.5 0.15 0.2 27];

score_table(2:size(test_label,2)+1, 1) = test_label;
score_table(1, 2:size(label,2)+1) = label;
comparison_table = score_table;

score_table(2:size(score,1)+1, 2:size(score,2)+1) = num2cell(score);
score_table(size(score_table,1)+1, 2:size(mean_score,2)+1) = num2cell(mean_score(:));
score_table(size(score_table,1),1) = {'mean'};
score_table = score_table'

comparison_table(2:size(comparison,1)+1, 2:size(comparison,2)+1) = comparison;
comparison_table(size(comparison_table,1)+1, 2:size(mean_diff,2)+1) = num2cell(mean_diff(:));
comparison_table(size(comparison_table,1),1) = {'mean'};
comparison_table = comparison_table'

figure('OuterPosition', [0 0 1000 800]);
ord_score(:,1) = num2cell(mean_score);
ord_score(:,2) = color;
ord_score(:,3) = label;
ord_score = sortcell(ord_score)';
graphData(cell2num(ord_score(1,:)), ord_score(3,:), ord_score(2,:), marker, [], 'score');

figure('OuterPosition', [0 0 1000 800]);
ord_diff(:,1) = num2cell(mean_diff + 100);
ord_diff(:,2) = color;
ord_diff(:,3) = label;
ord_diff = sortcell(ord_diff)';
graphData(cell2num(ord_diff(1,:)), ord_diff(3,:), ord_diff(2,:), marker, [], 'diff F');

%friedman
%[p,tbl,stats] = friedman(score,1);
%multcompare(stats,0.01)
%myfriedman(score,1)