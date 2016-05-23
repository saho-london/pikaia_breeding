#pragma once

#include<memory>
#include<string>
#include<DxLib.h>
#include <typeinfo.h>

class Vector2;

//Sound���O���





namespace Sound{
	void loop_play(std::string name);
	void loop_play(int sHandle);
	void back_play(std::string name);
	void back_play(int sHandle);
	void stop_play(int sHandle);
	void check_stop_play(int sHandle);
	bool check_play(int sHandle);
}


namespace Func{
	//�����蔻��

	//2��
	template<typename T> T Sqr(T x);
	//���όv�Z
	template<typename T> T Dot2D(T Ax, T Ay, T Bx, T By);

	//�O�όv�Z
	template<typename T> T Cross2D(T Ax, T Ay, T Bx, T By);


	//�ǉ�
	//�_�Ɖ~
	bool PointCircle(const Vector2& point_pos, const Vector2& circle_center, double radius);

	//�~�`���m
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2);

	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2);

	//��`���m
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y);

	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2);

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad);

	//�_�ƕ��̂���� (�_�̍��W�A���̂�����̎n�_�E�I�_�܂ł̋����A�p�x)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad);

	//�_�Ƌ�`
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height);

	//�_�Ƌ�`
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size);

	//���ʂ̓_�Ƌ�`
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y);

	//�~(���acr,(cx,cy))�̋ߎ������`�Ɓ@�����`(����(rx1,ry1), �E��(rx2, ry2))�̓����蔻��
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2);

	//�������m(0�Ȃ炠�����ĂȂ��A0�ȏ�͂������Ă�
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y);

	//Lines�œ������Ă��ꍇ�͈ʒu���v�Z�ł���
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y);

	//�~�Ɛ���
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey);


	//�x�N�g��

	//���_�𒆐S��ang����]
	void rotateonzero(double &x, double &y, double ang);

	//����_(centerx,centery)�𒆐S��ang����]
	void rotateonpoint(double &x, double &y, double centerx, double centery, double ang);

	//(���_����(sx,sy)�ւ̒P�ʃx�N�g�������߂�
	void normalizedVector(double &vx, double &vy, double sx, double sy);

	//(sx,sy)����(ex,ey)�ւ̒P�ʃx�N�g�������߂�
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɑ��
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty);

	//(dx,dy)�����A�傫��dist�̃x�N�g�������߁A���ʂ�result�ɉ��Z
	void addVector(double r, double angle, double &resultx, double &resulty);

	//�ɍ��W�\������xy�\���ɒ���
	void polartoxy(double &x, double &y, double r, double ang);

	//�p�x���v�Z
	double calAngle(double x, double y);

	//�p�x���v�Z
	double calAngle(double sx, double sy, double ex, double ey);

	/*
	startx : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
	enddif : �J�n�ƏI���̒l�̍���
	time_now : ���݂̎���
	time_end : Tween�̍��v����
	*/

	//�^�_�@�����������O���t
	double linef(double startx, double dif, double time_now, double time_end);

	//�^�_�@����������2���Ȑ�
	double quadraticf(double startx, double dif, double time_now, double time_end);

	//3�_��ʂ钼���O���t
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end);

	//4�_��ʂ钼���O���t
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end);


	//�C�[�W���O�Ȑ�

	/*
	t : ���݂̎���
	b : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
	c : �J�n�ƏI���̒l�̍���
	d : Tween�̍��v����
	*/

	//�C�[�W���O�Ȑ� Cubic
	double ease_cubic_in(double t, double b, double c, double d);

	double ease_cubic_out(double t, double b, double c, double d);

	double ease_cubic_inout(double t, double b, double c, double d);


	//�C�[�W���O�Ȑ� Sinusoidal
	double ease_sin_in(double t, double b, double c, double d);

	double ease_sin_out(double t, double b, double c, double d);

	double ease_sin_inout(double t, double b, double c, double d);

	//�C�[�W���O�Ȑ� Exponential
	double ease_exp_in(double t, double b, double c, double d);

	double ease_exp_out(double t, double b, double c, double d);

	double ease_exp_inout(double t, double b, double c, double d);

	//�C�[�W���O�Ȑ� Circular
	double ease_sqrt_in(double t, double b, double c, double d);

	double ease_sqrt_out(double t, double b, double c, double d);

	double ease_sqrt_inout(double t, double b, double c, double d);



	//�x�W�F�Ȑ�  p1->p2->p3  0<t<1
	double bz_curve(double p1, double p2, double p3, double t);

	//�x�W�F�Ȑ�  p1->p2->p3  nowtime, endtime
	double bz_curve(double p1, double p2, double p3, double nowt, double endt);

	//�A�j���[�V�����p�E�_�^�_�^�_�^�ƂȂ�O���t
	int Repeat(int frame, int loop_num);

	//2���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t);

	//2���x�W�G�Ȑ��Ő���_���ʂ�悤�Ɉ��������ꍇ�̐���_��Ԃ��֐�
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint);

	//Control��ʂ�2���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control
		, const Vector2& End, float t);

	//3���x�W�G�Ȑ����v�Z����֐�
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1
		, const Vector2& ControlPoint2, const Vector2& End, float t);

	//�֗��֐�

	//HSV��RGB�Ɋ��Z ���ڊ֐��̈����ɓn���p
	DWORD GetColorHSV(int h, int s, int v);

	//HSV��RGB�Ɋ��Z int�ɕۑ�����p
	int HSVtoRGB(int h, int s, int v);

	//HSV��setdrawbright
	void SetDrawBrightHSV(int h, int s, int v);

	//0xXXXXXX��SetDrawBright����֐�
	void SetDrawBrightInt(int col);

	//�����̊p�x,����̊p�x 2�p�̊֌W��Ԃ��@���v��葤�ɓ������ق����߂����1 �����łȂ����-1
	int abs_angle(double angle1, double angle2);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  tarx�Ƃ̍���erange�ȉ���tarx = x�ɂ���
	void moverate(double &x, double tarx, double rate, double erange = 1.0);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist = 0.5);

	//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0  dist��0.5�ȉ���tarP = P�ɂ���
	void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist = 0.5);


	//���_�Ƃ̋�����Ԃ�
	double dist(double x, double y);

	//2�_�̋�����Ԃ�
	double dist(double x1, double y1, double x2, double y2);

	//2�_�̋�����2���Ԃ�
	double distSqr(double x1, double y1, double x2, double y2);

	//rate��cool�̃Z�b�g��cool���X�V�Ebool��Ԃ�
	bool coolcount(int &cool);

	//��E�U���E����(�b)�E�o�߃t���[�����w�肵��sin��Ԃ�
	double sinsec(double base, double a, double t, double frame);
}