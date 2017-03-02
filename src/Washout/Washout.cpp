//------------------------------------------//
// ���O			�F�E�H�b�V���A�E�g			//
// CPU			�F							//
// �R���p�C��	�FVisual C++				//
// �@�\			�F�E�H�b�V���A�E�g����		//
//----------------- ���� -------------------//
// ���t			����	���e				//
// 2012.03.11	�V��	�R�����g�ǉ�		//
// 2012.03.22	�V��	�t�B���^���N���X��	//
// 2012.04.29	�V��	�E�H�b�V���A�E�g���N���X��	//
//------------------------------------------//

//------------------------------------------//
//				�C���N���[�h				//
//------------------------------------------//
#include "Washout.h"
#include "Filter.h"

#include <iostream>	// memset�p

//------------------------------------------//
// �@�\		�F�R���X�g���N�^				//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�Ȃ�							//
//------------------------------------------//
// ���t			����	���e				//
// 2012.04.29	�V��	�V�K�쐬			//
//------------------------------------------//
Washout::Washout(UINT t_ms, CDBL& tScale, CDBL& rScale) :
	time_ms(t_ms),
	transScale(tScale),
	rotateScale(rScale),
	vecGs(0, 0, GRAVITY_mm)
{
	// ������
	m_x = m_y = m_z = m_phi = m_sit = m_psi = 0;
	m_vx = m_vy = m_vz = phi_t = phi_r = sit_t = sit_r = 0;

	memset( &stPilot, 0, sizeof(stPilot) );

	// �t�B���^�ϐ�
	double freq_wn  = 2.5;			// ��n �F�܂��_���g���i�n�C�p�X�j
	double freq_wlp = 2 * freq_wn;	// ��LP�F�܂��_���g���i���[�p�X�j
	double damp		= 1;			// ��LP�F�_���s���O�W��

	// Translation�̃n�C�p�X�t�B���^
	tHPF[0] = new JAXA_tHPF(time_ms, freq_wn);
	tHPF[1] = new JAXA_tHPF(time_ms, freq_wn);
	tHPF[2] = new JAXA_tHPF(time_ms, freq_wn);

	// Tilt-Coordination�̃��[�p�X�t�B���^
	rLPF[0] = new JAXA_tLPF(time_ms, freq_wlp, damp);
	rLPF[1] = new JAXA_tLPF(time_ms, freq_wlp, damp);
	rLPF[2] = new JAXA_tLPF(time_ms, freq_wlp, damp);

	// Rotation�̃n�C�p�X�t�B���^
	rHPF[0] = new JAXA_rHPF(time_ms, freq_wn);
	rHPF[1] = new JAXA_rHPF(time_ms, freq_wn);
	rHPF[2] = new JAXA_rHPF(time_ms, freq_wn);
}

//------------------------------------------//
// �@�\		�F�f�X�g���N�^					//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�Ȃ�							//
// �߂��l	�F�Ȃ�							//
//------------------------------------------//
// ���t			����	���e				//
// 2012.06.17	�V��	�V�K�쐬			//
//------------------------------------------//
Washout::~Washout()
{
	delete[] tHPF[3];
	delete[] rLPF[3];
	delete[] rHPF[3];
}

