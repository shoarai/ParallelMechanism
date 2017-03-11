
#include "SquareMatrix.h"
#include <string>

using namespace std;

SquareMat::SquareMat(UINT n) : num(n), Matrix(n, n) {}

SquareMat::SquareMat(const Matrix &mat)
    : num(mat.m_row), Matrix(mat.m_row, mat.m_row) {
  // 行と列の要素数が等しいか
  if (mat.m_row != mat.m_col) {
    string err = "Matrix isn't square matrix";
    throw err;
  }

  // 値代入
  for (UINT i = 0; i < num; i++) {
    for (UINT j = 0; j < num; j++) {
      val[i][j] = mat.val[i][j];
    }
  }
}

SquareMat &SquareMat::operator=(const Matrix &mat) {
  // 行と列の要素数が等しいか
  if (mat.m_row != mat.m_col) {
    string err = "Matrix isn't square matrix";
    throw err;
  }

#ifdef VECTOR
  // 行の要素数を設定する
  val.resize(m_row);

  for (UINT i = 0; i < m_row; i++) {
    // 列の要素数を設定する
    val[i].resize(m_col);
  }
#endif

  // 値代入
  for (UINT i = 0; i < num; i++) {
    for (UINT j = 0; j < num; j++) {
      val[i][j] = mat.val[i][j];
    }
  }

  return *this;
}

// SquareMat::operator Matrix() {
//   Matrix matAns(num, num);
//
// #ifdef VECTOR
//   // 行の要素数を設定する
//   val.resize(m_row);
//
//   for (UINT i = 0; i < m_row; i++) {
//     // 列の要素数を設定する
//     val[i].resize(m_col);
//   }
// #endif
//
//   // 値代入
//   for (UINT i = 0; i < num; i++) {
//     for (UINT j = 0; j < num; j++) {
//       matAns.val[i][j] = val[i][j];
//     }
//   }
//
//   return matAns;
// }

double SquareMat::cofactor(UINT row, UINT col) const {
  // 次数が１少ない行列を作る
  SquareMat tmp(num - 1);

  // 代入先の行番号
  UINT i2 = 0;

  // 代入元の行番号
  for (UINT i = 0; i < num; i++) {
    // 余因子展開の対象の行をとばす
    if (i == row) {
      continue;
    }

    // 代入先の列番号
    UINT j2 = 0;

    // 代入元の列番号
    for (UINT j = 0; j < num; j++) {
      // 余因子展開の対象の列をとばす
      if (j == col) {
        continue;
      }

      // 次数が１小さい行列を作る
      tmp.val[i2][j2] = val[i][j];

      j2++;
    }

    i2++;
  }

  // 解となる余因子
  double ans = tmp.det();

  // 行番号＋列番号が奇数の時は、マイナスをかける
  if ((row + col) % 2 != 0) {
    ans *= -1;
  }

  return ans;
}

SquareMat SquareMat::adjMat() const {
  // 解となる行列
  static SquareMat smatAns(num);
  double ele[6][6];

  for (UINT i = 0; i < num; i++) {
    for (UINT j = 0; j < num; j++) {
      // 余因子を転置して代入する
      smatAns.val[i][j] = cofactor(j, i);

      ele[i][j] = smatAns.val[i][j];
    }
  }
  volatile double ele2 = 0;
  ele2++;

  return smatAns;
}

double SquareMat::det() const {
  // 行列式
  double ans = 0;

  //------------------------------------------//
  // 次数が２のとき、たすきがけで解く			//
  //------------------------------------------//
  if (num == 2) {
    ans = val[0][0] * val[1][1] - val[0][1] * val[1][0];
  }
  //------------------------------------------//
  // 次数が３のとき、サラスの方法で解く		//
  //------------------------------------------//
  else if (num == 3) {
    ans = val[0][0] * val[1][1] * val[2][2];
    ans += val[0][1] * val[1][2] * val[2][0];
    ans += val[0][2] * val[1][0] * val[2][1];
    ans -= val[0][2] * val[1][1] * val[2][0];
    ans -= val[0][0] * val[1][2] * val[2][1];
    ans -= val[0][1] * val[1][0] * val[2][2];
  }
  //------------------------------------------//
  // 次数が４以上のとき						//
  //------------------------------------------//
  else {
    // 行列の対角要素に０があるか判定
    bool dia0 = true;
    //		bool dia0 = false;

    for (UINT i = 0; i < num; i++) {
      if (val[i][i] == 0) {
        dia0 = true;
      }
    }

    //------------------------------------------//
    // 行列の対角要素に０があるとき、余因子展開で解く
    //------------------------------------------//
    if (dia0 == true) {
      // 余因子の対象位置をずらす
      for (UINT i = 0; i < num; i++) {
        // 余因子展開の対象にする値が０なら
        if (val[i][0] == 0) {
          continue;
        }

        // 余因子展開の対象にする値 × 余因子
        ans += val[i][0] * this->cofactor(i, 0);
      }
    }
    //------------------------------------------//
    // 行列の対角要素に０がないとき、三角行列で解く
    //------------------------------------------//
    else {
      ans = 1;        // 行列式
      double buf = 0; // 一次保存

      // 上三角行列
      SquareMat triMat = *this;

      // 上三角行列を作成
      // http://thira.plavox.info/blog/2008/06/_c.html
      for (UINT i = 0; i < num; i++) {
        for (UINT j = 0; j < num; j++) {
          if (i < j) {
            if (triMat.val[i][i] == 0) {
              return 0;
            };

            buf = triMat.val[j][i] / triMat.val[i][i]; // 対角成分に0がないとき

            for (UINT k = 0; k < num; k++) {
              triMat.val[j][k] -= triMat.val[i][k] * buf;
            }
          }
        }
      }

      // 対角部分の積
      for (UINT i = 0; i < num; i++) {
        ans *= triMat.val[i][i];
      }
    }
  }

  return ans;
}

