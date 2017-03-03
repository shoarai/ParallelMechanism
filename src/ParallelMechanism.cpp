// Copyright (c) 2017 shoarai

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

ParallelMechanism::ParallelMechanism()
    : enMechaState(MECHA_OUT), jacobianMatrix(6), jacobianDeterminant(0),
      dexterity(0){};

void ParallelMechanism::beWithinLimit() { enMechaState = MECHA_IN; }

void ParallelMechanism::beOutsideLimit() { enMechaState = MECHA_OUT; }

// 器用性を計算する
void ParallelMechanism::calculateDexterity() {
  // 行列式が存在しないとき
  if (jacobianDeterminant == 0) {
    return;
  }

  // ノルム計算
  double k =
      jacobianMatrix.norm() * jacobianMatrix.invrs(jacobianDeterminant)
                                  .norm(); // ←行列のノルム計算ができてない！

  if (k == 0) {
    return;
  }

  // 器用性計算
  dexterity = 1 / k;
}
