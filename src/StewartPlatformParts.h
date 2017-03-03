// Copyright (c) 2017 shoarai

#include "Vector/Vector.h"

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

class BasePlate {
private:
  double radius; // 半径
  double angle;  // 球面軸受同士の角度
  double angle2;

public:
  BasePlate(CDBL &r, CDBL &ang); // 変数初期化
  Vector vecS[6];                // 球面軸受のベクトル：Si(i = 0〜5)
};

// 可変長の脚
class ExpansibleLeg {
private:
  double length; // 長さ
  double maxLen; // 最大の長さ
  double minLen; // 最小の長さ

public:
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
  void setLength(CDBL &len) { length = len; };
  CDBL getLength() const { return length; }
  CDBL getMax() const { return maxLen; }
  CDBL getMin() const { return minLen; }
};
