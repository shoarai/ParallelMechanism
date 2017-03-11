// Copyright © 2017 shoarai

#include "StewartPlatform.h"
#include "Vector/RotationMatrix.h"

StewartPlatform::StewartPlatform() {
  // メカニズムのスケール
  double mechaScale = 10;

  //------------------------------------------//
  // 設計変数の設定							//
  //------------------------------------------//
  double legMaxLen = 3331 / mechaScale; // 脚の最大の長さ
  double legMinLen = 2081 / mechaScale; // 脚の最小の長さ

  double legLen =
      (3331 + 2081) / 2 / mechaScale; // 脚の長さ
                                      //	double legLenEx 	= (3331)
                                      /// mechaScale - legLen;		//
                                      //脚の伸縮可能な長さ

  double platformR = 1600 / mechaScale; // プラットフォームの内接円の半径
  double basePlateR = 1650 / mechaScale; // ベースの内接円の半径

  double platformSpheWid =
      100 / mechaScale; // プラットフォームの軸支点の幅の半分
  double basePlateSpheWid = 300 / mechaScale; // ベースの軸支点の幅の半分

  double platformSpheRad =
      2 * asin(platformSpheWid / platformR); // プラットフォームの軸支点の角度
  double basePlateSpheRad =
      2 * asin(basePlateSpheWid / basePlateR); // ベースの軸支点の角度

  // プラットーフォーム（内接円の半径、球面軸受の配置角度）
  platform = new HexaPlatform(platformR, platformSpheRad);

  // ベース（内接円の半径、球面軸受の配置角度）
  basePlate = new BasePlate(basePlateR, basePlateSpheRad);

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 可変長の脚（最大の長さ、最小の長さ）
    leg[i] = new ExpansibleLeg(legMaxLen, legMinLen);
  }

  /*	legLen		= 250;					// 脚の長さ
          legLenEx 	= 10;					//
     脚の伸縮可能な長さ platformR 		= 200;
     // プラットフォームの内接円の半径
          basePlateR 		= 300;					//
     ベースの内接円の半径 platformSpheRad	= deg2rad( 30 );
     // 軸支点の角度 basePlateSpheRad	= deg2rad( 30 );		//
     軸支点の角度
  */
  // 脚の長さからプラットフォームの高さを計算する
  double ad_b_wid =
      sqrt(square(platformR) + square(basePlateR) -
           2 * platformR * basePlateR *
               cos((deg2rad(120) - platformSpheRad - basePlateSpheRad) / 2));

  // プラットフォームの高さの初期値
  vecPdef.set(0, 0, -sqrt(square(legLen) - square(ad_b_wid)));
}

StewartPlatform::~StewartPlatform() {
  delete platform;
  delete basePlate;

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    delete leg[i];
  }
};

void StewartPlatform::inverseDisplacement() {
  // 回転行列
  RotationMatrix rotMatT(platformPosition.getRotationX(),
                         platformPosition.getRotationY(),
                         platformPosition.getRotationZ());

  //------------------------------------------//
  // ベクトル回転 //
  //------------------------------------------//
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    platform->vecEd[i] = rotMatT.rotateVec(platform->vecE[i]); // E'i = Ei×T
  }

// ベクトルPの設定
#if 0
	// R(X, Y, Z) = T×(x, y, z) + (0, 0, vecPzDef)
	Vector tmp( sixDof.getx(), sixDof.gety(), sixDof.getz() );

	vecP = trnsMat.trans(tmp);

	vecP.setz(vecP.getz() + vecPzDef);	// 初期Rzを加算
#endif

#if 1
  // R(X, Y, Z) = platform(x, y, z)	動作領域計算用
  vecP.set(platformPosition.getTranslationX(),
           platformPosition.getTranslationY(),
           platformPosition.getTranslationZ());
  vecP += vecPdef;
#endif

  //------------------------------------------//
  // ベクトル計算 //
  //------------------------------------------//
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 脚ベクトルを求める
    leg[i]->vecL = basePlate->vecS[i] - platform->vecEd[i] - vecP;

    // 脚の長さを算出する
    leg[i]->setLength(leg[i]->vecL.norm());

    //		leg[i]->setLength(
    //			sqrt( square( basePlate->vecS[i].getx() - (
    // platform->vecEd[i].getx() +  vecP.getx() ) ) +
    // square(  basePlate->vecS[i].gety() - ( platform->vecEd[i].gety() +
    // vecP.gety() ) )
    //				+ square( basePlate->vecS[i].getz() - (
    // platform->vecEd[i].getz() +  vecP.getz() ) ) ) );
  }
}

