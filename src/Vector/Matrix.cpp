
#include "Matrix.h"
#include <string>

using namespace std;
Matrix::Matrix(UINT row, UINT col) : m_row(row), m_col(col) {
#ifdef _STD_VECTOR_
  // 行の要素数を設定する
  val.resize(m_row);

  for (UINT i = 0; i < m_row; i++) {
    // 列の要素数を設定する
    val[i].resize(m_col);
  }
#else
  // 行要素を生成する
  val = new double *[m_row];

  for (UINT i = 0; i < m_row; i++) {
    // 列要素を生成する
    val[i] = new double[m_col];
  }

  // 行列要素を初期化する
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] = 0;
    }
  }
#endif
}

Matrix::Matrix(const Matrix &mat) : m_row(mat.m_row), m_col(mat.m_col) {
#ifdef _STD_VECTOR_
  // 行の要素数を設定する
  val.resize(m_row);

  for (UINT i = 0; i < m_row; i++) {
    // 列の要素数を設定する
    val[i].resize(m_col);
  }
#else
  // 列成分生成
  val = new double *[m_row];

  for (UINT i = 0; i < m_row; i++) {
    // 行成分生成
    val[i] = new double[m_col];
  }

  // 値代入
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] = mat.val[i][j];
    }
  }
#endif
}

Matrix::~Matrix() {
#ifdef _STD_VECTOR_
#else
  // 行列要素破棄
  for (UINT i = 0; i < m_row; i++) {
    delete[] val[i];
  }

  delete[] val;
#endif
}

double &Matrix::operator()(UINT row, UINT col) { return val[row - 1][col - 1]; }

Matrix &Matrix::operator=(const Matrix &mat) {
  // 行列同士の行数と列数が等しくないとき
  if (m_row != mat.m_row || m_col != mat.m_col) {
    string err = "Matrix can't be substituted";
    throw err;
  }

#ifdef _STD_VECTOR_
  // 行の要素数を設定する
  val.resize(m_row);

  for (UINT i = 0; i < m_row; i++) {
    // 列の要素数を設定する
    val[i].resize(m_col);
  }
#endif

  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] = mat.val[i][j];
    }
  }

  return *this;
}

Matrix Matrix::operator+(const Matrix &mat) const {
  // 行列同士の行数と列数が等しくないとき
  if (m_row != mat.m_row || m_col != mat.m_col) {
    string err = "Matrix can't be added";
    throw err;
  }

  // 解となる行列
  Matrix matAns(m_row, m_col);

  // 受け取った2つの行列を加算する
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      matAns.val[i][j] = val[i][j] + mat.val[i][j];
    }
  }

  return matAns;
}

Matrix &Matrix::operator+=(const Matrix &mat) {
  // 行列同士の行数と列数が等しくないとき
  if (m_row != mat.m_row || m_col != mat.m_col) {
    string err = "Matrix can't be added";
    throw err;
  }

  // 受け取った2つの行列を加算する
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] += mat.val[i][j];
    }
  }

  return *this;
}

Matrix Matrix::operator-(const Matrix &mat) const {
  // 行列同士の行数と列数が等しくないとき
  if (m_row != mat.m_row || m_col != mat.m_col) {
    string err = "Matrix can't be subtracted";
    throw err;
  }

  // 解となる行列
  Matrix matAns(m_row, m_col);

  // 行列減算
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      matAns.val[i][j] = val[i][j] - mat.val[i][j];
    }
  }

  return matAns;
}

Matrix &Matrix::operator-=(const Matrix &mat) {
  // 行列同士の行数と列数が等しくないとき
  if (m_row != mat.m_row || m_col != mat.m_col) {
    string err = "Matrix can't be subtracted";
    throw err;
  }

  // 行列加算
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] -= mat.val[i][j];
    }
  }

  return *this;
}

Matrix Matrix::operator*(const Matrix &mat) const {
  // 被乗数の行列の列数＝乗数の行列の行数
  if (m_col != mat.m_row) {
    string err = "Matrix can't be producted";
    throw err;
  }

  // 解となる行列（被乗数の行列の列数、乗数の行列の行数）
  Matrix matAns(m_row, mat.m_col);

  // 行列の乗算
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < mat.m_col; j++) {
      for (UINT k = 0; k < m_row; k++) {
        matAns.val[i][j] += val[i][k] * mat.val[k][j];
      }
    }
  }

  return matAns;
}

Matrix Matrix::operator*(CDBL &in_val) const {
  // 解となる行列
  Matrix matAns(m_row, m_col);

  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      matAns.val[i][j] = val[i][j] * in_val;
    }
  }

  return matAns;
}

Matrix &Matrix::operator*=(CDBL &in_val) {
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] *= in_val;
    }
  }

  return *this;
}

Matrix Matrix::operator/(CDBL &in_val) const {
  // 解となる行列
  Matrix matAns(m_row, m_col);
  double ele[6][6];

  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      matAns.val[i][j] = val[i][j] / in_val;
      ele[i][j] = matAns.val[i][j];
    }
  }

  return matAns;
}

Matrix &Matrix::operator/=(CDBL &in_val) {
  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      val[i][j] /= in_val;
    }
  }

  return *this;
}

Matrix Matrix::transpose() const {
  // 解となる行列（行と列を反対に設定）
  Matrix matAns(m_col, m_row);

  for (UINT i = 0; i < m_row; i++) {
    for (UINT j = 0; j < m_col; j++) {
      matAns.val[i][j] = val[j][i];
    }
  }

  return matAns;
}
