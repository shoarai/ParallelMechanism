#include "StewartPlatform.h"
#include "Vector/RotationMatrix.h"

// #include <iomanip>  // setw用
#include <iostream> // cout用

using namespace std;

// 変数初期化
HexaPlatform::HexaPlatform(CDBL &rad, CDBL &ang)
    : radius(rad), angle(ang), angle2(PI * 2 / 3 - ang) {
  // 球面軸受の初期ベクトルの初期化
  vecE[0].set(radius * cos(angle / 2), radius * sin(angle / 2), 0);
  vecE[1].set(radius * cos(angle / 2), -radius * sin(angle / 2), 0);

  vecE[2].set(-radius * sin(PI / 2 - angle - angle2 / 2),
              -radius * cos(PI / 2 - angle - angle2 / 2), 0);

  vecE[3].set(-radius * cos(angle2 / 2), -radius * sin(angle2 / 2), 0);
  vecE[4].set(-radius * cos(angle2 / 2), radius * sin(angle2 / 2), 0);

  vecE[5].set(-radius * sin(PI / 2 - angle - angle2 / 2),
              radius * cos(PI / 2 - angle - angle2 / 2), 0);
}

// 変数初期化
Base::Base(CDBL &rad, CDBL &ang)
    : radius(rad), angle(ang), angle2(PI * 2 / 3 - ang) {
  // 球面軸受のベクトルの初期化
  vecS[0].set(radius * cos(angle2 / 2), radius * sin(angle2 / 2), 0);
  vecS[1].set(radius * cos(angle2 / 2), -radius * sin(angle2 / 2), 0);
  vecS[2].set(radius * sin(PI / 2 - angle - angle2 / 2),
              -radius * cos(PI / 2 - angle - angle2 / 2), 0);
  vecS[3].set(-radius * cos(angle / 2), -radius * sin(angle / 2), 0);
  vecS[4].set(-radius * cos(angle / 2), radius * sin(angle / 2), 0);
  vecS[5].set(radius * sin(PI / 2 - angle - angle2 / 2),
              radius * cos(PI / 2 - angle - angle2 / 2), 0);
}

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

  double pltR = 1600 / mechaScale; // プラットフォームの内接円の半径
  double baseR = 1650 / mechaScale; // ベースの内接円の半径

  double pltSpheWid = 100 / mechaScale; // プラットフォームの軸支点の幅の半分
  double baseSpheWid = 300 / mechaScale; // ベースの軸支点の幅の半分

  double pltSpheRad =
      2 * asin(pltSpheWid / pltR); // プラットフォームの軸支点の角度
  double baseSpheRad = 2 * asin(baseSpheWid / baseR); // ベースの軸支点の角度

  // プラットーフォーム（内接円の半径、球面軸受の配置角度）
  plt = new HexaPlatform(pltR, pltSpheRad);

  // ベース（内接円の半径、球面軸受の配置角度）
  base = new Base(baseR, baseSpheRad);

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 可変長の脚（最大の長さ、最小の長さ）
    leg[i] = new ExpansibleLeg(legMaxLen, legMinLen);
  }

  /*	legLen		= 250;					// 脚の長さ
          legLenEx 	= 10;					//
     脚の伸縮可能な長さ pltR 		= 200;
     // プラットフォームの内接円の半径
          baseR 		= 300;					//
     ベースの内接円の半径 pltSpheRad	= deg2rad( 30 );		//
     軸支点の角度 baseSpheRad	= deg2rad( 30 );		// 軸支点の角度
  */
  // 脚の長さからプラットフォームの高さを計算する
  double ad_b_wid = sqrt(
      square(pltR) + square(baseR) -
      2 * pltR * baseR * cos((deg2rad(120) - pltSpheRad - baseSpheRad) / 2));

  // プラットフォームの高さの初期値
  vecPdef.set(0, 0, -sqrt(square(legLen) - square(ad_b_wid)));
}

StewartPlatform::~StewartPlatform() {
  delete plt;
  delete base;

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    delete leg[i];
  }
};

// 機能		：回転行列をかける
void StewartPlatform::invrsDis() {
  // 回転行列
  RotationMatrix rotMatT(sixDof.getPhi(), sixDof.getSit(), sixDof.getPsi());

  //------------------------------------------//
  // ベクトル回転 //
  //------------------------------------------//
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    plt->vecEd[i] = rotMatT.rotateVec(plt->vecE[i]); // E'i = Ei×T
  }

