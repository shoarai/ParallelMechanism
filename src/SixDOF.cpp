// Copyright (c) 2017 shoarai

#include "SixDOF.h"
#include <iostream>

using namespace std;

SixDOF::SixDOF()
    : m_x(0), m_y(0), m_z(0), m_phi(0), m_theta(0), m_psi(0), stepDis(0.5),
      stepAng(deg2rad(0.5)) {
  // 処理なし
}

SixDOF::SixDOF(CDBL &dis, CDBL &ang)
    : m_x(0), m_y(0), m_z(0), m_phi(0), m_theta(0), m_psi(0), stepDis(dis),
      stepAng(deg2rad(ang)) {
  // 処理なし
}

// 機能		：変数設定
void SixDOF::setData(CDBL &x, CDBL &y, CDBL &z, CDBL &phi, CDBL &theta,
                     CDBL &psi) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_phi = phi;
  m_theta = theta;
  m_psi = psi;
}
