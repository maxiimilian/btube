#include "dateneingabe.h"
#include <QApplication>
#include <string>
#include "cli.h"

/// Globaler String der den Ausführungspfad des Programms enthält
std::string run_path;

int main(int argc, char *argv[])
{
    // Ausführungspfad setzen (Erstes Argument)
    run_path = argv[0];

    // Prüfen, ob ein Argument in der Kommandozeile übergeben wurde
    if(argc == 2){
        std::string arg = argv[1];
        if(arg == "cli"){
            // siehe cli.cpp
            start_cli();
            return 0;
        }
        if(arg == "test"){
            run_tests();
            return 0;
        }
    }

    // GUI starten, wenn kein passendes Argument übergeben wurde
    QApplication app(argc, argv);

    DatenEingabe w;
    w.show();

    return app.exec();
}
