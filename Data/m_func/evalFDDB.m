function [data, label, color, marker, data_label] = evalFDDB(alg, msz, sf, knn_set)

    alg_id = 0;
    for alg_type = size(alg, 2):-1:1
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
                             
            fid_res_disc = fopen([alg{alg_type}{2} 'test_' file_id '_' alg{alg_type}{3} '_FDDB_disc.txt'], 'w');
            fid_res_cont = fopen([alg{alg_type}{2} 'test_' file_id '_' alg{alg_type}{3} '_FDDB_cont.txt'], 'w');
            for set_id = 1:10
                FDDB_set_id = num2str(set_id);
                if set_id < 10
                    FDDB_set_id = ['0' FDDB_set_id];
                end
                    
                FDDB_path = 'G:/QA/fddb/';
                FDDB_fold = ['G:/QA/fddb/FDDB-folds/FDDB-fold-' FDDB_set_id '.txt'];
                FDDB_annot = ['G:/QA/fddb/FDDB-folds/FDDB-fold-' FDDB_set_id '-ellipseList.txt'];
                FDDB_det = [alg{alg_type}{2} 'test_' file_id '__' alg{alg_type}{3} '_FDDB_' FDDB_set_id '.txt'];
<<<<<<< HEAD
<<<<<<< HEAD
                system(['fddb_eval.exe ' FDDB_path ' ' FDDB_fold ' ' FDDB_det ' ' FDDB_annot]);
=======
                system(['fddb_eval_mod_0.8.exe ' FDDB_path ' ' FDDB_fold ' ' FDDB_det ' ' FDDB_annot]);
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
                system(['fddb_eval_mod_0.8.exe ' FDDB_path ' ' FDDB_fold ' ' FDDB_det ' ' FDDB_annot]);
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079

                fid = fopen('tempDiscROC.txt', 'r');
                val = textscan(fid, '%f', 'delimiter', ' ');
                fprintf(fid_res_disc, '%f %d %d\r\n', val{1}(1), val{1}(2), val{1}(3));
                fclose(fid);
                
                fid = fopen('tempContROC.txt', 'r');
                val = textscan(fid, '%f', 'delimiter', ' ');
                fprintf(fid_res_cont, '%f %d\r\n', val{1}(1), val{1}(2));
                fclose(fid);                
            end  
            fclose(fid_res_disc); 
            fclose(fid_res_cont);
        
            fid = fopen([alg{alg_type}{2} 'test_' file_id '_' alg{alg_type}{3} '_FDDB_disc.txt'], 'r');
        
            if fid ~= -1
                data{alg_id, i} = textscan(fid, '%f %d %d', 'delimiter', ' ');                
                
                label{alg_id} = alg{alg_type}{1};
                color{alg_id} = alg{alg_type}{4};
                marker{alg_id} = alg{alg_type}{5};
                data_label{i} = ['m' int2str(msz) '_s' sf '_k' int2str(knn)]; 
                
                fclose(fid); 
            end      
        end
    end

end