
#include "ParallelMechanism.h"

Leg::Leg() { setData(0, 0, 0, 0, 0, 0); }

void Leg::setData(CDBL &d1, CDBL &d2, CDBL &d3, CDBL &d4, CDBL &d5, CDBL &d6) {
  data1 = d1;
  data2 = d2;
  data3 = d3;
  data4 = d4;
  data5 = d5;
  data6 = d6;
}

// 領域内
void ParallelMechanism::inLmt() { enMechaState = MECHA_IN; }

// 領域外
void ParallelMechanism::outLmt() { enMechaState = MECHA_OUT; }

// 器用性を計算する
void ParallelMechanism::calculateDexterity() {
  // 行列式が存在しないとき
  if (detJ == 0) {
    return;
  }

  // ノルム計算
  double k =
      matJ.norm() * matJ.invrs(detJ).norm(); // ←行列のノルム計算ができてない！

  if (k == 0) {
    return;
  }

  // 器用性計算
  dexterity = 1 / k;
}
