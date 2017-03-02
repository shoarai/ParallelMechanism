// Copyright (c) 2017 shoarai

#include "../src/StewartPlatform.h"
#include "unistd.h"
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

  // pMecha->reset();

  for (int i = 0; i < 4; i++) {
    // Position position(0, 1, 2, 3, 4, 5);
    // プラットフォーム設定
    pMecha->setPlatformPosition(0, 1, 2, 3, 4, 5);
    // 座標算出
    pMecha->calculateCoordinate();

    // if (((CheckHitKey(KEY_INPUT_LSHIFT) == TRUE) ||
    //  CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)) {
    //        pMecha->calculateVelocity(); // 逆速度解析
    // }

    cout << "Leg1: \t" << pMecha->legPos.getData1() << "\n";
    cout << "Leg2: \t" << pMecha->legPos.getData2() << "\n";
    cout << "Leg3: \t" << pMecha->legPos.getData3() << "\n";
    cout << "Leg4: \t" << pMecha->legPos.getData4() << "\n";
    cout << "Leg5: \t" << pMecha->legPos.getData5() << "\n";
    cout << "Leg6: \t" << pMecha->legPos.getData6() << "\n";
    //   sleep(1);
  }
  //
  cout << "end" << '\n';
  return 0;
}
