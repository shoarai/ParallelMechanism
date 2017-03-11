#ifndef _ROTATION_MATRIX_H_
#define _ROTATION_MATRIX_H_

#include "Vector.h"

class RotationMatrix {
public:
  RotationMatrix();                          // コンストラクタ
  RotationMatrix(                            // コンストラクタ
      const double &phi,                     // x軸周りの角度
      const double &sit,                     // y軸周りの角度
      const double &psi);                    // z軸周りの角度
  void calcRotateMat(                        // 回転行列計算
      const double &phi,                     // x軸周りの角度
      const double &sit,                     // y軸周りの角度
      const double &psi);                    // z軸周りの角度
  Vector rotateVec(const Vector &) const;    // ベクトル回転
  Vector rotateInvVec(const Vector &) const; // ベクトル逆回転
  RotationMatrix operator*(const RotationMatrix &)const; // 回転行列の積

private:
  enum { NUM = 3 };         // 行列の行数（＝列数）
  double element[NUM][NUM]; // 行列成分
};

#endif // _ROTATION_MATRIX_H_
