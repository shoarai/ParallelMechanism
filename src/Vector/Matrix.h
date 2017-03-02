//------------------------------------------//
// ���O			�F�s��						//
// CPU			�F //
// �R���p�C��	�FVisual C++				//
// �@�\			�F�s��						//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.05.15	�V��	�V�K�쐬			//
//------------------------------------------//
#ifndef _MATRIX_H_
#define _MATRIX_H_

//#define _STD_VECTOR_		// std::vector���g��
//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#ifdef _STD_VECTOR_
#include <vector>
#endif
#include "typedef.h"

//------------------------------------------//
//				�N�@���@�X //
//------------------------------------------//
class Matrix {
public:
  CUINT m_row; // �s
  CUINT m_col; // ��

#ifdef _STD_VECTOR_
  std::vector<std::vector<double>> val;
#else
  double **val; // �s���v�f�p�|�C���^
#endif

public:
  explicit Matrix(UINT, UINT); // �R���X�g���N�^
  Matrix(const Matrix &);      // �R�s�[�R���X�g���N�^
  virtual ~Matrix();           // �f�X�g���N�^

  // �s���v�f�������o��
  double &operator()(UINT row, UINT colN);

  // �s���̑���
  Matrix &operator=(const Matrix &);

  // �s���Ƃ̉����Z
  Matrix operator+(const Matrix &) const;
  Matrix &operator+=(const Matrix &);
  Matrix operator-(const Matrix &) const;
  Matrix &operator-=(const Matrix &);

  // �s���Ƃ̐�
  Matrix operator*(const Matrix &)const;

  // ���l�Ƃ̏揜�Z
  Matrix operator*(CDBL &)const;
  Matrix &operator*=(CDBL &);
  Matrix operator/(CDBL &) const;
  Matrix &operator/=(CDBL &);

  // �]�u�s��
  Matrix transpose() const;
};

#endif