void StewartPlatform::judgeMechanismState() {
  // プラットフォームの高さの判定
  // プラットフォームの高さが地面より下
  if (vecP.getz() >= 0) {
    beOutsideLimit();
  }
  // プラットフォームの高さが脚の最大長さより上
  else if (-vecP.getz() > leg[0]->getMax()) {
    beOutsideLimit();
  }

  // 脚長の判定
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 脚長が最大を超えているか
    if (leg[i]->getLength() > leg[i]->getMax()) {
      beOutsideLimit();
    }
    // 脚長が最小を下回っているか
    else if (leg[i]->getLength() < leg[i]->getMin()) {
      beOutsideLimit();
    }
  }

  return;
}

void StewartPlatform::calculateJacobianMatrix() {
  // 中間媒介ベクトル
  Vector vecZ
      [LEG_NUM_MAX];           // ベースの球面軸受からプラットフォームの球面軸受方向の単位ベクトル
  Vector vecEd_Z[LEG_NUM_MAX]; // ベクトルZとベクトルE'の外積

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    vecZ[i] = leg[i]->vecL.normalize();
    vecEd_Z[i] = platform->vecEd[i] * vecZ[i];
  }

  // ヤコビ行列１
  SquareMat jacobianMatrix1(
      vecZ[LEG_1].getx(), vecZ[LEG_1].gety(), vecZ[LEG_1].getz(),
      vecEd_Z[LEG_1].getx(), vecEd_Z[LEG_1].gety(), vecEd_Z[LEG_1].getz(),
      vecZ[LEG_2].getx(), vecZ[LEG_2].gety(), vecZ[LEG_2].getz(),
      vecEd_Z[LEG_2].getx(), vecEd_Z[LEG_2].gety(), vecEd_Z[LEG_2].getz(),
      vecZ[LEG_3].getx(), vecZ[LEG_3].gety(), vecZ[LEG_3].getz(),
      vecEd_Z[LEG_3].getx(), vecEd_Z[LEG_3].gety(), vecEd_Z[LEG_3].getz(),
      vecZ[LEG_4].getx(), vecZ[LEG_4].gety(), vecZ[LEG_4].getz(),
      vecEd_Z[LEG_4].getx(), vecEd_Z[LEG_4].gety(), vecEd_Z[LEG_4].getz(),
      vecZ[LEG_5].getx(), vecZ[LEG_5].gety(), vecZ[LEG_5].getz(),
      vecEd_Z[LEG_5].getx(), vecEd_Z[LEG_5].gety(), vecEd_Z[LEG_5].getz(),
      vecZ[LEG_6].getx(), vecZ[LEG_6].gety(), vecZ[LEG_6].getz(),
      vecEd_Z[LEG_6].getx(), vecEd_Z[LEG_6].gety(), vecEd_Z[LEG_6].getz());

  jacobianMatrix = jacobianMatrix1;

  // ヤコビ行列２
  SquareMat jacobianMatrix2(1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                            0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
                            0, 1);

  // ヤコビ行列式計算
  jacobianDeterminant = jacobianMatrix.det();
}

void StewartPlatform::changePosition(Position &position) {
  // 可動領域判定リセット
  beWithinLimit();

  platformPosition = position;
  inverseDisplacement();
  judgeMechanismState();

  // 脚長の初期値
  static double legLenDef = leg[LEG_1]->getLength();

  // 脚データを設定する
  legPos.setData(
      leg[LEG_1]->getLength() - legLenDef, leg[LEG_2]->getLength() - legLenDef,
      leg[LEG_3]->getLength() - legLenDef, leg[LEG_4]->getLength() - legLenDef,
      leg[LEG_5]->getLength() - legLenDef, leg[LEG_6]->getLength() - legLenDef);
}

void StewartPlatform::calculateActuatorVelocity(CDBL &Vx, CDBL &Vy, CDBL &Vz,
                                                CDBL &Wphi, CDBL &Wtheta,
                                                CDBL &Wpsi) {
  sixVel.setData(Vx, Vy, Vz, Wphi, Wtheta, Wpsi);
  calculateJacobianMatrix();

  // プラットフォームの速度ベクトル：x. = [Vx  Vy  Vz  ωφ ωθ ωψ]
  Matrix matXdot(6, 1);
  matXdot(1, 1) = sixVel.getx();
  matXdot(2, 1) = sixVel.gety();
  matXdot(3, 1) = sixVel.getz();
  matXdot(4, 1) = sixVel.getPhi();
  matXdot(5, 1) = sixVel.getSit();
  matXdot(6, 1) = sixVel.getPsi();

  // 速度解析（q. = J * x.）
  Matrix matQdot = jacobianMatrix * matXdot;

  // 脚の速度を設定する
  legVel.setData(matQdot(1, 1), matQdot(2, 1), matQdot(3, 1), matQdot(4, 1),
                 matQdot(5, 1), matQdot(6, 1));
}
