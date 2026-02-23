#include <iostream>
#include "Core.h"
#include "DSP.h"
#include "FFT.h"
#include "mainwindow.h"


using namespace std;

int main()
{
    MainWindow Generator;
    SignalBuffer Sig;

    Generator.Dots_array();

    for(int i = 0;i<1024;i++){
        Sig.addPoint(Generator.dots[i]);

    }
    Sig.GetPoints();

    Sig.isReady();
}
