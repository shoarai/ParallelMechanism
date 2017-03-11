// Copyright © 2017 shoarai

#include "../src/StewartPlatform.h"
#include <iostream>

using namespace std;

int main() {
  shared_ptr<ParallelMechanism> mechanism = make_shared<StewartPlatform>();

  for (size_t i = 0; i < 3; i++) {
    Position position(0 + i, 1 + i, 2 + i, 3 + i, 4 + i, 5 + i);
    mechanism->changePosition(position);
    mechanism->calculateActuatorVelocity(0 + i, 1 + i, 2 + i, 3 + i, 4 + i,
                                         5 + i);

    cout << "Leg position" << '\n';
    cout << "Leg1: \t" << mechanism->legPos.getData1() << "\n";
    cout << "Leg2: \t" << mechanism->legPos.getData2() << "\n";
    cout << "Leg3: \t" << mechanism->legPos.getData3() << "\n";
    cout << "Leg4: \t" << mechanism->legPos.getData4() << "\n";
    cout << "Leg5: \t" << mechanism->legPos.getData5() << "\n";
    cout << "Leg6: \t" << mechanism->legPos.getData6() << "\n";

    cout << "Leg velocity" << '\n';
    cout << "Leg1: \t" << mechanism->legVel.getData1() << "\n";
    cout << "Leg2: \t" << mechanism->legVel.getData2() << "\n";
    cout << "Leg3: \t" << mechanism->legVel.getData3() << "\n";
    cout << "Leg4: \t" << mechanism->legVel.getData4() << "\n";
    cout << "Leg5: \t" << mechanism->legVel.getData5() << "\n";
    cout << "Leg6: \t" << mechanism->legVel.getData6() << "\n";
    // Leg position
    // Leg1: 	0
    // Leg2: 	96.2039
    // Leg3: 	135.714
    // Leg4: 	235.736
    // Leg5: 	148.365
    // Leg6: 	230.398
    // Leg velocity
    // Leg1: 	194.936
    // Leg2: 	516.802
    // Leg3: 	-928.081
    // Leg4: 	-421.97
    // Leg5: 	89.1748
    // Leg6: 	21.185
  }
  return 0;
}