// ベクトルPの設定
#if 0
	// R(X, Y, Z) = T×(x, y, z) + (0, 0, vecPzDef)
	Vector tmp( sixDof.getx(), sixDof.gety(), sixDof.getz() );

	vecP = trnsMat.trans(tmp);

	vecP.setz(vecP.getz() + vecPzDef);	// 初期Rzを加算
#endif

#if 1
  // R(X, Y, Z) = plt(x, y, z)	動作領域計算用
  vecP.set(sixDof.getx(), sixDof.gety(), sixDof.getz());
  vecP += vecPdef;
#endif

  //------------------------------------------//
  // ベクトル計算 //
  //------------------------------------------//
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 脚ベクトルを求める
    leg[i]->vecL = base->vecS[i] - plt->vecEd[i] - vecP;

    // 脚の長さを算出する
    leg[i]->setLen(leg[i]->vecL.norm());

    //		leg[i]->setLen(
    //			sqrt( square( base->vecS[i].getx() - (
    // plt->vecEd[i].getx() +  vecP.getx() ) ) 				+
    // square(  base->vecS[i].gety() - ( plt->vecEd[i].gety() +  vecP.gety() ) )
    //				+ square( base->vecS[i].getz() - (
    // plt->vecEd[i].getz() +  vecP.getz() ) ) ) );
  }
}

// 可動制限内か判定する
void StewartPlatform::chkLmt() {
  // プラットフォームの高さの判定
  // プラットフォームの高さが地面より下
  if (vecP.getz() >= 0) {
    outLmt(); // 可動領域外
  }
  // プラットフォームの高さが脚の最大長さより上
  else if (-vecP.getz() > leg[0]->getMax()) {
    outLmt(); // 可動領域外
  }

  // 脚長の判定
  for (int i = 0; i < LEG_NUM_MAX; i++) {
    // 脚長が最大を超えているか
    if (leg[i]->getLen() > leg[i]->getMax()) {
      outLmt(); // 可動領域外
    }
    // 脚長が最小を下回っているか
    else if (leg[i]->getLen() < leg[i]->getMin()) {
      outLmt(); // 可動領域外
    }
  }

  return;
}

// 機能		：ヤコビ行列を算出する
void StewartPlatform::calcJacobi() {
  // 中間媒介ベクトル
  Vector vecZ
      [LEG_NUM_MAX];           // ベースの球面軸受からプラットフォームの球面軸受方向の単位ベクトル
  Vector vecEd_Z[LEG_NUM_MAX]; // ベクトルZとベクトルE'の外積

  for (int i = 0; i < LEG_NUM_MAX; i++) {
    vecZ[i] = leg[i]->vecL.normalize();
    vecEd_Z[i] = plt->vecEd[i] * vecZ[i];
  }

  // ヤコビ行列１
  SquareMat matJ1(
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

  matJ = matJ1;

  // ヤコビ行列２
  SquareMat matJ2(1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                  1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1);

  // ヤコビ行列式計算
  detJ = matJ.det();
}

// 座標を算出する
void StewartPlatform::calculateCoordinate() {
  // 可動領域判定リセット
  inLmt();

  // 逆変位計算
  invrsDis();

  // 可動範囲チェック
  chkLmt();

  // 脚長の初期値
  static double legLenDef = leg[LEG_1]->getLen();

  // 脚データを設定する
  legPos.setData(
      leg[LEG_1]->getLen() - legLenDef, leg[LEG_2]->getLen() - legLenDef,
      leg[LEG_3]->getLen() - legLenDef, leg[LEG_4]->getLen() - legLenDef,
      leg[LEG_5]->getLen() - legLenDef, leg[LEG_6]->getLen() - legLenDef);
}

// 脚底部の速度算出
void StewartPlatform::calculateVelocity() {
  // ヤコビ行列計算
  calcJacobi();

  // プラットフォームの速度ベクトル：x. = [Vx  Vy  Vz  ωφ ωθ ωψ]
  Matrix matXdot(6, 1);

  // プラットフォームの速度設定
  matXdot(1, 1) = sixVel.getx();
  matXdot(2, 1) = sixVel.gety();
  matXdot(3, 1) = sixVel.getz();
  matXdot(4, 1) = sixVel.getPhi();
  matXdot(5, 1) = sixVel.getSit();
  matXdot(6, 1) = sixVel.getPsi();

  // 速度解析（q. = J * x.）
  Matrix matQdot = matJ * matXdot;

  // 脚の速度を設定する
  legVel.setData(matQdot(1, 1), matQdot(2, 1), matQdot(3, 1), matQdot(4, 1),
                 matQdot(5, 1), matQdot(6, 1));
}
