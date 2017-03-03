// Copyright (c) 2017 shoarai

#pragma once

#include "ParallelMechanism.h"
#include "SixDOF.h"
#include "StewartPlatformParts.h"

class StewartPlatform : public ParallelMechanism {
private:
  // 脚番号
  enum EN_LEG_NUM { LEG_1 = 0, LEG_2, LEG_3, LEG_4, LEG_5, LEG_6, LEG_NUM_MAX };

  // Vectors
  Vector vecP;    // 運動座標系原点の位置ベクトル
  Vector vecPdef; // 運動座標系原点の位置ベクトルの初期値

  // Parts
  HexaPlatform *platform;          // プラットフォーム
  BasePlate *basePlate;            // ベース
  ExpansibleLeg *leg[LEG_NUM_MAX]; // 可変長の脚

  SixDOF sixDof; // 6自由度姿勢
  SixDOF sixVel; // 6自由度速度
public:
  StewartPlatform();
  ~StewartPlatform();
  void changePosition(CDBL &x, CDBL &y, CDBL &z, CDBL &phi, CDBL &theta,
                      CDBL &psi);
  void calculateActuatorVelocity(CDBL &Vx, CDBL &Vy, CDBL &Vz, CDBL &Wphi,
                                 CDBL &Wtheta, CDBL &Wpsi);

private:
  void inverseDisplacement();     // 逆変位計算
  void calculateJacobianMatrix(); // ヤコビ行列計算
  void judgeMechanismState();
};
