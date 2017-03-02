//------------------------------------------//
// ���O			�F�s��						//
// CPU			�F //
// �R���p�C��	�FVisual C++				//
// �@�\			�F�s��						//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.05.15	�V��	�V�K�쐬			//
//------------------------------------------//
#ifndef _SQUARE_MATRIX_H_
#define _SQUARE_MATRIX_H_
//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#include "Matrix.h"

//------------------------------------------//
//				�N�@���@�X //
//------------------------------------------//
class SquareMat : public Matrix {
public:
  int num; // �s���̍s���i���񐔁j
  // CUINT num; // �s���̍s���i���񐔁j

public:
  // �R���X�g���N�^
  explicit SquareMat(UINT);

  SquareMat(CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &,
            CDBL &, CDBL &, CDBL &, CDBL &);

  SquareMat(const Matrix &); // �R�s�[�R���X�g���N�^
  virtual ~SquareMat(){};    // �f�X�g���N�^

  // �����s���̑���
  SquareMat &operator=(const Matrix &);

  // �s���N���X�ւ̃L���X�g
  // operator Matrix();

  double norm() const;              // �m����
  double det() const;               // �s����
  SquareMat invrs(CDBL &det) const; // �t�s��

private:
  double cofactor(UINT, UINT) const; // �]���q
  double trace() const;              // �Ίp�a
  SquareMat adjMat() const;          // �]���q�s��
};

#endif
