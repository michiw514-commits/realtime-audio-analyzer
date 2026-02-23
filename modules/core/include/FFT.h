#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>
#include <cmath>

class FFT {
public:
    // Конструктор с размером преобразования (должен быть степенью 2)
    explicit FFT(size_t size);

    // Запрещаем копирование
    FFT(const FFT&) = delete;
    FFT& operator=(const FFT&) = delete;

    // Прямое преобразование (принимает действительный сигнал, возвращает комплексный спектр)
    std::vector<std::complex<double>> forward(const std::vector<double>& signal) const;

    // Прямое преобразование (принимает комплексный сигнал)
    std::vector<std::complex<double>> forward(const std::vector<std::complex<double>>& signal) const;

    // Обратное преобразование
    std::vector<std::complex<double>> inverse(const std::vector<std::complex<double>>& spectrum) const;

    // Получить амплитудный спектр (удобно для визуализации)
    std::vector<double> magnitude(const std::vector<std::complex<double>>& spectrum) const;

    // Получить фазовый спектр
    std::vector<double> phase(const std::vector<std::complex<double>>& spectrum) const;

    // Проверка, является ли размер степенью двойки
    static bool isPowerOfTwo(size_t n);

    // Получить размер FFT
    size_t size() const { return size_; }

private:
    // Внутренняя реализация (рекурсивный или итеративный FFT)
    void fft(std::vector<std::complex<double>>& data, bool invert) const;

    size_t size_;                                    // Размер FFT
    mutable std::vector<std::complex<double>> twiddle_;  // Поворотные коэффициенты (кэш)
};

#endif // FFT_H
