function excitation_io_pair_dict = add_dict(roi, target_torque, encoder_vel, excitation_io_pair_dict, dict_key)
    input = target_torque(roi);
    output = encoder_vel(roi);
    io_pair = [input output];
    excitation_io_pair_dict(dict_key) = io_pair;
end
