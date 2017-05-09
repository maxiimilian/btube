#include <iostream>
#include "rohr.h"

using namespace std;

int main(){
    Rohr rohr(2.3, 5.5);

    cout << "Querschnitt ist: " << rohr.get_querschnitt(5) << endl;

    return 0;
}
