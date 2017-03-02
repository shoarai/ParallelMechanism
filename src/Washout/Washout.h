//------------------------------------------//
// ���O			�F�E�H�b�V���A�E�g�w�b�_	//
// CPU			�F //
// �R���p�C��	�FVisual C++				//
// �@�\			�F�E�H�b�V���A�E�g��������	//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.04.29	�V��	�E�H�b�V���A�E�g���N���X��	//
// 2012.06.17	�V��	�t�B���^�N���X�쐬�A//
//						�E�H�b�V���A�E�g�̈����Ɍv�Z����
////
//------------------------------------------//
#pragma once //�C���N���[�h�K�[�h
//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#include "../Vector/Vector.h"

//------------------------------------------//
//				�N�@���@�X //
//------------------------------------------//
// �t�B���^
class Filter;

// �E�H�b�V���A�E�g
class Washout {
private:
  UINT time_ms;       // �v�Z����
  double transScale;  // ���i�̃X�P�[��
  double rotateScale; // ���]�̃X�P�[��

  // �d�͉����xgs
  Vector vecGs;

  // �o�͒l
  double m_x, m_y, m_z, m_phi, m_sit, m_psi;

  // ���Ԕ}���ϐ��A���x�A�p�x
  double m_vx, m_vy, m_vz, phi_t, phi_r, sit_t, sit_r;

  // �p�C���b�g�̑̊��^��
  struct st6DOF {
    double ax, ay, az, wphi, wsit, wpsi;
  } stPilot;

  //------------------------------------------//
  // �t�B���^ //
  //------------------------------------------//
  Filter *tHPF[3];
  Filter *rLPF[3];
  Filter *rHPF[3];

  //------------------------------------------//
  // �C�����C��								//
  //------------------------------------------//
  // �ϕ�
  inline double timeInteg(CDBL &x, CDBL &v) {
    return (x + v * msec2sec(time_ms));
  }

public:
  // �R���X�g���N�^
  Washout(UINT t_ms, CDBL &tScale = 1, CDBL &rScale = 1);
  ~Washout(); // �f�X�g���N�^

  // �E�H�b�V���A�E�g����
  void washout(CDBL &, CDBL &, CDBL &, CDBL &, CDBL &, CDBL &);

  // �����x�`��
  void rend(const Vector &);

  // �ϐ��擾
  CDBL getx() const { return m_x; };
  CDBL gety() const { return m_y; };
  CDBL getz() const { return m_z; };
  CDBL getPhi() const { return m_phi; };
  CDBL getSit() const { return m_sit; };
  CDBL getPsi() const { return m_psi; };
};
