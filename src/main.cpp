#include "dateneingabe.h"
#include <QApplication>
#include <string>
#include "cli.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
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
    // cout<<"argc: "<<argc<<endl;
    // cout<<"argv: "<<argv<<endl;

    // GUI starten, wenn kein passendes Argument übergeben wurde
    QApplication app(argc, argv);

    DatenEingabe w;
    w.show();
    // w.set_argv(argv);

    return app.exec();
}
