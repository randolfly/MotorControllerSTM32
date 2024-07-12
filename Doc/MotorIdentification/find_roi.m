function roi = find_roi(target_torque, magnitude, gain)

    arguments
        target_torque (1, :) double
        magnitude = 200
        gain = 1
    end

    tol = 5;
    N = 4096;

    indices = find(abs(target_torque - abs(magnitude * gain)) < tol | abs(target_torque + abs(magnitude * gain)) < tol);
    roi = sort(indices);

    if length(roi) >= N
        roi = roi(1:N);
    else
        complement_list = 1:(N - length(roi));
        roi = [roi roi(end) + complement_list];
    end

end
