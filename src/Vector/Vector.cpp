//------------------------------------------//
// ���O			�F���W�N���X				//
// CPU			�F							//
// �R���p�C��	�FVisual C++				//
// �@�\			�F���W�N���X				//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.05.15	�V��	�V�K�쐬			//
//------------------------------------------//

//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#include "Vector.h"

// �R���X�g���N�^
Vector::Vector()
	: m_x(), m_y(), m_z(){}

Vector::Vector(CDBL& x, CDBL& y, CDBL& z)
	: m_x(x), m_y(y), m_z(z){}

// �x�N�g�������������o��
CDBL Vector::getx() const{
	return m_x;
}
CDBL Vector::gety() const{
	return m_y;
}
CDBL Vector::getz() const{
	return m_z;
}


// �x�N�g���������ݒ肷��
void Vector::set(CDBL& x, CDBL& y, CDBL& z){
	m_x = x;
	m_y = y;
	m_z = z;
}
void Vector::setx(CDBL& x){
	m_x = x;
}
void Vector::sety(CDBL& y){
	m_y = y;
}
void Vector::setz(CDBL& z){
	m_z = z;
}

// �x�N�g�������Z����
Vector Vector::operator+(const Vector &vecArg) const
{
	Vector vecAns;
	vecAns.m_x = m_x + vecArg.m_x;
	vecAns.m_y = m_y + vecArg.m_y;
	vecAns.m_z = m_z + vecArg.m_z;

	return vecAns;
}

// �x�N�g�������Z����
Vector& Vector::operator+=(const Vector &vecArg)
{
	m_x += vecArg.m_x;
	m_y += vecArg.m_y;
	m_z += vecArg.m_z;

	return *this;
}

// �x�N�g�������Z����
Vector Vector::operator-(const Vector &vecArg) const
{
	Vector vecAns;
	vecAns.m_x = m_x - vecArg.m_x;
	vecAns.m_y = m_y - vecArg.m_y;
	vecAns.m_z = m_z - vecArg.m_z;

	return vecAns;
}

// �x�N�g�������Z����
Vector& Vector::operator-=(const Vector &vecArg)
{
	m_x -= vecArg.m_x;
	m_y -= vecArg.m_y;
	m_z -= vecArg.m_z;

	return *this;
}

// �x�N�g���ɐ��l�����Z����
Vector Vector::operator*(CDBL& val) const
{
	Vector vecAns;
	vecAns.m_x = m_x * val;
	vecAns.m_y = m_y * val;
	vecAns.m_z = m_z * val;

	return vecAns;
}

// �x�N�g���ɐ��l�����Z����
Vector& Vector::operator*=(CDBL& val)
{
	m_x *= val;
	m_y *= val;
	m_z *= val;

	return *this;
}

// �x�N�g���𐔒l�ŏ��Z����
Vector Vector::operator/(CDBL& val) const
{
	Vector vecAns;
	vecAns.m_x = m_x / val;
	vecAns.m_y = m_y / val;
	vecAns.m_z = m_z / val;

	return vecAns;
}

// �x�N�g���𐔒l�ŏ��Z����
Vector& Vector::operator/=(CDBL& val)
{
	m_x /= val;
	m_y /= val;
	m_z /= val;

	return *this;
}

// �x�N�g���̊O�ς����߂�
Vector Vector::operator*(const Vector &vecArg) const
{
	Vector vecAns;
	vecAns.m_x = m_y * vecArg.m_z - m_z * vecArg.m_y;
	vecAns.m_y = m_z * vecArg.m_x - m_x * vecArg.m_z;
	vecAns.m_z = m_x * vecArg.m_y - m_y * vecArg.m_x;

	return vecAns;
}

// �x�N�g���̓��ς����߂�
double Vector::operator%(const Vector &vecArg) const
{
	return (m_x * vecArg.getx() + m_y * vecArg.gety() + m_z * vecArg.getz());
}

// VECTOR�N���X�ɃL���X�g����
// Vector::operator VECTOR()
// {
// 	VECTOR vecAns;
//
// 	vecAns.x = static_cast<float>( m_y );
// 	vecAns.y = static_cast<float>(-m_z );
// 	vecAns.z = static_cast<float>( m_x );
//
// 	return vecAns;
// }

//------------------------------------------//
// �@�\		�F�x�N�g���̃m���������߂�		//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�m����						//
// -----------------------------------------//
// ���t			����	���e				//
// 2012.08.11	�V��	�V�K�쐬			//
//------------------------------------------//
double Vector::norm() const
{
	return sqrt(square(m_x) + square(m_y) + square(m_z));
}

//------------------------------------------//
// �@�\		�F�x�N�g���𐳋K������			//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F����							//
// -----------------------------------------//
// ���t			����	���e				//
// 2012.08.11	�V��	�V�K�쐬			//
//------------------------------------------//
Vector Vector::normalize() const
{
	Vector vecAns = *this;

	vecAns /= vecAns.norm();

	return vecAns;
}

//------------------------------------------//
// �@�\		�F�������W���ɍ��W				//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�x�N�g��						//
// -----------------------------------------//
// ���t			����	���e				//
// 2012.08.15	�V��	�V�K�쐬			//
//------------------------------------------//
Vector Vector::rct2plr() const
{
	Vector vecAns;

	// ���a
	vecAns.setx( sqrt(square(m_x) + square(m_y) + square(m_z)) );

	// XY���ʂ̕Ίp��
	vecAns.sety( atan2( m_y, m_x ) );

	// Z���ւ̕Ίp��
	vecAns.setz( atan2( sqrt(square(m_x) + square(m_y)), m_z) );

	return vecAns;
}

//------------------------------------------//
// �@�\		�F�ɍ��W���������W				//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�x�N�g��						//
// -----------------------------------------//
// ���t			����	���e				//
// 2012.08.15	�V��	�V�K�쐬			//
//------------------------------------------//
Vector Vector::plr2rct() const
{
	Vector vecAns(
		m_x * sin(m_z) * cos(m_y),
		m_x * sin(m_z) * sin(m_y),
		m_x * cos(m_z) );

	return vecAns;
}

//------------------------------------------//
// �@�\		�F�ɍ��W���������W				//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�x�N�g��						//
// -----------------------------------------//
// ���t			����	���e				//
// 2012.08.15	�V��	�V�K�쐬			//
//------------------------------------------//
void Vector::setPolar2cart(CDBL& radius, CDBL& angleXY, CDBL& angleToZ)
{
	// �ɍ��W���������W
	set( radius * sin(angleToZ) * cos(angleXY),
		 radius * sin(angleToZ) * sin(angleXY),
		 radius * cos(angleToZ) );
}
