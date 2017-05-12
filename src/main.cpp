// Erstmal keine GUI in main.cpp
#include <iostream>
#include "rohr.h"
#include "fluid.h"

using namespace std;

int main(){
    Rohr rohr(1,5);
    cout << "Rohrquerschnitt: " << rohr.get_querschnitt(2) << endl;
    return 0;
}
