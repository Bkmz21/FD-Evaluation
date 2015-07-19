function data = readData(fid, detector)

    C = textscan(fid, '%s', 'delimiter', '\n');

    if (strcmp(detector, '') ~= 1)
        idx = find(~cellfun(@isempty, strfind(C{1}, ['use_' detector ' = true'])));
        if (isempty(idx))
           disp('invalid file');
           return;
        end   
    end
        
    idx = find(~cellfun(@isempty, strfind(C{1}, 'test_data')));
    if (isempty(idx))
        idx = find(~cellfun(@isempty, strfind(C{1}, 'clip_name')));
    end
    if (isempty(idx))
        disp('invalid file');
        return;
    end   
    
    buffer = C{1}(idx:size(C{1}, 1));
    colsName = sprintf('%s\t\n', buffer{1});
    dataText = sprintf('%s\t\n', buffer{2:length(buffer)});
    
    if (isempty(strfind(colsName , 'detect_rate')))
        data = textscan(dataText,'%s %u32 %u32 %u32 %u32 %u32 %u32 %u32 %u32 %f %f %f', 'delimiter', '\t');
    else
        data = textscan(dataText,'%s %u32 %u32 %u32 %u32 %u32 %u32 %u32 %f %f %f', 'delimiter', '\t');
        data(:,5) = [];
    end
    
end