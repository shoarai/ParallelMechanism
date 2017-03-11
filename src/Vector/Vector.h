
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "typedef.h"

class Vector {
private:
  double m_x; // x成分
  double m_y; // y成分
  double m_z; // z成分

public:
  // コンストラクタ
  Vector();
  Vector(CDBL &, CDBL &, CDBL &);

  // ベクトル成分を取り出す
  CDBL getx() const;
  CDBL gety() const;
  CDBL getz() const;

  // ベクトル成分を設定する
  void set(CDBL &, CDBL &, CDBL &);
  void setx(CDBL &);
  void sety(CDBL &);
  void setz(CDBL &);

  // ベクトルとの加減算
  Vector operator+(const Vector &) const;
  Vector &operator+=(const Vector &);
  Vector operator-(const Vector &) const;
  Vector &operator-=(const Vector &);

  // 数値との乗除算
  Vector operator*(CDBL &)const;
  Vector &operator*=(CDBL &);
  Vector operator/(CDBL &) const;
  Vector &operator/=(CDBL &);

  Vector operator*(const Vector &)const;  //  ベクトルの外積
  double operator%(const Vector &) const; //  ベクトルの内積

  double norm() const;      // ノルムを求める
  Vector normalize() const; // ベクトルを正規化をする

  // 座標変換
  Vector rct2plr() const; // 直交座標系→極座標系
  Vector plr2rct() const; // 極座標系→直交座標系

  // 極座標系→直交座標系（2次元対応）
  void setPolar2cart(CDBL &rad, CDBL &angleXY, CDBL &angleToZ = deg2rad(90));
};

#endif // _VECTOR_H_