SquareMat SquareMat::invrs(CDBL &deter) const {
  // 行列式を求める
  //	double det = this->det();

  if (deter == 0) {
    string err = "Determinant is zero, so inverse matrix don't exist";
    throw err;
    //		throw std::overflow_error("invrs():InverseMatrix don't exist");
    ////error処理
  }

  // 解となる行列
  SquareMat smatAns(num);

  bool dia0 = true;
  //	bool dia0 = false;

  // 行列の対角要素に０があるか判定
  for (UINT i = 0; i < num; i++) {
    if (val[i][i] == 0) {
      dia0 = true;
    }
  }

  if (dia0 == true) {
    //		smatAns = this->adjMat() / deter;
    smatAns = this->adjMat();
    //		Matrix smatAns2(adjMat());

    double ele[6][6];
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        ele[i][j] = smatAns.val[i][j];
      }
    }

    //		smatAns = this->adjMat();
    smatAns = smatAns / deter;
  }
  //------------------------------------------//
  // 行列の対角要素に０がないとき、三角行列を使って解く
  //------------------------------------------//
  else {
    double matBuf[6][6]; // 一時的な行列
    double buf = 0;      // 一時的なデータを蓄える
    int n = 6;           // 配列の次数

    // 行列を一時保存
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        matBuf[i][j] = val[i][j];
      }
    }

    // 単位行列を作る
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) {
          smatAns.val[i][j] = 1;
        } else {
          smatAns.val[i][j] = 0;
        }
      }
    }

    // 掃き出し法
    for (int i = 0; i < n; i++) {
      buf = 1 / matBuf[i][i];

      for (int j = 0; j < n; j++) {
        matBuf[i][j] *= buf;
        smatAns / val[i][j] *= buf;
      }

      for (int j = 0; j < n; j++) {
        if (i != j) {
          buf = matBuf[j][i]; // ０の可能性あり（エラー）

          for (int k = 0; k < n; k++) {
            matBuf[j][k] -= matBuf[i][k] * buf;
            smatAns.val[j][k] -= smatAns.val[i][k] * buf;
          }
        }
      }
    }
  }

  return smatAns;
}

double SquareMat::norm() const {
  double ans = 0;

  //------------------------------------------//
  // 未実装 //
  //------------------------------------------//

  return ans;
}

double SquareMat::trace() const {
  double ans = 0;

  for (UINT i = 0; i < num; i++) {
    ans += val[i][i];
  }

  return ans;
}

SquareMat::SquareMat(CDBL &r0c0, CDBL &r0c1, CDBL &r0c2, CDBL &r0c3, CDBL &r0c4,
                     CDBL &r0c5, CDBL &r1c0, CDBL &r1c1, CDBL &r1c2, CDBL &r1c3,
                     CDBL &r1c4, CDBL &r1c5, CDBL &r2c0, CDBL &r2c1, CDBL &r2c2,
                     CDBL &r2c3, CDBL &r2c4, CDBL &r2c5, CDBL &r3c0, CDBL &r3c1,
                     CDBL &r3c2, CDBL &r3c3, CDBL &r3c4, CDBL &r3c5, CDBL &r4c0,
                     CDBL &r4c1, CDBL &r4c2, CDBL &r4c3, CDBL &r4c4, CDBL &r4c5,
                     CDBL &r5c0, CDBL &r5c1, CDBL &r5c2, CDBL &r5c3, CDBL &r5c4,
                     CDBL &r5c5)
    : num(6), Matrix(6, 6) {
  val[0][0] = r0c0;
  val[0][1] = r0c1;
  val[0][2] = r0c2;
  val[0][3] = r0c3;
  val[0][4] = r0c4;
  val[0][5] = r0c5;
  val[1][0] = r1c0;
  val[1][1] = r1c1;
  val[1][2] = r1c2;
  val[1][3] = r1c3;
  val[1][4] = r1c4;
  val[1][5] = r1c5;
  val[2][0] = r2c0;
  val[2][1] = r2c1;
  val[2][2] = r2c2;
  val[2][3] = r2c3;
  val[2][4] = r2c4;
  val[2][5] = r2c5;
  val[3][0] = r3c0;
  val[3][1] = r3c1;
  val[3][2] = r3c2;
  val[3][3] = r3c3;
  val[3][4] = r3c4;
  val[3][5] = r3c5;
  val[4][0] = r4c0;
  val[4][1] = r4c1;
  val[4][2] = r4c2;
  val[4][3] = r4c3;
  val[4][4] = r4c4;
  val[4][5] = r4c5;
  val[5][0] = r5c0;
  val[5][1] = r5c1;
  val[5][2] = r5c2;
  val[5][3] = r5c3;
  val[5][4] = r5c4;
  val[5][5] = r5c5;
}
