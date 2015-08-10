<<<<<<< HEAD
<<<<<<< HEAD
function [true, false, recall, precision, F_score] = calcMetrics(data, F_alpha, func, col_id_face, col_id_true, col_id_false)
=======
function [true, false, recall, precision, F1] = calcMetrics(data, F1_alpha, func, col_id_face, col_id_true, col_id_false)
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
function [true, false, recall, precision, F1] = calcMetrics(data, F1_alpha, func, col_id_face, col_id_true, col_id_false)
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
    
    if nargin < 6
        col_id_face = 3;
        col_id_true = 5;
        col_id_false = 6;          
    end
    
    if size(data, 2) < 3
<<<<<<< HEAD
<<<<<<< HEAD
        F_alpha = 0.5;
=======
        F1_alpha = 0.5;
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
        F1_alpha = 0.5;
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
    end
    
    for j = 1:size(data, 1)   
        index = [];
        for i = 1:size(data, 2);
            index = [index i];
            if (isempty(data{j, i}))                
                continue;
            end
            
            val = data{j, i};
 
            true(index, j) = func(val{col_id_true}(:));                           
            false(index, j) = func(val{col_id_false}(:)); 
            
            if col_id_face == -1
                total_objects = 1;
            else
                total_objects = func(val{col_id_face}(:));
            end
            total_detections = true(index, j) + false(index, j);            
              
            recall(index, j) = true(index, j) / total_objects;
            precision(index, j) = true(index, j) ./ total_detections;
               
<<<<<<< HEAD
<<<<<<< HEAD
            alpha = F_alpha;
=======
            alpha = F1_alpha;
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
            alpha = F1_alpha;
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
            if alpha == -1
                switch i
                    case 1
                        alpha = 0.2;
                    case size(data, 2)
                        alpha = 0.8; 
                    otherwise  
                        alpha = 0.5; 
                end   
            end
            
<<<<<<< HEAD
<<<<<<< HEAD
            F_temp(index) = 1 ./ (alpha ./ precision(index, j) + (1 - alpha) ./ recall(index, j));
=======
            F1_temp(index) = 1 ./ (alpha ./ precision(index, j) + (1 - alpha) ./ recall(index, j));
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
            F1_temp(index) = 1 ./ (alpha ./ precision(index, j) + (1 - alpha) ./ recall(index, j));
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
            
            index = [];
        end
        
<<<<<<< HEAD
<<<<<<< HEAD
        F_score(j) = roundn(mean(F_temp(:)), -3);
=======
        F1(j) = roundn(mean(F1_temp(:)), -3);
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
        F1(j) = roundn(mean(F1_temp(:)), -3);
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
    end

end

