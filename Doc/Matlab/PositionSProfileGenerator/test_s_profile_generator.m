clear SProfilePlanner;
% 边界条件
q0 = 0; q1 = 0.1;
v0 = 0; v1 = 0;
vmax = 2; amax = 1; jmax = 1;

pos_list = [];

time = 0:0.001:50;
pos = SProfilePlanner(1, 0, q0, q1, v0, v1, vmax, amax, jmax);

for t = time
    pos = SProfilePlanner(0, t, q0, q1, v0, v1, vmax, amax, jmax);
    pos_list = [pos_list; pos];
end

figure(1)
plot(time, pos_list, 'r', 'LineWidth', 1.5)
