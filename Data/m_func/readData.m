function [data, label, color, marker, data_label] = readData(path, alg, msz, sf, knn_set)

    alg_id = 0;
    for alg_type = 1:1:size(alg, 2)
        if alg{alg_type}{1}(1) == '-'
            continue; 
        end;
        alg_id = alg_id + 1;                
    
        for i = 1:size(knn_set, 2)
            knn = knn_set(i);
            
            file_id = [int2str(msz) '_' sf '_' int2str(knn)];          
            if ~isempty(strfind(alg{alg_type}{3}, 'FDPL'))
                file_id = '20_1.05_5'; 
            end  
            if ~isempty(strfind(alg{alg_type}{3}, 'FDLIB'))
                file_id = ['20_1.05_' int2str(4 + -2 * knn)]; 
            end 
        
            fid = fopen([path alg{alg_type}{2} 'test_' file_id '_' alg{alg_type}{3} '.txt'], 'r');
            if fid ~= -1
                data{alg_id, i} = parseFile(fid, alg{alg_type}{3});

                label{alg_id} = alg{alg_type}{1};
                color{alg_id} = alg{alg_type}{4};
                marker{alg_id} = alg{alg_type}{5};
                data_label{i} = ['m' int2str(msz) '_s' sf '_k' int2str(knn)]; 

                fclose(fid); 
            end
        end
    end

end