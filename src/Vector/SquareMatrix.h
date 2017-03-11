#ifndef _SQUARE_MATRIX_H_
#define _SQUARE_MATRIX_H_

#include "Matrix.h"

class SquareMat : public Matrix {
public:
  UINT num; // 行列の行数（＝列数）

public:
  // コンストラクタ
  explicit SquareMat(UINT);

  SquareMat(CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &);

  SquareMat(const Matrix &); // コピーコンストラクタ
  virtual ~SquareMat(){};    // デストラクタ

  // 正方行列の代入
  SquareMat &operator=(const Matrix &);

  // 行列クラスへのキャスト
  // operator Matrix();

  double norm() const;              // ノルム
  double det() const;               // 行列式
  SquareMat invrs(CDBL &det) const; // 逆行列

private:
  double cofactor(UINT, UINT) const; // 余因子
  double trace() const;              // 対角和
  SquareMat adjMat() const;          // 余因子行列
};

#endif
