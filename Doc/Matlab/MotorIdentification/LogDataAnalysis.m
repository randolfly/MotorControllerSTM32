%% load all data
clear;
load('../../Data/电机参数辨识/参数辨识设置_20240712084412.mat')
t = (1:length(encoder_vel))' * 0.001;
target_torque = double(target_torque);
encoder_vel = double(encoder_vel);

%% plot all data
% ap = APlot(2, 2);
% ap.ASubPlot([1 2]);
% plot(t, target_torque);
% xlabel("time(s)"); ylabel("target torque(1/1000)")
%
% ap.ASubPlot([3 4]);
% plot(t, encoder_vel);
% xlabel("time(s)"); ylabel("velocity(rad/s)")

%% extract all io pairs
excitation_io_pair_dict = containers.Map();
% find all +-200 points id

roi = find_roi(target_torque, 200, 1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '200-1');

roi = find_roi(target_torque, 200, 1.1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '200-1_1');

roi = find_roi(target_torque, 250, 1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '250-1');

roi = find_roi(target_torque, 250, 1.1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '250-1_1');

roi = find_roi(target_torque, 300, 1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '300-1');

roi = find_roi(target_torque, 300, 1.1);
excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, '300-1_1');

%% load signal to do calibration
io1 = excitation_io_pair_dict('250-1_1');
io2 = excitation_io_pair_dict('250-1');

io = io1 - io2;
% u = io(:, 1);
u = io2(:, 1) * 0.1;
v = io(:, 2);
