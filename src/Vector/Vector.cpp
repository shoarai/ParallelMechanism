
#include "Vector.h"

// コンストラクタ
Vector::Vector() : m_x(), m_y(), m_z() {}

Vector::Vector(CDBL &x, CDBL &y, CDBL &z) : m_x(x), m_y(y), m_z(z) {}

// ベクトル成分を取り出す
CDBL Vector::getx() const { return m_x; }
CDBL Vector::gety() const { return m_y; }
CDBL Vector::getz() const { return m_z; }

// ベクトル成分を設定する
void Vector::set(CDBL &x, CDBL &y, CDBL &z) {
  m_x = x;
  m_y = y;
  m_z = z;
}
void Vector::setx(CDBL &x) { m_x = x; }
void Vector::sety(CDBL &y) { m_y = y; }
void Vector::setz(CDBL &z) { m_z = z; }

// ベクトルを加算する
Vector Vector::operator+(const Vector &vecArg) const {
  Vector vecAns;
  vecAns.m_x = m_x + vecArg.m_x;
  vecAns.m_y = m_y + vecArg.m_y;
  vecAns.m_z = m_z + vecArg.m_z;

  return vecAns;
}

// ベクトルを加算する
Vector &Vector::operator+=(const Vector &vecArg) {
  m_x += vecArg.m_x;
  m_y += vecArg.m_y;
  m_z += vecArg.m_z;

  return *this;
}

// ベクトルを減算する
Vector Vector::operator-(const Vector &vecArg) const {
  Vector vecAns;
  vecAns.m_x = m_x - vecArg.m_x;
  vecAns.m_y = m_y - vecArg.m_y;
  vecAns.m_z = m_z - vecArg.m_z;

  return vecAns;
}

// ベクトルを減算する
Vector &Vector::operator-=(const Vector &vecArg) {
  m_x -= vecArg.m_x;
  m_y -= vecArg.m_y;
  m_z -= vecArg.m_z;

  return *this;
}

// ベクトルに数値を乗算する
Vector Vector::operator*(CDBL &val) const {
  Vector vecAns;
  vecAns.m_x = m_x * val;
  vecAns.m_y = m_y * val;
  vecAns.m_z = m_z * val;

  return vecAns;
}

// ベクトルに数値を乗算する
Vector &Vector::operator*=(CDBL &val) {
  m_x *= val;
  m_y *= val;
  m_z *= val;

  return *this;
}

// ベクトルを数値で除算する
Vector Vector::operator/(CDBL &val) const {
  Vector vecAns;
  vecAns.m_x = m_x / val;
  vecAns.m_y = m_y / val;
  vecAns.m_z = m_z / val;

  return vecAns;
}

// ベクトルを数値で除算する
Vector &Vector::operator/=(CDBL &val) {
  m_x /= val;
  m_y /= val;
  m_z /= val;

  return *this;
}

// ベクトルの外積を求める
Vector Vector::operator*(const Vector &vecArg) const {
  Vector vecAns;
  vecAns.m_x = m_y * vecArg.m_z - m_z * vecArg.m_y;
  vecAns.m_y = m_z * vecArg.m_x - m_x * vecArg.m_z;
  vecAns.m_z = m_x * vecArg.m_y - m_y * vecArg.m_x;

  return vecAns;
}

// ベクトルの内積を求める
double Vector::operator%(const Vector &vecArg) const {
  return (m_x * vecArg.getx() + m_y * vecArg.gety() + m_z * vecArg.getz());
}

double Vector::norm() const {
  return sqrt(square(m_x) + square(m_y) + square(m_z));
}

Vector Vector::normalize() const {
  Vector vecAns = *this;

  vecAns /= vecAns.norm();

  return vecAns;
}

Vector Vector::rct2plr() const {
  Vector vecAns;

  // 動径
  vecAns.setx(sqrt(square(m_x) + square(m_y) + square(m_z)));

  // XY平面の偏角Φ
  vecAns.sety(atan2(m_y, m_x));

  // Z軸への偏角Θ
  vecAns.setz(atan2(sqrt(square(m_x) + square(m_y)), m_z));

  return vecAns;
}

Vector Vector::plr2rct() const {
  Vector vecAns(m_x * sin(m_z) * cos(m_y), m_x * sin(m_z) * sin(m_y),
                m_x * cos(m_z));

  return vecAns;
}

void Vector::setPolar2cart(CDBL &radius, CDBL &angleXY, CDBL &angleToZ) {
  // 極座標→直交座標
  set(radius * sin(angleToZ) * cos(angleXY),
      radius * sin(angleToZ) * sin(angleXY), radius * cos(angleToZ));
}