//------------------------------------------//
// �@�\		�F�E�H�b�V���A�E�g����			//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�F�q���@�̕��i�����x�Ɗp���x	//
// �߂��l	�F�Ȃ�							//
//------------------------------------------//
// ���t			����	���e				//
// 2012.03.11	�V��	t=0�ŃX�e�b�v����	//
// 2012.04.29	�V��	�߂��l���ݒ�		//
//------------------------------------------//
void Washout::washout( CDBL& ax, CDBL& ay, CDBL& az, CDBL& wphi, CDBL& wsit, CDBL& wpsi )
{
	//------------------------------------------//
	// Translation								//
	//------------------------------------------//
	// �t�B���^�X�P�[��
	double ax_scale = ax * transScale;
	double ay_scale = ay * transScale;
	double az_scale = az * transScale;

	// �d�͉����x��������
	double ax_g = ax_scale + vecGs.getx();
	double ay_g = ay_scale + vecGs.gety();
	double az_g = az_scale + vecGs.getz() - GRAVITY_mm;

	// ���i�����x���n�C�p�X�t�B���^��������
	double ax_hp = tHPF[0]->filtering( ax_g );
	double ay_hp = tHPF[1]->filtering( ay_g );
	double az_hp = tHPF[2]->filtering( az_g );

	// ���x�Z�o
	m_vx = timeInteg(m_vx, ax_hp);
	m_vy = timeInteg(m_vy, ay_hp);
	m_vz = timeInteg(m_vz, az_hp);

	// �ψʎZ�o
	m_x = timeInteg(m_x, m_vx);
	m_y = timeInteg(m_y, m_vy);
	m_z = timeInteg(m_z, m_vz);

	//------------------------------------------//
	// Tilt-coordination						//
	//------------------------------------------//
	// ���[�p�X�t�B���^����
	double ax_lp = rLPF[0]->filtering( ax_scale );
	double ay_lp = rLPF[1]->filtering( ay_scale );

	// ���������x���X�Ίp�ɕϊ�����
	sit_t = - asin( ax_lp / GRAVITY_mm );
	phi_t =   asin( ay_lp / GRAVITY_mm );

	// asin�̃G���[���m�i�j
	if( !(-deg2rad(90) <= sit_t && sit_t <= deg2rad(90)) ){
		if(ax_lp < 0){
			sit_t = deg2rad(90);
		}else{
			sit_t = -deg2rad(90);
		}
	}
	if( !(-deg2rad(90) <= phi_t && phi_t <= deg2rad(90)) ){
		if(ay_lp > 0){
			phi_t = deg2rad(90);
		}else{
			phi_t = -deg2rad(90);
		}
	}

	//------------------------------------------//
	// Rotation									//
	//------------------------------------------//
	// �t�B���^�X�P�[��
	double vphi_scale = wphi * rotateScale;
	double vsit_scale = wsit * rotateScale;
	double vpsi_scale = wpsi * rotateScale;

	// �p���x���n�C�p�X�t�B���^��������
	double wphi_hp = rHPF[0]->filtering( vphi_scale );
	double wsit_hp = rHPF[1]->filtering( vsit_scale );
	double wpsi_hp = rHPF[2]->filtering( vpsi_scale );

	// ���]�^���̊p�x���Z�o����
	phi_r = timeInteg(phi_r, wphi_hp);
	sit_r = timeInteg(sit_r, wsit_hp);
	m_psi = timeInteg(m_psi, wpsi_hp);


	//------------------------------------------//
	// Tilt�p �{ Rotation�p						//
	//------------------------------------------//
	// Tilt-coordination��Rotation�̊p�x�����Z����
	m_phi = phi_t + phi_r;
	m_sit = sit_t + sit_r;

	//------------------------------------------//
	// �d�͉����xgs�̎Z�o						//
	//------------------------------------------//
	// ���]�s���̐���
	double sphi = sin( m_phi );
	double cphi = cos( m_phi );
	double ssit = sin( m_sit );
	double csit = cos( m_sit );

	// �d�͉����xgs
	vecGs.set(
		GRAVITY_mm *   (-ssit),
		GRAVITY_mm * sphi * csit,
		GRAVITY_mm * cphi * csit );

	//------------------------------------------//
	// �p�C���b�g�̑̊������x�̎Z�o				//
	//------------------------------------------//
	stPilot.ax   = ax_hp + ax_lp;
	stPilot.ay   = ay_hp + ay_lp;
	stPilot.az   = az_hp;
	stPilot.wphi = wphi_hp;
	stPilot.wsit = wsit_hp;
	stPilot.wpsi = wpsi_hp;

	// �Ղ̉��]�����K�p
	sphi = sin( 0.0 );
	cphi = cos( 0.0 );
	ssit = sin( 0.0 );
	csit = cos( 0.0 );
	double spsi = sin( m_psi );
	double cpsi = cos( m_psi );

	// ���]�s��
	double matT[3][3] = {
		{			csit * cpsi			 ,			csit * spsi			   ,	-ssit	},
		{sphi * ssit * cpsi - cphi * spsi, sphi * ssit * spsi + cphi * cpsi, sphi * csit},
		{cphi * ssit * cpsi - sphi * spsi, cphi * ssit * spsi - sphi * cpsi, cphi * csit},
	};

	double pi_ax = stPilot.ax * matT[0][0] + stPilot.ay * matT[1][0] + stPilot.az * matT[2][0];
	double pi_ay = stPilot.ax * matT[0][1] + stPilot.ay * matT[1][1] + stPilot.az * matT[2][1];
	double pi_az = stPilot.ax * matT[0][2] + stPilot.ay * matT[1][2] + stPilot.az * matT[2][2];

	stPilot.ax = pi_ax;
	stPilot.ay = pi_ay;
	stPilot.az = pi_az;

	return;
}

