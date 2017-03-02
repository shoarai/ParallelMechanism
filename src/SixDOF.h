// 機能			：6自由度運動
#ifndef _SIX_DOF_H_
#define _SIX_DOF_H_

//------------------------------------------//
//				インクルード				//
//------------------------------------------//
#include "Vector/typedef.h"

//------------------------------------------//
//				ク　ラ　ス //
//------------------------------------------//
class SixDOF {
public:
  SixDOF();
  SixDOF(const double &dis, const double &ang);
  double getx() const;
  double gety() const;
  double getz() const;
  double getPhi() const;
  double getSit() const;
  double getPsi() const;
  void setData(const double &x, const double &y, const double &z,
               const double &phi, const double &theta, const double &psi);

private:
  // 6自由度運動
  double m_x;     // x軸方向
  double m_y;     // y軸方向
  double m_z;     // z軸方向
  double m_phi;   // x軸周り
  double m_theta; // y軸周り
  double m_psi;   // z軸周り

  // 運動操作の刻み
  double stepDis; // 変位
  double stepAng; // 角度
};

// 運動取得
inline double SixDOF::getx() const { return m_x; };
inline double SixDOF::gety() const { return m_y; };
inline double SixDOF::getz() const { return m_z; };
inline double SixDOF::getPhi() const { return m_phi; };
inline double SixDOF::getSit() const { return m_theta; };
inline double SixDOF::getPsi() const { return m_psi; };

#endif // _SIX_DOF_H_
