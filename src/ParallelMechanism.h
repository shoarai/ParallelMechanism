#include "SixDOF.h"
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
protected:
public:
  Vector vecP;    // 運動座標系原点の位置ベクトル
  Vector vecPdef; // 運動座標系原点の位置ベクトルの初期値
  Leg legPos;     // 脚の位置
  Leg legVel;     // 脚の速度

  ParallelMechanism()
      : enMechaState(MECHA_OUT), matJ(6), detJ(0), dexterity(0){};

  virtual ~ParallelMechanism(){};
  void setPlatformPosition( // プラットフォームの姿勢設定
      CDBL &x,              // x
      CDBL &y,              // y
      CDBL &z,              // z
      CDBL &phi,            // φ
      CDBL &theta,          // θ
      CDBL &psi);           // ψ
  void setPlatformVelocity( // プラットフォームの速度設定
      CDBL &x,              // Vx
      CDBL &y,              // Vy
      CDBL &z,              // Vz
      CDBL &phi,            // Wφ
      CDBL &theta,          // Wθ
      CDBL &psi);           // Wψ

  virtual void calculateCoordinate() = 0; // 座標算出
  virtual void calculateVelocity() = 0;   // 速度計算

protected:
  SixDOF sixDof;             // 6自由度姿勢
  SixDOF sixVel;             // 6自由度速度
  SquareMat matJ;            // ヤコビ行列
  double detJ;               // ヤコビ行列式
  double dexterity;          // 器用性
  void calculateDexterity(); // 器用性計算（未実装）
  void inLmt();              // 動作領域内
  void outLmt();             // 動作領域外

  virtual void invrsDis() = 0;   // 逆変位計算
  virtual void calcJacobi() = 0; // ヤコビ行列計算
  virtual void chkLmt() = 0;     // 可動制限判定

private:
  // メカニズムの状態
  enum EN_MECHA_STATE {
    MECHA_IN = 0, // 動作領域内
    MECHA_OUT,    // 動作領域外
    MECHA_STATE_MAX
  };

  EN_MECHA_STATE enMechaState; // メカニズムの状態
};
