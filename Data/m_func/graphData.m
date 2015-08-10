function graphData(data, label, color, marker, axis_name, graph_name)
   
    set(gca,'DefaultTextFontSize',16,'DefaultTextFontName','Arial'); 
    set(gca,'fontsize',12);
    hold on

    if size(data, 2) == 2
        data_Y = data{1};
        data_X = data{2};
        
        for j = 1:size(data_Y, 2)    
            plot(data_X(:, j),data_Y(:, j),'k','Color',color{j},'LineWidth',2,'Marker',marker{j},'MarkerSize',8,'MarkerFaceColor',color{j});
        end
 
        max_x = max(max(data_X,[],2));
        if max_x < 1
            xlim([0, 1]);
        else
            xlim([0, max_x]);
        end
        ylim([0, 1]);        
        grid on;
<<<<<<< HEAD
<<<<<<< HEAD
        axis('square');
        
=======
 
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
 
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
        legend(label, 4);
        BY = get(gca,'YTick');
        BX = get(gca,'XTick'); 
        ylabel(axis_name{1},'Rotation',0,'Position',[BX(1) BY(size(BY,2))+0.015],'FontSize',14);
        xlabel(axis_name{2},'Position',[BX(size(BX,2))/2 BY(1)-0.06],'FontSize',14);
        title(graph_name,'FontSize',14);
    else
        if size(data, 1) == 1
            data(2, :) = 0;
        end
        
        max_val = max(max(data))
        
        h = bar(data);
        xlim([0.5, 1.5]);     
        if max_val > 1
            ylim([-150, 150]);
        else
            ylim([-1.5, 1.5]);            
        end
        set(gca,'XTick', [1:length(label)]);
        title(graph_name,'FontSize',14);
        
        for i = 1:length(h)
            set(h(i), 'FaceColor', color{i});
    
            XDATA = get(get(h(i),'Children'),'XData');
            YDATA = get(get(h(i),'Children'),'YData');
            for j = 1:size(XDATA, 2)
                x = XDATA(1,j)+(XDATA(3,j)-XDATA(1,j))/2;
                y = YDATA(2,j);
                
                if max_val > 1
                    t = num2str(roundn(y-100,-2),4);
<<<<<<< HEAD
<<<<<<< HEAD
                    if y > 10 
                        t = num2str(roundn(y-100,-2),4);
                    end;
=======
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
                    if YDATA(2,j) ~= 100
                        t = [t '%'];
                    else
                        t = '100%';
                    end

<<<<<<< HEAD
<<<<<<< HEAD
                    text(x,y+30,t,'Color',color{i},'FontSize',12,'HorizontalAlignment','center','Rotation',90)
                    text(x,-5,label{i},'Color',color{i},'FontSize',14,'HorizontalAlignment','right','Rotation',60)
                else
                    t = num2str(roundn(y,-2),4);  
                    text(x,y+0.2,t,'Color',color{i},'FontSize',12,'HorizontalAlignment','center','Rotation',90)
                    text(x,-0.05,label{i},'Color',color{i},'FontSize',14,'HorizontalAlignment','right','Rotation',60) 
=======
=======
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
                    text(x,y+20,t,'Color',color{i},'FontSize',10,'HorizontalAlignment','center','Rotation',90)
                    text(x,-5,label{i},'Color',color{i},'FontSize',12,'HorizontalAlignment','right','Rotation',60)
                else
                    t = num2str(roundn(y,-2),4);  
                    text(x,y+0.1,t,'Color',color{i},'FontSize',10,'HorizontalAlignment','center','Rotation',90)
                    text(x,-0.05,label{i},'Color',color{i},'FontSize',12,'HorizontalAlignment','right','Rotation',60) 
<<<<<<< HEAD
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
=======
>>>>>>> 684e4945fb80c5c016a15e87ced26dca18726079
                end
            end
        end
    end

end

