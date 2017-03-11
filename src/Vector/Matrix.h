// Copyright © 2017 shoarai

#ifndef _MATRIX_H_
#define _MATRIX_H_

//#define _STD_VECTOR_		// std::vectorを使う
#ifdef _STD_VECTOR_
#include <vector>
#endif
#include "typedef.h"

class Matrix {
public:
  CUINT m_row; // 行
  CUINT m_col; // 列

#ifdef _STD_VECTOR_
  std::vector<std::vector<double>> val;
#else
  double **val; // 行列要素用ポインタ
#endif

public:
  explicit Matrix(UINT, UINT); // コンストラクタ
  Matrix(const Matrix &);      // コピーコンストラクタ
  virtual ~Matrix();           // デストラクタ

  // 行列要素を取り出す
  double &operator()(UINT row, UINT colN);

  // 行列の代入
  Matrix &operator=(const Matrix &);

  // 行列との加減算
  Matrix operator+(const Matrix &) const;
  Matrix &operator+=(const Matrix &);
  Matrix operator-(const Matrix &) const;
  Matrix &operator-=(const Matrix &);

  // 行列との積
  Matrix operator*(const Matrix &)const;

  // 数値との乗除算
  Matrix operator*(CDBL &)const;
  Matrix &operator*=(CDBL &);
  Matrix operator/(CDBL &) const;
  Matrix &operator/=(CDBL &);

  // 転置行列
  Matrix transpose() const;
};

#endif
