#include <iostream>
#include "../lib/qpu.h"

using namespace std;

int main() {
    qpu Q(5);
    cout << Q.timestep() << endl;
    Q.H(0);
    cout << Q.timestep() << endl;
    Q.RZ(0, 0.1);
    cout << Q.timestep() << endl;
    Q.RY(1, 0.2);
    cout << Q.timestep() << endl;
    Q.RX(2, 0.3);
    cout << Q.timestep() << endl;
    Q.X(0);
    cout << Q.timestep() << endl;
    Q.Y(1);
    cout << Q.timestep() << endl;
    Q.Z(2);
    cout << Q.timestep() << endl;
    Q.CX(0, 3);
    cout << Q.timestep() << endl;
    Q.CCX(1, 2, 4);
    cout << Q.timestep() << endl;
    Q.S(3);
    cout << Q.timestep() << endl;
    Q.T(4);
    cout << Q.timestep() << endl;
    Q.dump(cout);
}