//------------------------------------------//
// �@�\		�F�p�C���b�g�̑̊������x�`��	//
// ����		�F�Ȃ�							//
// ����		�F�Ȃ�							//
// �Q��		�F�Ȃ�							//
// ����		�F�V��							//
// ����		�FR�̍��W						//
// �߂��l	�F�Ȃ�							//
//------------------------------------------//
// ���t			����	���e				//
// 2012.06.17	�V��	���W�N���X�����ړ�	//
//------------------------------------------//
void Washout::rend(const Vector &vecP)
{
  // 	// �F�ݒ�
  // 	int clrAxisX = GetColor( 255, 0, 0 );
  // 	int clrAxisY = GetColor( 0, 255, 0 );
  // 	int clrAxisZ = GetColor( 0, 0, 255 );
  //
  // 	// �v���b�g�t�H�[���̈ʒuR���`���p�ɃL���X�g
  // 	float x_p_f = static_cast<float>( vecP.getx() );
  // 	float y_p_f = static_cast<float>( vecP.gety() );
  // 	float z_p_f = static_cast<float>( vecP.getz() );
  //
  // 	//------------------------------------------//
  // 	// ���i�����x�̕`�� //
  // 	//------------------------------------------//
  // 	int arrwScale = 10;
  //
  // 	// �����̒���
  // 	float ax_f = static_cast<float>( stPilot.ax / arrwScale );
  // 	float ay_f = static_cast<float>( stPilot.ay / arrwScale );
  // 	float az_f = static_cast<float>( stPilot.az / arrwScale );
  //
  // 	Vector acce(
  // 		stPilot.ax / arrwScale,
  // 		stPilot.ay / arrwScale,
  // 		stPilot.az / arrwScale );
  //
  // 	// �J�v�Z��
  // 	float cupR = 5.0;	// ���a
  //
  // 	// �~��
  // 	int coneH	= 25;	// ����
  // 	float coneR = 10;	// ���a
  //
  // 	// Ax���̕`��
  // //	DrawLine3D(
  // //		VGet( y_p_f, -z_p_f, x_p_f ),
  // //		VGet( y_p_f, -z_p_f, x_p_f + ax_f ), clrAxisX );
  //
  // 	// Ax���̕`��
  // 	if( ax_f > 0 )
  // 	{
  // 		// ��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f ),
  // 			VGet( y_p_f, -z_p_f, x_p_f ), cupR, 20, clrAxisX, clrAxisX, TRUE
  // );
  //
  // 		// �~��
  // 		DrawCone3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f + coneH ),
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f ), coneR, 20, clrAxisX,
  // clrAxisX, TRUE );
  // 	}
  // 	else if( ax_f < 0 )
  // 	{
  // 		// ��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f ),
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f ), cupR, 20, clrAxisX, clrAxisX,
  // TRUE );
  //
  // 		// �~��
  // 		DrawCone3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f - coneH ),
  // 			VGet( y_p_f, -z_p_f, x_p_f + ax_f ), coneR, 20, clrAxisX,
  // clrAxisX, TRUE );
  // 	}
  //
  // 	// Ay���̕`��
  // //	DrawLine3D(
  // //		VGet( y_p_f, -z_p_f, x_p_f ),
  // //		VGet( y_p_f + ay_f, -z_p_f, x_p_f ), clrAxisY );
  //
  // 	// Ay���̕`��
  // 	if( ay_f > 0 )
  // 	{
  // 		// ��
  // 		DrawCone3D(
  // 			VGet( y_p_f + ay_f + coneH, -z_p_f, x_p_f ),
  // 			VGet( y_p_f + ay_f, -z_p_f, x_p_f ), coneR, 20, clrAxisY,
  // clrAxisY, TRUE );
  //
  // 		// �~��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f ),
  // 			VGet( y_p_f + ay_f, -z_p_f, x_p_f ), cupR, 20, clrAxisY, clrAxisY,
  // TRUE );
  // 	}
  // 	else if( ay_f < 0 )
  // 	{
  // 		// ��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f + ay_f, -z_p_f, x_p_f ),
  // 			VGet( y_p_f, -z_p_f, x_p_f ), cupR, 20, clrAxisY, clrAxisY, TRUE
  // );
  //
  // 		// �~��
  // 		DrawCone3D(
  // 			VGet( y_p_f + ay_f - coneH, -z_p_f, x_p_f ),
  // 			VGet( y_p_f + ay_f, -z_p_f, x_p_f ), coneR, 20, clrAxisY,
  // clrAxisY, TRUE );
  // 	}
  //
  // 	// Az���̕`��
  // //	DrawLine3D(
  // //		VGet( y_p_f, -z_p_f, x_p_f ),
  // //		VGet( y_p_f, -(z_p_f + az_f), x_p_f ), clrAxisZ );
  //
  // 	// Az���̕`��
  // 	if( az_f > 0 )
  // 	{
  // 		// ��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f, -(z_p_f + az_f), x_p_f ),
  // 			VGet( y_p_f, -z_p_f, x_p_f ), cupR, 20, clrAxisZ, clrAxisZ, TRUE
  // );
  //
  // 		// �~��
  // 		DrawCone3D(
  // 			VGet( y_p_f, -(z_p_f + az_f + coneH), x_p_f ),
  // 			VGet( y_p_f, -(z_p_f + az_f), x_p_f ), coneR, 20, clrAxisZ,
  // clrAxisZ, TRUE );
  // 	}
  // 	else if( az_f < 0 )
  // 	{
  // 		// ��
  // 		DrawCapsule3D(
  // 			VGet( y_p_f, -z_p_f, x_p_f ),
  // 			VGet( y_p_f, -(z_p_f + az_f), x_p_f ), cupR, 20, clrAxisZ,
  // clrAxisZ, TRUE );
  //
  // 		// �~��
  // 		DrawCone3D(
  // 			VGet( y_p_f, -(z_p_f + az_f - coneH), x_p_f ),
  // 			VGet( y_p_f, -(z_p_f + az_f), x_p_f ), coneR, 20, clrAxisZ,
  // clrAxisZ, TRUE );
  // 	}
  //
  // #if  0
  // 	//------------------------------------------//
  // 	// �p���x�̕`�� //
  // 	//------------------------------------------//
  // 	// �~���̒���
  // 	float vphi_f  = static_cast<float>( stPilot.Vphi )  * 200;
  // 	float vsit_f = static_cast<float>( stPilot.Vsit ) * 200;
  // 	float vpsi_f  = static_cast<float>( stPilot.Vpsi )  * 200;
  //
  // 	float vphi_b  = static_cast<float>( stPilot.Vphi )  * 100;
  // 	float vsit_b = static_cast<float>( stPilot.Vsit ) * 100;
  // 	float vpsi_b  = static_cast<float>( stPilot.Vpsi )  * 100;
  //
  //
  // 	int coneH_def = 0;	// �����l
  //
  // 	// �����x���Ƃ̋���
  // 	int mrgH = -20;
  // 	int mrgW = 100;
  //
  // 	// V�ӂ̕`��
  // 	if( vphi_f == 0 ){}
  // 	else if( vphi_f > 0 ){
  // 		DrawCone3D(
  // 			VGet( y_p_f + coneH_def / 2 + vphi_f, -(z_p_f + mrgH), x_p_f +
  // mrgW ),
  // 			VGet( y_p_f - coneH_def / 2 - vphi_f, -(z_p_f + mrgH), x_p_f +
  // mrgW ), vphi_b , 20, clrAxisX, clrAxisX, TRUE ); 	}else{
  // 		DrawCone3D(
  // 			VGet( y_p_f - coneH_def / 2 + vphi_f, -(z_p_f + mrgH), x_p_f +
  // mrgW ),
  // 			VGet( y_p_f + coneH_def / 2 - vphi_f, -(z_p_f + mrgH), x_p_f +
  // mrgW ), vphi_b, 20, clrAxisX, clrAxisX, TRUE );
  // 	}
  //
  // 	// V�Ƃ̕`��
  // 	if( vsit_f == 0 ){}
  // 	else if( vsit_f > 0 ){
  // 		DrawCone3D(
  // 			VGet( y_p_f - mrgW, -(z_p_f + mrgH), x_p_f - coneH_def / 2 -
  // vsit_f ),
  // 			VGet( y_p_f - mrgW, -(z_p_f + mrgH), x_p_f + coneH_def / 2 +
  // vsit_f ), vsit_b, 20, clrAxisY, clrAxisY, TRUE ); 	}else{
  // 		DrawCone3D(
  // 			VGet( y_p_f - mrgW, -(z_p_f + mrgH), x_p_f + coneH_def / 2 -
  // vsit_f ),
  // 			VGet( y_p_f - mrgW, -(z_p_f + mrgH), x_p_f - coneH_def / 2 +
  // vsit_f ), vsit_b, 20, clrAxisY, clrAxisY, TRUE );
  // 	}
  //
  // 	// V�Ղ̕`��
  // 	if( vpsi_f == 0 ){}
  // 	else if( vpsi_f > 0 ){
  // 		DrawCone3D(
  // 			VGet( y_p_f + coneH_def / 2 + vpsi_f, -(z_p_f + mrgW), x_p_f -
  // mrgH ),
  // 			VGet( y_p_f - coneH_def / 2 - vpsi_f, -(z_p_f + mrgW), x_p_f -
  // mrgH ), vpsi_b, 20, clrAxisZ, clrAxisZ, TRUE ); 	}else{
  // 		DrawCone3D(
  // 			VGet( y_p_f - coneH_def / 2 + vpsi_f, -(z_p_f + mrgW), x_p_f -
  // mrgH ),
  // 			VGet( y_p_f + coneH_def / 2 - vpsi_f, -(z_p_f + mrgW), x_p_f -
  // mrgH ), vpsi_b, 20, clrAxisZ, clrAxisZ, TRUE );
  // 	}
  // #endif
}
