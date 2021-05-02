%% US_Radar_MATLAB.m
% _Ver.:      1.0.0
% _Author:    Mohanad M. Marzouk
% _Date:      210503_Initial
% _Last Mod.: 210503
% _Brief:
%   __ Matlab code for sonar detection plot
%-----------------------------------------------------------------------------------------
%% Graph Customization
clear,clc;
figure('Units','Normalized','OuterPosition',[0,0,1,1]);
%% Draw scale data
th = linspace(0,pi,1000);
R = 10:10:100;
for ii = 1:length(R)
  x = R(ii)*cos(th);
  y = R(ii)*sin(th);
  plot(x,y,'Color',[0.603922,0.803922,0.196078],'LineWidth',1);
  hold on;
end
%% Draw Axis data
x0 = [0,100,0,0,0,0];
x1 = [0,100,86.60,50,-50,-86.60];
y0 = [0,0,0,0,0,0];
y1 = [100,50,86.60,86.60,50];
for ii = 1:length(x0)
  hold on;
  plot([x0(ii),x1(ii)],[y0(ii),y1(ii)],'Color',[0.603922,0.803922,0.196078],...
    'LineWidth',2);
end
%% Draw Sonar default data
for ii = 1:180
  hold on;
  [x,y] = pol2cart(ii*0.0174532925,100);
  h(ii) = plot([0,x],[0,y],'g','LineWidth',1);
end
%% USE the following section for hardware implementation only
%{
  % define serial port
  s1 = serialport('COM13');   % change com port as per your configuration
  s1.BaudRate = 9600;         % select baud rate 9600
  fopen(s1);
  % draw sonar data
  while(1)
    data = fscanf(s1);
    [th,r] = strtok(data);
    th = real(str2double(th));
    r = str2double(r);
    set(h(th),'color','r');
    [x0,y0] = pol2cart(th*0.0174532925,100);
    [x,y] = pol2cart(th*0.0174532925,r);
    set(h(th),'XData',[x0,x]);
    set(h(th),'YData',[y0,y]);
    m = plot([0,x0],[0,y0],'r','LineWidth',3);
    drawnow;
    delete(m);
  end
%}