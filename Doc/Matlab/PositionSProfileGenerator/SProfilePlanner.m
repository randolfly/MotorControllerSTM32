function pos = SProfilePlanner(execute, t, q0, q1, v0, v1, vmax, amax, jmax)
    persistent param init_profile stop_profile sigma T;
    
    if isempty(param)
        param = zeros(1,16);
        init_profile = false;
        stop_profile = false;
        sigma = 1;
        T = 0;
    end
    
    pos = q1;

    if abs(q0-q1)<5e-7 
        return;
    end
    
    if execute
        stop_profile = false;
    end

    if stop_profile == false

        if init_profile == false
            sigma = sign(q1 - q0);
            param = STrajectoryPara(q0, q1, v0, v1, vmax, amax, jmax);
            T = param(1) + param(2) + param(3);
            init_profile = true;
        else
            if t <= T
                pos = sigma * S_position(t, param(1), param(2), param(3), param(4), param(5), param(6), param(7), param(8), param(9), param(10), param(11), param(12), param(13), param(14), param(15), param(16));
            else
                pos = q1;
                stop_profile = true;
            end
        end
    else
        init_profile = false;
    end

end
