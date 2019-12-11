data=importdata("../data/output_R.md"); % 假设要读取R标记对应的动作次数；
No = data(:,1);
x  = data(:,2);
y  = data(:,3);
[m,indx] = max(x);
nx = m - x;
[minx,minxl]=findpeaks(nx,'minpeakdistance',30); %minx波谷值点  minxl：波谷值点对应的位置   波谷间最小间隔=30  

[m,indy] = max(y);
ny=m-y;
[miny,minyl]=findpeaks(ny,'minpeakdistance',30); %miny波谷值点  minyl：波谷值点对应的位置 波峰谷间最小间隔=30
count = (length(minx(:)) + length(miny(:)))/2 - 1                      %总的动作数；

%plot functions;

subplot(1,2,1)
hold on
plot(x);                                            %绘制原波形
plot(minxl,x(minxl),'*','color','R');                    %绘制最大值点

title("x对应的幅值图");
grid on;
subplot(1,2,2);
hold on
plot(y);                                            %绘制原波形
plot(minyl,y(minyl),'*','color','G');                 %绘制最大值点
title("y对应的幅值图");
grid on;