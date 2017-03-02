//------------------------------------------//
// 名前			：座標クラス				//
// CPU			：							//
// コンパイラ	：Visual C++				//
// 機能			：座標クラス				//
//----------------- 履歴 -------------------//
// 日付			作者	内容				//
// 2012.05.15	新井	新規作成			//
//------------------------------------------//

//------------------------------------------//
//				インクルード				//
//------------------------------------------//
#include "RotationMatrix.h"

//------------------------------------------//
// 機能		：コンストラクタ				//
// 注意		：なし							//
// メモ		：なし							//
// 参照		：なし							//
// 作者		：新井							//
// 引数		：なし							//
// 戻り値	：なし							//
// -----------------------------------------//
// 日付			作者	内容				//
// 2012.11.02	新井	新規作成			//
//------------------------------------------//
RotationMatrix::RotationMatrix()
{
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			element[i][j] = 0;
		}
	}
}

RotationMatrix::RotationMatrix(
	const double &phi,		// x軸周りの角度
	const double &sit,		// y軸周りの角度
	const double &psi)		// z軸周りの角度
{
	calcRotateMat(phi, sit, psi);
}

//------------------------------------------//
// 機能		：回転行列を求める				//
// 注意		：なし							//
// メモ		：なし							//
// 参照		：なし							//
// 作者		：新井							//
// 引数		：なし							//
// 戻り値	：なし							//
// -----------------------------------------//
// 日付			作者	内容				//
// 2012.06.17	新井	新規作成			//
//------------------------------------------//
void RotationMatrix::calcRotateMat(const double &phi, const double &sit, const double &psi)
{
	// 各角度の三角関数
	const double sphi = sin( phi ); 
	const double cphi = cos( phi );
	const double ssit = sin( sit );
	const double csit = cos( sit );
	const double spsi = sin( psi );
	const double cpsi = cos( psi );

	// 回転行列
	element[0][0] = csit * cpsi; element[0][1] = sphi * ssit * cpsi - cphi * spsi; element[0][2] = cphi * ssit * cpsi - sphi * spsi;
	element[1][0] = csit * spsi; element[1][1] = sphi * ssit * spsi + cphi * cpsi; element[1][2] = cphi * ssit * spsi - sphi * cpsi;
	element[2][0] =	-ssit	; element[2][1] =			sphi * csit			   ; element[2][2] =			cphi * csit			  ;
}

//------------------------------------------//
// 機能		：ベクトル回転					//
// 注意		：なし							//
// メモ		：なし							//
// 参照		：なし							//
// 作者		：新井							//
// 引数		：ベクトル						//
// 戻り値	：ベクトル						//
// -----------------------------------------//
// 日付			作者	内容				//
// 2012.06.17	新井	新規作成			//
//------------------------------------------//
Vector RotationMatrix::rotateVec(const Vector &vecArg) const
{
	Vector vecAns(
		element[0][0] * vecArg.getx() + element[0][1] * vecArg.gety() + element[0][2] * vecArg.getz(),
		element[1][0] * vecArg.getx() + element[1][1] * vecArg.gety() + element[1][2] * vecArg.getz(),
		element[2][0] * vecArg.getx() + element[2][1] * vecArg.gety() + element[2][2] * vecArg.getz()
	);
	
	return vecAns;
}

//------------------------------------------//
// 機能		：ベクトル逆回転				//
// 注意		：なし							//
// メモ		：なし							//
// 参照		：なし							//
// 作者		：新井							//
// 引数		：ベクトル						//
// 戻り値	：ベクトル						//
// -----------------------------------------//
// 日付			作者	内容				//
// 2012.06.19	新井	新規作成			//
//------------------------------------------//
Vector RotationMatrix::rotateInvVec(const Vector &vecArg) const
{
	Vector vecAns(
		element[0][0] * vecArg.getx() + element[1][0] * vecArg.gety() + element[2][0] * vecArg.getz(),
		element[0][1] * vecArg.getx() + element[1][1] * vecArg.gety() + element[2][1] * vecArg.getz(),
		element[0][2] * vecArg.getx() + element[1][2] * vecArg.gety() + element[2][2] * vecArg.getz()
	);
	
	return vecAns;
}

//------------------------------------------//
// 機能		：行列の積						//
// 注意		：なし							//
// メモ		：なし							//
// 参照		：なし							//
// 作者		：新井							//
// 引数		：ベクトル						//
// 戻り値	：ベクトル						//
// -----------------------------------------//
// 日付			作者	内容				//
// 2012.11.08	新井	新規作成			//
//------------------------------------------//
RotationMatrix RotationMatrix::operator*(const RotationMatrix& rmatArg) const
{
	RotationMatrix rmatAns;

	// 行列の乗算
	for(UINT i = 0; i < NUM; i++){
		for(UINT j = 0; j < NUM; j++){
			for(UINT k = 0; k < NUM; k++){
				rmatAns.element[i][j] += element[i][k] * rmatArg.element[k][j];
			}
		}
	}

	return rmatAns;
}