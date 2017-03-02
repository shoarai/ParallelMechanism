//------------------------------------------//
// ���O			�F�x�N�g��					//
// CPU			�F //
// �R���p�C��	�FVisual C++				//
// �@�\			�F�x�N�g��					//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.05.15	�V��	�V�K�쐬			//
//------------------------------------------//
#ifndef _VECTOR_H_
#define _VECTOR_H_

//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#include "typedef.h"

//------------------------------------------//
//				�N�@���@�X //
//------------------------------------------//
class Vector {
private:
  double m_x; // x����
  double m_y; // y����
  double m_z; // z����

public:
  // �R���X�g���N�^
  Vector();
  Vector(CDBL &, CDBL &, CDBL &);

  // �x�N�g�������������o��
  CDBL getx() const;
  CDBL gety() const;
  CDBL getz() const;

  // �x�N�g���������ݒ肷��
  void set(CDBL &, CDBL &, CDBL &);
  void setx(CDBL &);
  void sety(CDBL &);
  void setz(CDBL &);

  // �x�N�g���Ƃ̉����Z
  Vector operator+(const Vector &) const;
  Vector &operator+=(const Vector &);
  Vector operator-(const Vector &) const;
  Vector &operator-=(const Vector &);

  // ���l�Ƃ̏揜�Z
  Vector operator*(CDBL &)const;
  Vector &operator*=(CDBL &);
  Vector operator/(CDBL &) const;
  Vector &operator/=(CDBL &);

  Vector operator*(const Vector &)const;  //  �x�N�g���̊O��
  double operator%(const Vector &) const; //  �x�N�g���̓���

  // VECTOR�N���X�ɃL���X�g����
  // operator VECTOR();

  double norm() const; // �m���������߂�
  Vector
  normalize() const; // �x�N�g���𐳋K��������

  // ���W�ϊ�
  Vector rct2plr() const; // �������W�n���ɍ��W�n
  Vector plr2rct() const; // �ɍ��W�n���������W�n

  // �ɍ��W�n���������W�n�i2�����Ή��j
  void setPolar2cart(CDBL &rad, CDBL &angleXY, CDBL &angleToZ = deg2rad(90));
};

#endif // _VECTOR_H_
