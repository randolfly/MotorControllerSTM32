%% load step signal
clear;
load("../../Data/电机参数辨识/阶跃扭矩信号_20240712102344.mat")
t = (1:length(encoder_vel))' * 0.001;
target_torque = double(target_torque);
encoder_vel = double(encoder_vel);

%% step signal analysis

roi = 50077:66068;
figure;
plot(t(roi), target_torque(roi));
figure;
plot(t(roi), encoder_vel(roi));
