#include "FFT.h"
#include <stdexcept>
#include <algorithm>

FFT::FFT(size_t size) : size_(size) {
    // Проверяем, что размер - степень двойки
    if (!isPowerOfTwo(size_)) {
        throw std::invalid_argument("FFT size must be a power of two");
    }

    // Предвычисляем поворотные коэффициенты (для ускорения)
    twiddle_.resize(size_ / 2);
    for (size_t i = 0; i < size_ / 2; ++i) {
        double angle = -2.0 * M_PI * i / size_;
        twiddle_[i] = std::complex<double>(std::cos(angle), std::sin(angle));
    }
}

bool FFT::isPowerOfTwo(size_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}

std::vector<std::complex<double>> FFT::forward(const std::vector<double>& signal) const {
    if (signal.size() != size_) {
        throw std::invalid_argument("Signal size must match FFT size");
    }

    // Конвертируем double в complex<double>
    std::vector<std::complex<double>> data(size_);
    for (size_t i = 0; i < size_; ++i) {
        data[i] = std::complex<double>(signal[i], 0.0);
    }

    fft(data, false);
    return data;
}

std::vector<std::complex<double>> FFT::forward(const std::vector<std::complex<double>>& signal) const {
    if (signal.size() != size_) {
        throw std::invalid_argument("Signal size must match FFT size");
    }

    auto data = signal;
    fft(data, false);
    return data;
}

std::vector<std::complex<double>> FFT::inverse(const std::vector<std::complex<double>>& spectrum) const {
    if (spectrum.size() != size_) {
        throw std::invalid_argument("Spectrum size must match FFT size");
    }

    auto data = spectrum;
    fft(data, true);

    // Нормировка (делим на размер)
    for (auto& val : data) {
        val /= static_cast<double>(size_);
    }

    return data;
}

void FFT::fft(std::vector<std::complex<double>>& data, bool invert) const {
    size_t n = data.size();

    if (n == 1) return;

    // Разделяем на четные и нечетные индексы
    std::vector<std::complex<double>> even(n / 2);
    std::vector<std::complex<double>> odd(n / 2);

    for (size_t i = 0; i < n / 2; ++i) {
        even[i] = data[i * 2];
        odd[i] = data[i * 2 + 1];
    }

    // Рекурсивно вычисляем FFT для половин
    fft(even, invert);
    fft(odd, invert);

    // Комбинируем результаты
    for (size_t i = 0; i < n / 2; ++i) {
        // Поворотный коэффициент
        double angle = 2.0 * M_PI * i / n;
        if (invert) angle = -angle;

        std::complex<double> w(std::cos(angle), std::sin(angle));

        data[i] = even[i] + w * odd[i];
        data[i + n / 2] = even[i] - w * odd[i];
    }
}

std::vector<double> FFT::magnitude(const std::vector<std::complex<double>>& spectrum) const {
    std::vector<double> mag(spectrum.size());
    for (size_t i = 0; i < spectrum.size(); ++i) {
        mag[i] = std::abs(spectrum[i]);
    }
    return mag;
}

std::vector<double> FFT::phase(const std::vector<std::complex<double>>& spectrum) const {
    std::vector<double> ph(spectrum.size());
    for (size_t i = 0; i < spectrum.size(); ++i) {
        ph[i] = std::arg(spectrum[i]);
    }
    return ph;
}
