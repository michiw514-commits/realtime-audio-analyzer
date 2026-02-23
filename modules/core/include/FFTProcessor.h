#ifndef DSP_H
#define DSP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <bitset>


using namespace std;

struct SignalParameters
{

    double frequency = 0.0;
    double amplitude = 0.0;
    double phase = 0.0;

};

struct Spectrum
{
    vector<SignalParameters> Spect;
    double sampleRate = 1000;//Поумолчанию

    int SIZE() const
    {
        return this->Spect.size();
    }

    double MaxFrequency()
    {
        if(this->Spect.empty())
            return 0.0;

        SignalParameters a = Spect[0];
        for (int i = 0;i < this->Spect.size(); i++)
            a.frequency = max(a.frequency,Spect[i+1].frequency);
        return a.frequency;
    }
};

class FFTProcessor
{
public:



    bool DataVerification(vector<double> V)//Проверка сигнала для дальнейшего преобразования
    {
        if((V.size() & (V.size()-1)) == 0)
            return true;
        else {
            return false;
        }
    }

    vector<double> WindowFunction(vector<double> V)
    {
        int W[1024];
        for(int i = 0;V.size() <= 1024;i++)
            W[i] = 1;
        for(int i = 0;V.size() <= 1024;i++)
        {
            V[i] *= W[i];
        }
        return V;
    }

    Spectrum forming(vector<complex<double>> V, SignalParameters SigP, Spectrum Spect1)
    {
        for(int i = 0; i < V.size();i++)
        {
            SigP.amplitude = sqrt(V[i].real()*V[i].real() + V[i].imag()*V[i].imag());
            SigP.frequency = (Spect1.sampleRate * i)/1024;
            SigP.phase = atan2(V[i].imag(),V[i].real());
            Spect1.Spect.push_back(SigP);
        }
        return Spect1;
    }

    SignalParameters SigP;
    Spectrum Spect1;

private:
    const double sampleRate;
    const double TwoPi = 6.283185307179586;
};

#endif // DSP_H
