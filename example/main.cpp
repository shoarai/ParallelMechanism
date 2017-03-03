// Copyright (c) 2017 shoarai

#include "../src/StewartPlatform.h"
#include <iostream>

using namespace std;

int main() {
  // Leg1: 	0
  // Leg2: 	96.2039
  // Leg3: 	135.714
  // Leg4: 	235.736
  // Leg5: 	148.365
  // Leg6: 	230.398

  shared_ptr<ParallelMechanism> pMecha = make_shared<StewartPlatform>();

  pMecha->changePosition(0, 1, 2, 3, 4, 5);

  pMecha->calculateActuatorVelocity(0, 1, 2, 3, 4, 5);

  cout << "Leg position" << '\n';
  cout << "Leg1: \t" << pMecha->legPos.getData1() << "\n";
  cout << "Leg2: \t" << pMecha->legPos.getData2() << "\n";
  cout << "Leg3: \t" << pMecha->legPos.getData3() << "\n";
  cout << "Leg4: \t" << pMecha->legPos.getData4() << "\n";
  cout << "Leg5: \t" << pMecha->legPos.getData5() << "\n";
  cout << "Leg6: \t" << pMecha->legPos.getData6() << "\n";

  cout << "Leg velocity" << '\n';
  cout << "Leg1: \t" << pMecha->legVel.getData1() << "\n";
  cout << "Leg2: \t" << pMecha->legVel.getData2() << "\n";
  cout << "Leg3: \t" << pMecha->legVel.getData3() << "\n";
  cout << "Leg4: \t" << pMecha->legVel.getData4() << "\n";
  cout << "Leg5: \t" << pMecha->legVel.getData5() << "\n";
  cout << "Leg6: \t" << pMecha->legVel.getData6() << "\n";

  cout << "end" << '\n';
  return 0;
}
