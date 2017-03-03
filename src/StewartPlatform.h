// 名前			：スチュワートプラットフォーム
#pragma once

#include "ParallelMechanism.h"

// プラットフォーム
class HexaPlatform {
private:
  double radius; // 半径
  double angle;  // 球面軸受同士の角度
  double angle2;

public:
  HexaPlatform(CDBL &r, CDBL &ang); // 変数初期化
  Vector vecE[6];  // 球面軸受の初期ベクトル	：ei(i = 0〜5)
  Vector vecEd[6]; // 球面軸受のベクトル		：e'i(i = 0〜5)
};

// ベース
class Base {
private:
  double radius; // 半径
  double angle;  // 球面軸受同士の角度
  double angle2;

public:
  Base(CDBL &r, CDBL &ang); // 変数初期化
  Vector vecS[6];           // 球面軸受のベクトル：Si(i = 0〜5)
};

// 可変長の脚
class ExpansibleLeg {
private:
  double length; // 長さ
  double maxLen; // 最大の長さ
  double minLen; // 最小の長さ

public:
  // 変数設定
  ExpansibleLeg(CDBL &len1, CDBL &len2) {
    if (len1 >= len2) {
      maxLen = len1;
      minLen = len2;
    } else {
      maxLen = len2;
      minLen = len1;
    }

    // 最大と最小の長さの中間
    length = (maxLen - minLen) / 2 + minLen;
  }

  Vector vecL; // 脚のベクトル：Li(i = 0〜5)

  // 脚長設定
  void setLen(CDBL &len) { length = len; };

  // 変数取得
  CDBL getLen() const { return length; }
  CDBL getMax() const { return maxLen; }
  CDBL getMin() const { return minLen; }
};

class StewartPlatform : public ParallelMechanism {
private:
  // 脚番号
  enum EN_LEG_NUM { LEG_1 = 0, LEG_2, LEG_3, LEG_4, LEG_5, LEG_6, LEG_NUM_MAX };

  // 部品
  HexaPlatform *plt;               // プラットフォーム
  Base *base;                      // ベース
  ExpansibleLeg *leg[LEG_NUM_MAX]; // 可変長の脚

public:
  StewartPlatform();
  ~StewartPlatform();

  void changePosition(CDBL &x, CDBL &y, CDBL &z, CDBL &phi, CDBL &theta,
                      CDBL &psi);
  void calculateLegVelocity(CDBL &x,     // Vx
                            CDBL &y,     // Vy
                            CDBL &z,     // Vz
                            CDBL &phi,   // Wφ
                            CDBL &theta, // Wθ
                            CDBL &psi);  // Wψ // 速度解析

protected:
  virtual void chkLmt(); // 可動制限判定

private:
  //------------------------------------------//
  // 座標算出 //
  //------------------------------------------//
  void invrsDis();   // 逆変位計算
  void calcJacobi(); // ヤコビ行列計算
};
