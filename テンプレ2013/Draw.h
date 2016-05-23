#pragma once

#include <string>
#include <DxLib.h>

class Vector2;

namespace MyDraw{
	//�ʏ�̕`��E���W�͍�����w��
	void normal(int x, int y, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�摜�̒����̍��W���w�肵�ĕ`��
	void center(int x, int y, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�`��
	void exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�E�����w��`��
	void exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//���R�ό`�`��
	void modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//����E�E�����w�肵�ĕ`��
	void modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
	void modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
	void trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
	void circlegauge(int x, int y, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
	void circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�}�`�`��֐�

	//����`��
	void line(int sx, int sy, int ex, int ey, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//�Ǝ�
	//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
	void lineangle(int sx, int sy, int r, double angle, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//����`��
	void box(int x1, int y1, int x2, int y2, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�Ǝ�
	//���S���w�肵�Ĕ���`��
	void centerbox(double centerx, double centery, double width, double height, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�~��`��
	void circle(int x, int y, int r, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�O�p�`��`��
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);


	//�����`��֐�

	//������`��
	void text(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`��
	void centertext(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�����̉E��̍��W���w�肵�ĕ�����`��
	void righttext(int x, int y, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
	void centertext_space(int x, int y, int color, int font_handle, int space, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);



	//Vector2�g�p

	//�ʏ�̕`��E���W�͍�����w��
	void normal(const Vector2& pos, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�摜�̒����̍��W���w�肵�ĕ`��
	void center(const Vector2& pos, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�`��
	void exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�g��E��]�E�����w��`��
	void exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//���R�ό`�`��
	void modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//����E�E�����w�肵�ĕ`��
	void modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�ȉ~��ɃO���t��`��@r�ŉ~�̔��a�Erate:�c��r��rate�̔�̕��Ђ��Ⴐ������Eangle:��]�p
	void modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�摜�̎w�肵�������̂ݕ`��@�`����W�E������W�E�`��摜�T�C�Y
	void trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha = 255, int TurnFlag = 0, int BlendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��@(dx, dy)���V�t�g
	void circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�T�[�N���Q�[�W�`��i�t�����j�@(dx, dy)���V�t�g
	void circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�}�`�`��֐�

	//����`��
	void line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//�Ǝ�
	//�n�_�ƏI�_�ւ̋����A�p�x���w�肵�Đ���`��
	void lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha = 255, int Thickness = 1, int BlendMode = DX_BLENDMODE_ALPHA);

	//����`��
	void box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�Ǝ�
	//���S���w�肵�Ĕ���`��
	void centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�~��`��
	void circle(const Vector2& pos, int r, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�O�p�`��`��
	void triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);


	//�����`��֐�

	//������`��
	void text(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`��
	void centertext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);
	void centertext(const Vector2& pos, int color, int font_handle, int fontSize, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�����̉E��̍��W���w�肵�ĕ�����`��
	void righttext(const Vector2& pos, int color, int font_handle, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);

	//�w�肵�����W�𒆐S�ɕ�����`�� �����̊Ԋu���w��\
	void centertext_space(const Vector2& pos, int color, int font_handle, int space, const std::string &str, int Alpha = 255, int BlendMode = DX_BLENDMODE_ALPHA);
}