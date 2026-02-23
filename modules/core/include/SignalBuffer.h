#include <iostream>
#include <deque>
#include <vector>

using namespace std;

class SignalBuffer
{
public:

    void addPoint(double x) //Добавляем точки в конец очереди, если она переполнена, то удаляем 1й элемент и добавляем последний
    {
        if(buffer.size() < N)
            buffer.push_back(x);
        else
        {
            buffer.pop_front();
            buffer.push_back(x);
        }

    }

    void GetPoints() //Просматриваем все точки в очереди (Хранилище)
    {
        for(int i = 0;i < buffer.size();i++)
            cout << buffer[i] << endl;
    }

    bool isReady() const //Проверяем готовность (смотрим пока буффер полностью не заполнится)
    {
        if(buffer.size() == N)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    vector<double> GetWindow() const //Готовим вектор Сигнала для передачи в FFT модуль
    {
        vector<double> Signal;
        for(int i = 0;i < buffer.size();i++)
            Signal.push_back(buffer[i]);
        return Signal;
    }

private:
    deque<double> buffer;//очередь из даблов
    static const int N = 1024;//Максимальный размер очереди
};

