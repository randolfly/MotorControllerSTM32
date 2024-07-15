% 定义参数
N = 4096; % 信号长度
fs = 1000; % 采样频率
frequencies = primes(31) * fs / N; % 期望频率
frequencies = frequencies(2:end);

% 初始化频谱
spectrum = zeros(1, N);

% 设置期望频率的幅度并应用汉宁窗
amplitude = 1; % 设定相同的幅度
window_length = 3; % 汉宁窗长度
half_window = (window_length - 1) / 2;

for f = frequencies
    index = round(f / fs * N) + 1;
    window = hann(window_length)'; % 汉宁窗
    spectrum(index - half_window:index + half_window) = amplitude * window;
end

% 确保频谱的对称性
spectrum(N / 2 + 2:end) = fliplr(spectrum(2:N / 2));

% 生成复数频谱
spectrum_complex = spectrum .* exp(1i * 2 * pi * rand(1, N));

% 生成时域信号
signal = ifft(spectrum_complex, 'symmetric');

% 对信号进行归一化处理
signal = signal / max(abs(signal));

% 将信号二值化
binary_signal = signal > 0;
binary_signal = 2 * binary_signal - 1; % 将二进制信号转换为+1和-1

% 绘制信号
figure;
subplot(2, 1, 1);
plot(binary_signal);
title('二进制信号');
xlabel('样本');
ylabel('幅度');

% 绘制频谱
subplot(2, 1, 2);
frequencies_axis = (0:N - 1) * (fs / N);
plot(frequencies_axis, abs(fft(binary_signal)));
title('信号频谱');
xlabel('频率 (Hz)');
ylabel('幅度');
xlim([0 fs / 2]);
