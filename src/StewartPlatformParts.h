// Copyright © 2017 shoarai

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

class ExpansibleLeg {
private:
  double length;
  double maxLen;
  double minLen;

public:
  ExpansibleLeg(CDBL &maxLength, CDBL &minLength);
  Vector vecL; // 脚のベクトル：Li(i = 0〜5)

  // 脚長設定
  void setLength(CDBL &len) { length = len; };
  CDBL getLength() const { return length; }
  CDBL getMax() const { return maxLen; }
  CDBL getMin() const { return minLen; }
};
