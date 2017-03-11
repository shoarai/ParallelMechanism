// Copyright (c) 2017 shoarai

#include "Position.h"
#include "Vector/SquareMatrix.h"
#include "Vector/Vector.h"

class Leg {
public:
  Leg();
  void setData(CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &);
  CDBL getData1() const { return data1; };
  CDBL getData2() const { return data2; };
  CDBL getData3() const { return data3; };
  CDBL getData4() const { return data4; };
  CDBL getData5() const { return data5; };
  CDBL getData6() const { return data6; };

private:
  double data1, data2, data3, data4, data5, data6;
};

class ParallelMechanism {
public:
  Leg legPos; // 脚の位置
  Leg legVel; // 脚の速度

  ParallelMechanism();
  virtual ~ParallelMechanism(){};

  virtual void changePosition(Position &platformPosition) = 0;
  virtual void calculateActuatorVelocity(CDBL &Vx, CDBL &Vy, CDBL &Vz,
                                         CDBL &Wphi, CDBL &Wtheta,
                                         CDBL &Wpsi) = 0;

protected:
  SquareMat jacobianMatrix;   // ヤコビ行列
  double jacobianDeterminant; // ヤコビ行列式
  double dexterity;           // 器用性
  void calculateDexterity();  // 器用性計算（未実装）
  void beWithinLimit();       // 動作領域内
  void beOutsideLimit();      // 動作領域外

  virtual void inverseDisplacement() = 0;     // 逆変位計算
  virtual void calculateJacobianMatrix() = 0; // ヤコビ行列計算
  virtual void judgeMechanismState() = 0;     // 可動制限判定

private:
  enum EN_MECHA_STATE {
    MECHA_IN = 0, // 動作領域内
    MECHA_OUT,    // 動作領域外
    MECHA_STATE_MAX
  } enMechaState;
};
