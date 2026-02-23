#include "mainwindow.h"
#include <iostream>
#include "Core.h"
#include "DSP.h"
#include "FFT.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SignalHandling_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    MainWindow Generator;
    SignalBuffer Sig;

    Generator.Dots_array();

    for(int i = 0;i<1024;i++){
        Sig.addPoint(Generator.dots[i]);

    }
    Sig.GetPoints();

    Sig.isReady();
    return a.exec();
}
